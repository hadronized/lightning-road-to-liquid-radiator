#ifndef __GLYPH_VS_HPP
#define __GLYPH_VS_HPP

char const *SHD_GLYPH_VS =
"#version 330\n"
"out vec2 uv;"
"uniform vec4 p;" /* position of the left upper corner, and width and height */
"vec2 co[4]=vec2[]("
  "vec2(p.x+p.z,p.y),"
  "vec2(p.x+p.z,p.y+p.w),"
  "vec2(p.x,p.y),"
  "vec2(p.x,p.y+p.w)"
");"
"void main(){"
  "gl_Position=vec4(co[gl_VertexID], 0., 1.);"
  "uv=co[gl_VertexID] / p.zw;"
"}";

#endif /* guard */

