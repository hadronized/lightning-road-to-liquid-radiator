#include <bitset>
#include <cassert>
#include <cstring>
#include <iostream>
#include "text_writer.hpp"

text_writer_c::text_writer_c( ) {
  /* generate the textures for each glyph */
  float texels[GLYPH_SIZE];

  glGenTextures(GLYPH_NB, _glyphTextures);
  for (auto i = 0u; i < GLYPH_NB; ++i) {
    if (!FNT_glyphs[i])
      continue;

    /* unpack texels */
    std::cout << "processing glyph " << i << std::endl;
    _unpack_texels(*(FNT_glyphs[i]), texels);
    std::cout << "glyph is:" << std::endl;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 6; ++j)
        std::cout << texels[i*6+j];
      std::cout << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, _glyphTextures[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, GLYPH_WIDTH, GLYPH_HEIGHT, 0, GL_RED, GL_FLOAT, texels);
  }
  glBindTexture(GL_TEXTURE_2D, 0);
}

text_writer_c::~text_writer_c() {
  glDeleteTextures(GLYPH_NB, _glyphTextures);
}

void text_writer_c::_unpack_texels(glyph_t const &packed, float *unpacked) const {
  int k = 0;

  /* FIXME: 6 is completely magic here. Coincidence? */
  for (int i = 0; i < 6; ++i) {
    std::bitset<8> bits = packed[i];
    std::cout << bits << std::endl;
    for (int j = 0; j < 8; ++j, ++k)
      unpacked[k] = bits[7 - j];
  }
}

size_t text_writer_c::glyph_index(char c) {
  return c - FNT_TBL_START;
}

void text_writer_c::draw_string(char const *text, float x, float y, float w) const {
  /* stupid implementation as first shot */
  //assert (w/h == GLYPH_WIDTH/GLYPH_HEIGHT); /* with that you cannot distor glyphs */
  auto l = strlen(text);
  auto offx = w/l;
  auto offy = offx / GLYPH_RATIO;

  for (float ox = 0.f, oy = 0.f; *text; ++text) {
    switch (*text) {
      case ' ' :
        ox += offx;
        break;

#if 0
      case '\n' :
        ox = 0;
        oy += GLYPH_HEIGHT;
        break;
#endif

      default :
        glBindTexture(GL_TEXTURE_2D, _glyphTextures[glyph_index(*text)]);
        glRectf(x+ox, y+oy, x+ox+offx, y+oy+offy);
        ox += offx;
        break;
    }
  }
}
