#version 400

layout (vertices = 3) out;

in vec3 gpos[];
out vec3 tpos[];

uniform float time;

void main() {
  tpos[gl_InvocationID] =  gpos[gl_InvocationID];
  if (gl_InvocationID == 0) {
    float t = pow(sin(time/2.)*10., 2.); /* TODO: formula to be changed */
    gl_TessLevelOuter[0] = t;
    gl_TessLevelOuter[1] = t;
    gl_TessLevelOuter[2] = t;
    gl_TessLevelInner[0] = t;
  }
}
