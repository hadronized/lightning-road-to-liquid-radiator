#version 130

in vec3 co;
uniform mat4 projection;
uniform mat4 view;

void main() {
  //gl_Position = projection * view * vec4(co, 1.f);
  gl_Position = vec4(co, 1.f);
}
