#ifndef __SWAP_LINES_FS_HPP
#define __SWAP_LINES_FS_HPP

#include "shader_common.hpp"

std::string const SHD_SWAP_LINES_FS =
SHD_VERSION_330_CORE +
SHD_OUT_FRAG +
SHD_UNIFORM_RES +
SHD_UNIFORM_OFFTEX +
SHD_UNIFORM_TIME +
SHD_GET_TEXCO +
SHD_RAND +
SHD_MAIN_FUNC +
  SHD_VEC2 + " uv=get_texco();" +
  SHD_VEC2 + " lookup=" + SHD_VEC2 + "(uv.x,mod(uv.y+clamp(time-54.,0.,1.)*fract(rand(vec2(0.,uv.y))),res.y));" +
  SHD_FRAG + "=texture2D(offtex,lookup);" +
"}";

#endif /* guard */

