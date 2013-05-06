#include "text_writer.hpp"

text_writer_c::text_writer_c( ) {
  /* generate the textures for each glyph */

  glGenTextures(GLYPH_NB, _glyphTextures);
  for (auto i = 0u; i < GLYPH_NB; ++i) {
    glBindTexture(GL_TEXTURE_2D, _glyphTextures[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, GLYPH_WIDTH, GLYPH_HEIGHT, 0, GL_RED, GL_BYTE, FNT_glyphs[i]);
  }
}

text_writer_c::~text_writer_c() {
  glDeleteTextures(GLYPH_NB, _glyphTextures);
}

size_t text_writer_c::glyph_index(char c) {
  return c - FNT_TBL_START;
}

void text_writer_c::draw_string(char const *text, float x, float y) const {
  /* stupid implementation as first shot */
  for (int off = 0; *text; ++text, off += GLYPH_WIDTH) {
    glBindTexture(GL_TEXTURE_2D, _glyphTextures[glyph_index(*text)]);
    glRectf(x+off, y, x+off+GLYPH_WIDTH, y+GLYPH_HEIGHT);
  }
}
