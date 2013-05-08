#ifndef __FINAL_COLORS_FS_HPP
#define __FINAL_COLORS_FS_HPP

char const *SHD_FINAL_COLORS_FS =
"#version 330\n"
"out vec4 frag;"
"uniform float time;"
"uniform vec2 res;"
"uniform sampler2D tex;"
"float plasma(vec2 uv){"
  "return sin(uv.x*28.+time)+sin(uv.y*28.-time)+sin(length(uv)*28.+time*2.);"
"}"
"void main(){"
  "vec2 uv=gl_FragCoord.xy*res;"
  "float p=plasma(uv);"
  "frag=texture2D(tex,uv)*vec4(p/2.,0.5-p,0.5+p*sin(time)/2.,1.);"
"}";

#endif /* guard */

