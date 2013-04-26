#version 400

layout (vertices = 2) out;

in vec3 gco[];
out vec3 tco[];

void main() {
  tco[gl_InvocationID] =  gco[gl_InvocationID];
  if (gl_InvocationID == 0) {
    float t = 2.;
    gl_TessLevelOuter[0] = 1.;
    gl_TessLevelOuter[1] = t;
  }
}
