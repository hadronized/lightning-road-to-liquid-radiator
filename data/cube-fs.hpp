#ifndef __CUBE_FS_HPP
#define __CUBE_FS_HPP

#include "shader_common.hpp"

std::string const SHD_CUBE_FS =
SHD_VERSION_330_CORE +
SHD_UNIFORM_TIME +
SHD_IN_POS +
SHD_OUT_FRAG +
SHD_VEC3 + " tex(" + SHD_VEC3 + " uv){" +
  "float v=sin(length(uv)*4.*time);" +
  SHD_RETURN + " " + SHD_VEC3 + "(v*cos(time),0.5+v/2.,1.-v*sin(time));" +
"}" +
SHD_MAIN_FUNC +
  SHD_VEC3 + " lpos=" + SHD_VEC3 + "(cos(time)*8.,sin(time)*8.,20.);" +
  SHD_VEC3 + " no=normalize(pos);" +
  SHD_VEC3 + " ldir=normalize(lpos-pos);" +
  "float d=max(0.,dot(ldir,no));" +
  SHD_FRAG + "=" + SHD_VEC4 + "(tex(pos),1.)*d;" +
"}";

#endif /* guard */

