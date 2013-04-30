#version 330

out vec4 frag;

uniform vec4 res;
uniform sampler2D offtex;
uniform float time;

vec2 get_uv() {
  return gl_FragCoord.xy * res.zw;
}

void main() {
  vec2 uv = get_uv();
  frag = texture2D(offtex, uv);
}
