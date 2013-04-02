#version 130

out vec4 frag;

uniform sampler2D offtex;
uniform float off_factor;

vec2 computeUV() {
  vec2 uv = vec2(gl_FragCoord.x/800./off_factor, gl_FragCoord.y/600./off_factor);
  
  return uv;
}

void main() {
  frag = vec4(texture2D(offtex, computeUV()));
} 
