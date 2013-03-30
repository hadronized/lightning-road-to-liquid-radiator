#version 130

out vec4 frag;

uniform sampler2D offtex;
uniform float off_factor;

vec2 computeUV() {
  vec2 uv = gl_FragCoord.xy;
  uv.x /= off_factor;
  uv.y /= off_factor;
  
  return uv;
}

void main() {
  frag = vec4(texture2D(offtex, computeUV()));
} 
