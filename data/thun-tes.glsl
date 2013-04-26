#version 400

layout (isolines, equal_spacing, cw) in;

in vec3 tco[];
out vec3 pos;

uniform mat4 proj;
uniform float time;

vec3 interpolate2(vec3 a, vec3 b) {
  //return a - gl_TessCoord.x*(a+b);
  return (1. - gl_TessCoord.x)*a + gl_TessCoord.x*b;
}

float rand(vec2 co){
  return (sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
  pos = interpolate2(tco[0], tco[1]);
  /* displacement */
  //pos += normalize(vec3(rand(pos.xz), rand(pos.xy), rand(pos.yz)))/10.;
  gl_Position = proj * vec4(pos, 1.);
}
