#ifndef __THUN_FS_HPP
#define __THUN_FS_HPP

#include "shader_common.hpp"

std::string const SHD_THUN_FS =
SHD_VERSION_330_CORE +
SHD_OUT_FRAG +
SHD_MAIN_FUNC +
  SHD_FRAG + "=" + SHD_VEC4 + "(0.6,0.5,1.,1.);" +
"}";

#endif /* guard */

