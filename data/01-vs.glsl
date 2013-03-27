#version 130

in vec3 co;

uniform vec2 res;
uniform float time;

void main() {
  gl_Position = vec4(co, 1.);
}
