#ifndef __TEXT_WRITER_HPP
#define __TEXT_WRITER_HPP

#include "gl.hpp"

#include "data/terminal_font.hpp" /* font to use */

class text_writer_c {
  GLuint _glyphTextures[GLYPH_NB];

  void _unpack_texels(glyph_t const &packed, float *unpacked) const;

public :
  text_writer_c(void);
  ~text_writer_c(void);

  /* return the glyph index for lookup the c character */
  static size_t glyph_index(char c);
  /* draw text at the given position */
  void draw_string(char const *text, float x, float y, float w) const;
};

#endif /* guard */

