#ifndef __GLYPH_FS_HPP
#define __GLYPH_FS_HPP

char const *SHD_GLYPH_FS =
"#version 330\n"
"in vec2 uv;"
"out vec4 frag;"
"uniform vec4 gres;" /* glyph resolution */
"uniform sampler2D tex;" /* texture of the glyph */
"uniform int v;"
"void main(){"
  "float f=texture2D(tex,vec2(uv.x,(1.-uv.y)));"
  "frag=vec4(f*sin(float(v*v)),f,f,1.);"
"}";

#endif /* guard */

