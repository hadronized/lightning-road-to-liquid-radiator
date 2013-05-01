#ifndef __SHADER_COMMON_HPP
#define __SHADER_COMMON_HPP

#include <string>

std::string const SHD_VERSION_330_CORE = "#version 330 core\n";
std::string const SHD_VERSION_400_CORE = "#version 400 core\n";
std::string const SHD_IN_CO            = "in vec3 co;";
std::string const SHD_OUT_GPOS         = "out vec3 gpos;";
std::string const SHD_IN_GPOS          = "in vec3 gpos[];";
std::string const SHD_OUT_TPOS         = "out vec3 tpos[];";
std::string const SHD_UNIFORM_TIME     = "uniform float time;";
std::string const SHD_MAIN_FUNC        = "void main(){";
std::string const SHD_VEC3             = "vec3";
std::string const SHD_GL_INVOC_ID      = "gl_InvocationID";
std::string const SHD_GL_TESS_LVL_OUT  = "gl_TessLevelOuter";
std::string const SHD_GL_TESS_LVL_IN   = "gl_TessLevelInner";

#endif /* guard */

