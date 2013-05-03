#version 330

out vec4 frag;

uniform vec4 res;
uniform sampler2D offtex;

vec2 get_uv() {
  return gl_FragCoord.xy * res.zw;
}

void main() {
  vec2 uv = get_uv();
  float step = res.z*1.5;
  frag = texture2D(offtex, vec2(uv.x-step*6., uv.y)) * 0.05
       + texture2D(offtex, vec2(uv.x-step*2., uv.y)) * 0.10
       + texture2D(offtex, vec2(uv.x-step, uv.y)) * 0.25
       + texture2D(offtex, vec2(uv.x, uv.y)) * 0.5
       + texture2D(offtex, vec2(uv.x+step, uv.y)) * 0.25
       + texture2D(offtex, vec2(uv.x+step*2., uv.y)) * 0.10
       + texture2D(offtex, vec2(uv.x+step*6., uv.y)) * 0.05
       ;
  frag += texture2D(offtex, vec2(uv.x, uv.y-step*6.)) * 0.05
        + texture2D(offtex, vec2(uv.x, uv.y-step*2.)) * 0.10
        + texture2D(offtex, vec2(uv.x, uv.y-step)) * 0.25
        + texture2D(offtex, vec2(uv.x, uv.y)) * 0.5
        + texture2D(offtex, vec2(uv.x, uv.y+step)) * 0.25
        + texture2D(offtex, vec2(uv.x, uv.y+step*2.)) * 0.10
        + texture2D(offtex, vec2(uv.x, uv.y+step*6.)) * 0.05
        ;
  frag *= 0.5;
}
