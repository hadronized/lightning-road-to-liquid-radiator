#ifndef __CUBE_VS_HPP
#define __CUBE_VS_HPP

#include "shader_common.hpp"

std::string const SHD_CUBE_VS =
SHD_VERSION_330_CORE +
SHD_IN_CO +
SHD_OUT_GPOS +
SHD_UNIFORM_TIME +
SHD_MAIN_FUNC +
"float t = time/2.;" +
SHD_VEC3 + " coZ=co;" +
"coZ.x=co.x*cos(t)-co.y*sin(t);" +
"coZ.y=co.x*sin(t)+co.y*cos(t);" +
SHD_VEC3 + " coYZ=coZ;" +
"coYZ.x=coZ.x*cos(t)+coZ.z*sin(t);" +
"coYZ.z=-coZ.x*sin(t)+coZ.z*cos(t);" +
SHD_VEC3 + " coXYZ=coYZ;" +
"coXYZ.y=coYZ.y*sin(t)+coYZ.z*cos(t);" +
"coXYZ.z=coYZ.y*cos(t)-coYZ.z*sin(t);" +
"gpos=coXYZ;}";

#endif /* guard */

