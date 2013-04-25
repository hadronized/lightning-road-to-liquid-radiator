#version 400

layout (vertices = 2) out;

in vec3 gpos[];
out vec3 tpos[];

void main() {
  tpos[gl_InvocationID] =  gpos[gl_InvocationID];
  if (gl_InvocationID == 0) {
    float t = 12.;
    gl_TessLevelOuter[0] = 1.;
    gl_TessLevelOuter[1] = t;
  }
}
