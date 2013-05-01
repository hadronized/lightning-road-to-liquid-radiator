#ifndef __CUBE_TES_HPP
#define __CUBE_TES_HPP

#include "shader_common.hpp"

std::string const SHD_CUBE_TES =
SHD_VERSION_400_CORE +
"layout(triangles,equal_spacing,cw)in;" +
SHD_IN_TPOS +
SHD_OUT_POS +
SHD_UNIFORM_PROJ +
SHD_UNIFORM_TIME +
SHD_VEC3 + " interpolate3(" + SHD_VEC3 + " a," + SHD_VEC3 + " b," + SHD_VEC3 + " c){" +
  SHD_RETURN + " a*gl_TessCoord.x+b*gl_TessCoord.y+c*gl_TessCoord.z;" +
"}" +
SHD_MAIN_FUNC +
  "pos=interpolate3(tpos[0],tpos[1],tpos[2]);" +
  SHD_VEC3 + " d=normalize(pos)-pos;" +
  "pos+=d*sin(max(0.,(time-13.7228)/8.*min(8.,(1.+max(0.,time-109.7)))));" +
  SHD_GL_POSITION + "=proj*" + SHD_VEC4 + "(pos.xy,pos.z-1.,1.);" +
"}";

#endif /* guard */

