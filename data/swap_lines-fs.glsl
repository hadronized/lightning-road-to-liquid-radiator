#version 330

out vec4 frag;

uniform vec4 res;
uniform sampler2D offtex;
uniform float time;

vec2 get_uv() {
  return gl_FragCoord.xy * res.zw;
}

float rand(vec2 co){
  return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
  vec2 uv = get_uv();
  vec2 lookup = vec2(uv.x, mod(uv.y+clamp(time - 54., 0., 1.)*rand(vec2(0., uv.y)), res.y));
  frag = texture2D(offtex, lookup);
}
