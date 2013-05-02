#ifndef __SWAP_LINES_FS_HPP
#define __SWAP_LINES_FS_HPP

char const *SHD_SWAP_LINES_FS =
"#version 330 core\n"
"out vec4 frag;"
"uniform vec4 res;"
"uniform sampler2D offtex;"
"uniform float time;"
"vec2 get_texco() {"
  "return gl_FragCoord.xy * res.zw;"
"}"
"float rand(vec2 a){"
  "return fract(sin(dot(a.xy,vec2(12.9898,78.233)))*43758.5453);"
"}"
"void main(){"
  "vec2 uv=get_texco();"
  "vec2 lookup=vec2(uv.x,mod(uv.y+clamp(time-54.,0.,1.)*rand(vec2(0.,uv.y)),res.y));"
  "frag=texture2D(offtex,lookup);"
"}";

#endif /* guard */

