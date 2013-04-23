#ifndef __MOD3_HPP
#define __MOD3_HPP

#include "gl.hpp"

namespace {
}

class mod3_c {
  /* shader stuff */

  void _init_uniforms();

public :
  mod3_c();
  ~mod3_c();

  void render(float time);
};

#endif /* guard */

