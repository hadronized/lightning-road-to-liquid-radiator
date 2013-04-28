#version 400

layout (isolines, equal_spacing, cw) in;

in vec3 tco[];
out vec3 pos;

uniform mat4 proj;
uniform float time;

const float PI = 3.14159265359;

vec3 interpolate2(vec3 a, vec3 b) {
  return a + gl_TessCoord.x*(b-a);
}

float rand(vec2 co) {
  return sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453;
}

vec3 displace(vec3 p) {
  float id = gl_PrimitiveID + 1 + time/5.;
  float pc = 1. - abs(1. - 2*gl_TessCoord.x); /* displacement contribution along the line */
  float md = 0.28; /* max displacement */
  vec3 disp = vec3(rand(vec2(pc, id*2.)), rand(vec2(-id*3., pc*5.)), rand(vec2(-pc,pc*7.))); /* displacement value */
  disp = normalize(disp);
  return p + disp*md*pc;
}

void main() {
  pos = interpolate2(tco[0], tco[1]);
  /* displacement */
  pos = displace(pos);
  gl_Position = proj * vec4(pos, 1.);
}
