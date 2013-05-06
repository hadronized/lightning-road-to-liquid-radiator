#ifndef __FINAL_FS_HPP
#define __FINAL_FS_HPP

char const *SHD_FINAL_FS =
"#version 330\n"
"out vec4 frag;"
"uniform vec2 res;"
"uniform sampler2D tex;"
"void main(){"
  "frag=texture2D(tex,gl_FragCoord.xy*res.xy);"
"}";

#endif /* guard */

