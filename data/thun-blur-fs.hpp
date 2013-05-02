#ifndef __THUN_BLUR_FS_HPP
#define __THUN_BLUR_FS_HPP

#include "shader_common.hpp"

std::string const SHD_THUN_BLUR_FS =
SHD_VERSION_330_CORE +
SHD_OUT_FRAG +
SHD_UNIFORM_RES +
SHD_UNIFORM_OFFTEX +
SHD_GET_TEXCO +
SHD_MAIN_FUNC +
  SHD_VEC2 + " uv=get_texco();" +
  "float s=res.z*1.5;" +
  SHD_FRAG + "=texture2D(offtex," + SHD_VEC2 + "(uv.x-s*3.,uv.y))*0.05" +
             "+texture2D(offtex,vec2(uv.x-s*2.,uv.y))*0.10" +
             "+texture2D(offtex,vec2(uv.x-s,uv.y))*0.40" +
             "+texture2D(offtex,vec2(uv.x,uv.y))*0.5" +
             "+texture2D(offtex,vec2(uv.x+s,uv.y))*0.40" +
             "+texture2D(offtex,vec2(uv.x+s*2.,uv.y))*0.10" +
             "+texture2D(offtex,vec2(uv.x+s*3.,uv.y))*0.05;" +
  SHD_FRAG + "+=texture2D(offtex,vec2(uv.x,uv.y-s*3.))*0.05" +
              "+texture2D(offtex,vec2(uv.x,uv.y-s*2.))*0.10" +
              "+texture2D(offtex,vec2(uv.x,uv.y-s))*0.40" +
              "+texture2D(offtex,vec2(uv.x,uv.y))*0.5" +
              "+texture2D(offtex,vec2(uv.x,uv.y+s))*0.40" +
              "+texture2D(offtex,vec2(uv.x,uv.y+s*2.))*0.10" +
              "+texture2D(offtex,vec2(uv.x,uv.y+s*3.))*0.05;" +
  SHD_FRAG + "*=0.5;" +
"}";

#endif /* guard */

