#ifndef __THUN_TCS_HPP
#define __THUN_TCS_HPP

char const *SHD_THUN_TCS =
"#version 400 core\n"
"layout(vertices=2)out;"
"in vec3 gpos[];"
"out vec3 tpos[];"
"void main(){"
  "tpos[gl_InvocationID]=gpos[gl_InvocationID];"
  "if(gl_InvocationID==0){"
    "gl_TessLevelOuter[0]=1.;"
    "gl_TessLevelOuter[1]=6.;"
  "}"
"}";

#endif /* guard */

