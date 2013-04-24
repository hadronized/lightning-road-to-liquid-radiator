#version 330

uniform vec4 res;
uniform float time;

out vec4 frag;

vec2 get_uv() {
  vec2 uv = 2. * gl_FragCoord.xy * res.zw - 1.;
  uv.y *= res.x*res.z;
  return uv;
}

void main() {
  vec2 uv = get_uv();
  frag = vec4(uv, 0., 1.);
}
