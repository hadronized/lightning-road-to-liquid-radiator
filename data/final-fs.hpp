#ifndef __FINAL_FS_HPP
#define __FINAL_FS_HPP

char const *SHD_FINAL_FS =
"#version 330\n"
"out vec4 frag;"
"uniform vec2 start;" /* left upper */
"uniform vec2 gres;" /* glyph resolution */
"uniform vec2 res;"
"uniform sampler2D tex;"
"void main(){"
  "frag=texture2D(tex,(gl_FragCoord.xy-start.xy)*res.xy*gres.xy);"
  //"frag=vec4((gl_FragCoord.xy-start.xy)*res.xy*gres.xy, 0., 1.);"
"}";

#endif /* guard */

