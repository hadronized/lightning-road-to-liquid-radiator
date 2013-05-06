#ifndef __GLYPH_FS_HPP
#define __GLYPH_FS_HPP

char const *SHD_GLYPH_FS =
"#version 330\n"
"in vec2 uv;"
"out vec4 frag;"
"uniform vec4 gres;" /* glyph resolution */
"uniform sampler2D tex;" /* texture of the glyph */
"void main(){"
  "frag=texture2D(tex,vec2(floor(uv.x*gres.x)*gres.z,floor(uv.y*gres.y)*gres.w));"
  //"frag=vec4(vec2(floor(uv.x*gres.x)*gres.z,floor(uv.y*gres.y)*gres.w), 0., 1.);"
"}";

#endif /* guard */

