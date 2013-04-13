#version 400

layout (vertices = 3) out;

in vec3 gpos[];
in vec3 gno[];

out vec3 tpos[];
out vec3 tno[];

void main() {
  tpos[gl_InvocationID] =  gpos[gl_InvocationID];
  tno[gl_InvocationID] =  gno[gl_InvocationID];
  gl_TessLevelOuter[0] = 4.;
  gl_TessLevelOuter[1] = 4.;
  gl_TessLevelOuter[2] = 4.;
  gl_TessLevelInner[0] = 4.;
}
