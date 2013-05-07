#ifndef __MOD3_HPP
#define __MOD3_HPP

#include "gl.hpp"
#include "shader.hpp"
#include "text_writer.hpp"

namespace {
}

class mod3_c {
  /* text writer */
  text_writer_c &_writer;

public :
  mod3_c(text_writer_c &writer);
  ~mod3_c();

  void render(float time);
};

#endif /* guard */

