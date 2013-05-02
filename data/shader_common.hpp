#ifndef __SHADER_COMMON_HPP
#define __SHADER_COMMON_HPP

#include <string>

std::string const SHD_VERSION_330_CORE = "#version 330 core\n";
std::string const SHD_VERSION_400_CORE = "#version 400 core\n";
std::string const SHD_IN_CO            = "in vec3 co;";
std::string const SHD_OUT_GPOS         = "out vec3 gpos;";
std::string const SHD_IN_GPOS          = "in vec3 gpos[];";
std::string const SHD_OUT_TPOS         = "out vec3 tpos[];";
std::string const SHD_IN_TPOS          = "in vec3 tpos[];";
std::string const SHD_OUT_POS          = "out vec3 pos;";
std::string const SHD_IN_POS           = "in vec3 pos;";
std::string const SHD_OUT_FRAG         = "out vec4 frag;";
std::string const SHD_GL_POSITION      = "gl_Position";
std::string const SHD_UNIFORM_RES      = "uniform vec4 res;";
std::string const SHD_UNIFORM_TIME     = "uniform float time;";
std::string const SHD_UNIFORM_PROJ     = "uniform mat4 proj;";
std::string const SHD_UNIFORM_OFFTEX   = "uniform sampler2D offtex;";
std::string const SHD_MAIN_FUNC        = "void main(){";
std::string const SHD_VEC2             = "vec2";
std::string const SHD_VEC3             = "vec3";
std::string const SHD_VEC4             = "vec4";
std::string const SHD_GL_INVOC_ID      = "gl_InvocationID";
std::string const SHD_GL_VERTEX_ID     = "gl_VertexID";
std::string const SHD_PRIMITIVE_ID     = "gl_PrimitiveID";
std::string const SHD_GL_TESS_LVL_OUT  = "gl_TessLevelOuter";
std::string const SHD_GL_TESS_LVL_IN   = "gl_TessLevelInner";
std::string const SHD_RETURN           = "return";
std::string const SHD_FRAG             = "frag";
std::string const SHD_GET_UV           =
"vec2 get_uv(){"
  "vec2 uv=2.*gl_FragCoord.xy*res.zw-1.;"
  "uv.y*=res.y*res.z;"
  "return uv;"
"}";
std::string const SHD_GET_TEXCO        =
"vec2 get_texco() {"
  "return gl_FragCoord.xy * res.zw;"
"}";
std::string const SHD_RAND             =
"float rand(vec2 a){"
  "return sin(dot(a.xy,vec2(12.9898,78.233)))*43758.5453;"
"}";
std::string const SHD_PI               = "const float PI=3.14159265359;";

#endif /* guard */

