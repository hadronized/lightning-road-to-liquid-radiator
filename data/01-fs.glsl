#version 130

uniform float time;

out vec4 frag;
    
void main() {
  float scanline = mod(gl_FragCoord.y, 2.0);
  frag = vec4(1., 1., 1., 1.);
}

