#ifndef __CUBE_PP_FS_HPP
#define __CUBE_PP_FS_HPP

#include "shader_common.hpp"

std::string const SHD_CUBE_PP_FS =
SHD_VERSION_330_CORE +
SHD_OUT_FRAG +
SHD_UNIFORM_OFFTEX +
SHD_UNIFORM_RES +
SHD_UNIFORM_TIME +
SHD_VEC2 + " uv_tex(){" +
  "float f=max(1.,min(70.,70.-(time-12.80)*80.));" +
  SHD_VEC2 + " uv=" + SHD_VEC2 + "(floor(gl_FragCoord.x/f)/(res.x/f),floor(gl_FragCoord.y/f)/(res.y/f));" +
  SHD_RETURN + " uv;" +
"}" +
SHD_GET_UV +
SHD_MAIN_FUNC +
  SHD_VEC2 + " uvtex=uv_tex();" +
  SHD_VEC2 + " uv=get_uv();" +
  "float c=clamp((2.-length(uv))*log((time-22.)/2.),0.,1.);" +
  SHD_FRAG + "=" + SHD_VEC4 + "(texture2D(offtex,uvtex))+" + SHD_VEC4 + "(c*1.1,c,c*1.3,1.);" +
"}";

#endif /* guard */

