#version 130

uniform vec2 res;
uniform float time;

out vec4 frag;

float PI = 3.14159265359;
float fovy = PI/2.;

vec2 get_uv() {
  vec2 uv = 2. * gl_FragCoord.xy / res.xy - 1.;
  uv.y /= res.x/res.y;

  return uv;
}

float heightmap(vec2 xz) {
  return -0.8;
}

void main() {
  vec2 uv = get_uv();
  vec3 cam = vec3(0., 0., 1. / tan(fovy/2.));
  vec3 ray = normalize(vec3(uv, 0.) - cam);

  frag = vec4(uv, 0., 1.);
}
