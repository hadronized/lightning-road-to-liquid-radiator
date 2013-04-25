#version 400

layout (isolines, equal_spacing, cw) in;

in vec3 tpos[];

out vec3 pos;

uniform mat4 proj;
uniform float time;

vec3 interpolate2(vec3 a, vec3 b) {
  return a - gl_TessCoord.y*(a+b);
}

void main() {
  pos = interpolate2(tpos[0], tpos[1]);
  gl_Position = proj * vec4(pos, 1.);
}
