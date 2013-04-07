#version 130

out vec4 frag;

uniform sampler2D offtex;
uniform float time;

vec2 computeUV() {
  float f = max(1., min(80., 160. - time*40.));
  vec2 uv = vec2(floor(gl_FragCoord.x / f) / (800./f), floor(gl_FragCoord.y / f) / (600./f));
  
  return uv;
}

void main() {
  vec2 uv = computeUV();
  float l = (1. - uv.xy
  frag = vec4(texture2D(offtex, uv)) * l;
} 
