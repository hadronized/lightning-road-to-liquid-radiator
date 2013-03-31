#version 130

uniform float time;

in vec3 ico;
out vec4 frag;
    
void main() {
  float scanline = mod(gl_FragCoord.y, 2.0);
  frag = vec4(1.f, 1.f, 1.f, 1.f);
}

