#version 330

out vec4 frag;

uniform sampler2D offtex;
uniform vec4 res;
uniform float time;

vec2 get_uv() {
  return gl_FragCoord.xy * res.zw;
}

void main() {
  vec2 uv = get_uv();
  vec2 step2 = res.zw / mod(max(0.01, time - 54.8732), 13.7150);
  frag = vec4(
    texture2D(offtex, uv).r,
    texture2D(offtex, vec2(uv.x+step2.y, uv.y)).g,
    texture2D(offtex, vec2(uv.x, uv.y+step2.y)).b,
    1.);
}
