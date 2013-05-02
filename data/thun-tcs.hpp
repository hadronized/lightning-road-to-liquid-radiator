#ifndef __THUN_TCS_HPP
#define __THUN_TCS_HPP

#include "shader_common.hpp"

std::string const SHD_THUN_TCS =
SHD_VERSION_400_CORE +
"layout(vertices=2)out;" +
SHD_IN_GPOS +
SHD_OUT_TPOS +
SHD_MAIN_FUNC +
  "tpos[" + SHD_GL_INVOC_ID + "]=gpos[" + SHD_GL_INVOC_ID + "];" +
  "if(" + SHD_GL_INVOC_ID + "==0){" +
    SHD_GL_TESS_LVL_OUT + "[0]=1.;" +
    SHD_GL_TESS_LVL_OUT + "[1]=6.;" +
  "}" +
"}";

#endif /* guard */

