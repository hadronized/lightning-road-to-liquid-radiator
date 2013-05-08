#ifndef __CUBE_TES_HPP
#define __CUBE_TES_HPP

char const *SHD_CUBE_TES =
"#version 330\n"
"#extension GL_ARB_tessellation_shader : enable\n"
"layout(triangles,equal_spacing,cw)in;"
"in vec3 tpos[];"
"out vec3 pos;"
"uniform mat4 proj;"
"uniform float time;"
"vec3 interpolate3(vec3 a,vec3 b,vec3 c){"
  "return a*gl_TessCoord.x+b*gl_TessCoord.y+c*gl_TessCoord.z;"
"}"
"void main(){"
  "pos=interpolate3(tpos[0],tpos[1],tpos[2]);"
  "vec3 d=normalize(pos)-pos;"
  "pos+=d*sin(max(0.,(time-13.7228)/8.*min(8.,(1.+max(0.,time-109.7)))));"
  "gl_Position=proj*vec4(pos.xy,pos.z-1.,1.);"
"}";

#endif /* guard */

