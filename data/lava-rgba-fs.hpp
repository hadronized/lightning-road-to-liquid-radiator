#ifndef __LAVA_RGBA_FS_HPP
#define __LAVA_RGBA_FS_HPP

#include "shader_common.hpp"

std::string const SHD_LAVA_RGBA_FS =
SHD_VERSION_330_CORE +
SHD_OUT_FRAG +
SHD_UNIFORM_OFFTEX +
SHD_UNIFORM_RES +
SHD_UNIFORM_TIME +
SHD_GET_TEXCO +
SHD_MAIN_FUNC +
  SHD_VEC2 + " uv=get_texco();" +
  SHD_VEC2 + " step2=0.5*res.zw/mod(max(0.01,time-54.8732),13.7150);" +
  SHD_FRAG + "=" + SHD_VEC4 + "(" +
    "texture2D(offtex,uv).r," +
    "texture2D(offtex,vec2(uv.x+step2.y,uv.y)).g," +
    "texture2D(offtex,vec2(uv.x,uv.y+step2.y)).b," +
    "1.);" +
"}";

#endif /* guard */

