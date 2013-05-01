#version 400 core

layout(vertices=3)out;

in vec3 gpos[];
out vec3 tpos[];

void main() {
  tpos[gl_InvocationID] =  gpos[gl_InvocationID];
  if (gl_InvocationID == 0) {
    float t = 12.;
    gl_TessLevelOuter[0] = t;
    gl_TessLevelOuter[1] = t;
    gl_TessLevelOuter[2] = t;
    gl_TessLevelInner[0] = t;
  }
}
