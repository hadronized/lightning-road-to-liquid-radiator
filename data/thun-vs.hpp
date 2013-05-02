#ifndef __THUN_VS_HPP
#define __THUN_VS_HPP

#include "shader_common.hpp"

std::string const SHD_THUN_VS =
SHD_VERSION_330_CORE +
SHD_OUT_GPOS +
SHD_UNIFORM_TIME +
SHD_RAND +
SHD_MAIN_FUNC +
  "int id=10*" + SHD_GL_VERTEX_ID + "+1;" +
  SHD_VEC3 + " p=" + SHD_VEC3 + "(rand(vec2(id,id*2.)),"
                "rand(vec2(id*3.,id*5.))," +
                "rand(vec2(id*7.,id*9.)));" +
  "p=" + SHD_VEC3 + "(normalize(p.xy),p.z);" +
  //p.z = -mod(gl_VertexID-time*3., 50.);
  "p.z=mod(-" + SHD_GL_VERTEX_ID + "/2.+(time-27.8)*3,-20.);" +
  "gpos=p;" +
"}";

#endif /* guard */

