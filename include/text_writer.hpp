#ifndef __TEXT_WRITER_HPP
#define __TEXT_WRITER_HPP

#include "gl.hpp"
#include "shader.hpp"

#include "data/terminal_font.hpp" /* font to use */

class text_writer_c {
  GLuint _glyphTextures[GLYPH_NB];
  shader_c _vs;
  shader_c _fs;
  program_c _ps;
  
  /* VA */
  GLuint _va;

  /* uniforms */
  GLint _pIndex;
  GLint _pValue;

  void _generate_glyphs(void);
  void _init_shader(void);
  void _init_uniforms(void);
  void _unpack_texels(glyph_t const &packed, float *unpacked) const;

public :
  text_writer_c(void);
  ~text_writer_c(void);

  /* return the glyph index for lookup the c character */
  static size_t glyph_index(char c);
  /* start a draw */
  void start_draw(void);
  /* draw text at the given position */
  void draw_string(char const *text, float x, float y, float h) const;
  /* end a draw */
  void end_draw(void);
};

#endif /* guard */

