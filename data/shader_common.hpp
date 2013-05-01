#ifndef __SHADER_COMMON_HPP
#define __SHADER_COMMON_HPP

#include <string>

std::string const SHD_VERSION_330_CORE = "#version 330 core\n";
std::string const SHD_IN_CO            = "in vec3 co;";
std::string const SHD_OUT_GPOS         = "out vec3 gpos;";
std::string const SHD_UNIFORM_TIME     = "uniform float time;";
std::string const SHD_MAIN_FUNC        = "void main(){";
std::string const SHD_VEC3             = "vec3";

#endif /* guard */

