#ifndef __THUN_TES_HPP
#define __THUN_TES_HPP

char const *SHD_THUN_TES =
"#version 330\n"
"#extension GL_ARB_tessellation_shader : enable\n"
"layout(isolines,equal_spacing,cw)in;"
"in vec3 tpos[];"
"out vec3 pos;"
"uniform mat4 proj;"
"uniform float time;"
"const float PI=3.14159265359;"
"vec3 interpolate2(vec3 a,vec3 b){"
  "return a+gl_TessCoord.x*(b-a);"
"}"
"float rand(vec2 a){"
  "return sin(dot(a.xy,vec2(12.9898,78.233)))*43758.5453;"
"}"
"vec3 displace(vec3 p){"
  "float id=gl_PrimitiveID+1+floor(time*28.);"
  "float pc=pow(1.-abs(1.-2*gl_TessCoord.x), 1);"
  "float md=0.15;"
  "vec3 disp=vec3(rand(vec2(pc,id*2.)),rand(vec2(-id*3.,pc*5.)),rand(vec2(-pc,pc*7.)));"
  "disp=normalize(disp);"
  "return p+disp*md*pc;"
"}"
"void main(){"
  "pos=interpolate2(tpos[0],tpos[1]);"
  "pos=displace(pos);"
  "gl_Position=proj*vec4(pos, 1.);"
"}";

#endif /* guard */

