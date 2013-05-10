#ifndef __THUN_BLUR_FS_HPP
#define __THUN_BLUR_FS_HPP

char const *SHD_THUN_BLUR_FS =
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
      "+texture2D(offtex,vec2(uv.x-s,uv.y))*0.40"
      "+texture2D(offtex,vec2(uv.x,uv.y))*0.5"
      "+texture2D(offtex,vec2(uv.x+s,uv.y))*0.40"
      "+texture2D(offtex,vec2(uv.x+s*2.,uv.y))*0.10"
      "+texture2D(offtex,vec2(uv.x+s*6.,uv.y))*0.08"
      "+texture2D(offtex,vec2(uv.x+s*10.,uv.y))*0.05"
      "+texture2D(offtex,vec2(uv.x+s*18.,uv.y))*0.02;"
  "frag+=texture2D(offtex,vec2(uv.x,uv.y-s*18.))*0.02"
       "+texture2D(offtex,vec2(uv.x,uv.y-s*10.))*0.05"
       "+texture2D(offtex,vec2(uv.x,uv.y-s*6.))*0.08"
       "+texture2D(offtex,vec2(uv.x,uv.y-s*2.))*0.10"
       "+texture2D(offtex,vec2(uv.x,uv.y-s))*0.40"
       "+texture2D(offtex,vec2(uv.x,uv.y))*0.5"
       "+texture2D(offtex,vec2(uv.x,uv.y+s))*0.40"
       "+texture2D(offtex,vec2(uv.x,uv.y+s*2.))*0.10"
       "+texture2D(offtex,vec2(uv.x,uv.y+s*6.))*0.08"
       "+texture2D(offtex,vec2(uv.x,uv.y+s*10.))*0.05;"
       "+texture2D(offtex,vec2(uv.x,uv.y+s*18.))*0.02;"
  "frag*=0.5;"
"}";

#endif /* guard */

