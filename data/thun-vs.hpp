#ifndef __THUN_VS_HPP
#define __THUN_VS_HPP

char const *SHD_THUN_VS =
"#version 330 core\n"
"out vec3 gpos;"
"uniform float time;"
"float rand(vec2 a){"
  "return sin(dot(a.xy,vec2(12.9898,78.233)))*43758.5453;"
"}"
"void main(){"
  "int id=10*gl_VertexID+1;"
  "vec3 p=vec3(rand(vec2(id,id*2.)),"
              "rand(vec2(-id*3.,id*5.)),"
              "rand(vec2(id*7.,-id*9.)));"
  "p=vec3(normalize(p.xy),p.z);"
  "p.z=mod(-gl_VertexID/2.+(time-27.8)*3,-20.);"
  "gpos=p;"
"}";

#endif /* guard */

