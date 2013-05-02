#ifndef __THUN_TES_HPP
#define __THUN_TES_HPP

#include "shader_common.hpp"

std::string const SHD_THUN_TES =
SHD_VERSION_400_CORE +
"layout(isolines,equal_spacing,cw)in;" +
SHD_IN_TPOS +
SHD_OUT_POS +
SHD_UNIFORM_PROJ +
SHD_UNIFORM_TIME +
SHD_PI +
SHD_VEC3 + " interpolate2(" + SHD_VEC3 + " a," + SHD_VEC3 + " b){" +
  SHD_RETURN + " a+gl_TessCoord.x*(b-a);" +
"}" +
SHD_RAND +
SHD_VEC3 + " displace(" + SHD_VEC3 + " p){" +
  "float id=" + SHD_PRIMITIVE_ID + "+1+time/5.;" +
  "float pc=1.-abs(1.-2*gl_TessCoord.x);" +
  "float md=0.28;" +
  SHD_VEC3 +" disp=" + SHD_VEC3 + "(rand(" + SHD_VEC2 + "(pc,id*2.)),rand(" + SHD_VEC2 + "(-id*3.,pc*5.)),rand(" + SHD_VEC2 + "(-pc,pc*7.)));" +
  "disp=normalize(disp);" +
  SHD_RETURN + " p+disp*md*pc;" +
"}" +
SHD_MAIN_FUNC +
  "pos=interpolate2(tpos[0],tpos[1]);" +
  "pos=displace(pos);" +
  SHD_GL_POSITION + "=proj*vec4(pos, 1.);" +
"}";

#endif /* guard */

