#ifndef __THUN_HBLUR_FS_HPP
#define __THUN_HBLUR_FS_HPP

char const *SHD_THUN_HBLUR_FS =
"#version 330 core\n"
"out vec4 frag;"
"uniform vec4 res;"
"uniform sampler2D offtex;"
"vec2 get_texco() {"
  "return gl_FragCoord.xy * res.zw;"
"}"
"void main(){"
  "vec2 uv=get_texco();"
  "float s=res.z*1.5;"
  "frag=texture2D(offtex,vec2(uv.x-s*18.,uv.y))*0.02"
      "+texture2D(offtex,vec2(uv.x-s*10.,uv.y))*0.05"
      "+texture2D(offtex,vec2(uv.x-s*6.,uv.y))*0.08"
      "+texture2D(offtex,vec2(uv.x-s*2.,uv.y))*0.10"
      "+texture2D(offtex,vec2(uv.x-s,uv.y))*0.35"
      "+texture2D(offtex,vec2(uv.x,uv.y))*0.5"
      "+texture2D(offtex,vec2(uv.x+s,uv.y))*0.35"
      "+texture2D(offtex,vec2(uv.x+s*2.,uv.y))*0.10"
      "+texture2D(offtex,vec2(uv.x+s*6.,uv.y))*0.08"
      "+texture2D(offtex,vec2(uv.x+s*10.,uv.y))*0.05"
      "+texture2D(offtex,vec2(uv.x+s*18.,uv.y))*0.02;"
"}";

#endif /* guard */

