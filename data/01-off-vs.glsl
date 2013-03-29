#version 130

in vec3 co;

void main() {
  gl_Position = vec4(co, 1.);
}

