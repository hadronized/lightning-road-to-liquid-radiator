#include <bitset>
#include <cassert>
#include <cstring>
#include <iostream>
#include "common.hpp"
#include "text_writer.hpp"

/* shaders sources */
#include "data/glyph-vs.hpp"
#include "data/glyph-fs.hpp"

text_writer_c::text_writer_c( ) :
    _vs(GL_VERTEX_SHADER)
  , _fs(GL_FRAGMENT_SHADER) {
  _generate_glyphs();
  _init_shader();
  _init_uniforms();
  glGenVertexArrays(1, &_va);
  glBindVertexArray(_va);
  glBindVertexArray(0);
}

text_writer_c::~text_writer_c() {
  glDeleteVertexArrays(1, &_va);
  glDeleteTextures(GLYPH_NB, _glyphTextures);
}

void text_writer_c::_generate_glyphs() {
  /* generate the textures for each glyph */
  float texels[GLYPH_SIZE];

  glGenTextures(GLYPH_NB, _glyphTextures);
  for (auto i = 0u; i < GLYPH_NB; ++i) {
    if (!FNT_glyphs[i])
      continue;

    /* unpack texels */
    _unpack_texels(*(FNT_glyphs[i]), texels);
#if DEBUG
    std::cout << "processing glyph " << i << std::endl;
    std::cout << "glyph is:" << std::endl;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 6; ++j)
        std::cout << (texels[i*6+j] ? 'X' : '_');
      std::cout << std::endl;
    }
#endif
    glBindTexture(GL_TEXTURE_2D, _glyphTextures[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, GLYPH_WIDTH, GLYPH_HEIGHT, 0, GL_RED, GL_FLOAT, texels);
  }
  glBindTexture(GL_TEXTURE_2D, 0);
}

void text_writer_c::_init_shader() {
  _vs.source(SHD_GLYPH_VS);
  _vs.compile();
  if (!_vs.compiled()) {
    std::cerr << "Glyph vertex shader failed to compile:\n" << _vs.compile_log() << std::endl;
    exit(1);
  }
  _fs.source(SHD_GLYPH_FS);
  _fs.compile();
  if (!_fs.compiled()) {
    std::cerr << "Glyph fragment shader failed to compile:\n" << _fs.compile_log() << std::endl;
    exit(1);
  }
  _ps.attach(_vs);
  _ps.attach(_fs);
  _ps.link();
  if (!_ps.linked()) {
    std::cerr << "Glyph program shader failed to compile:\n" << _ps.link_log() << std::endl;
    exit(2);
  }
}

void text_writer_c::_init_uniforms() {
  glUseProgram(_ps.id());
  _pIndex = _ps.map_uniform("p");
  auto gResIndex = _ps.map_uniform("gres");
  auto texIndex = _ps.map_uniform("tex");
  glUniform4f(gResIndex, GLYPH_WIDTH, GLYPH_HEIGHT, 1.f/GLYPH_WIDTH, 1.f/GLYPH_HEIGHT);
  glUniform1i(texIndex, 0);
}

void text_writer_c::_unpack_texels(glyph_t const &packed, float *unpacked) const {
  int k = 0;

  /* FIXME: 6 is completely magic here. Coincidence? */
  for (int i = 0; i < 6; ++i) {
    std::bitset<8> bits = packed[i];
    for (int j = 0; j < 8; ++j, ++k)
      unpacked[k] = bits[7 - j];
  }
}

size_t text_writer_c::glyph_index(char c) {
  return c - FNT_TBL_START;
}

void text_writer_c::start_draw() {
  glUseProgram(_ps.id());
}

void text_writer_c::draw_string(char const *text, float x, float y, float h) const {
  /* stupid implementation as first shot */
  auto w = h * GLYPH_RATIO;

  for (float ox = 0.f, oy = 0.f; *text; ++text) {
    switch (*text) {
      case ' ' :
        ox += w;
        break;

      case '\n' :
        ox = 0;
        oy -= h;
        break;

      default :
        glBindTexture(GL_TEXTURE_2D, _glyphTextures[glyph_index(*text)]);
        glBindVertexArray(_va);
        glUniform4f(_pIndex, x+ox, y+oy, w, h);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
        ox += w;
        break;
    }
  }
}

void text_writer_c::end_draw() {
}

