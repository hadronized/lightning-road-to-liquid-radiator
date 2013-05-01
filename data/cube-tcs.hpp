#ifndef __CUBE_TCS_HPP
#define __CUBE_TCS_HPP

#include "shader_common.hpp"

std::string const SHD_CUBE_TCS =
SHD_VERSION_400_CORE +
"layout(vertices=3)out;" +
SHD_IN_GPOS +
SHD_OUT_TPOS +
SHD_MAIN_FUNC +
"tpos[" + SHD_GL_INVOC_ID + "]=gpos[" + SHD_GL_INVOC_ID + "];" +
"if(" + SHD_GL_INVOC_ID + "==0){" +
    "float t=12.;" +
    SHD_GL_TESS_LVL_OUT + "[0]=t;" +
    SHD_GL_TESS_LVL_OUT + "[1]=t;" +
    SHD_GL_TESS_LVL_OUT + "[2]=t;" +
    SHD_GL_TESS_LVL_IN + "[0]=t;" +
  "}" +
"}";

#endif /* guard */

