#version 130

in vec3 co;
out vec3 ico;

uniform float time;
uniform mat4 proj;

void main() {
  ico = co;
  gl_Position = proj * vec4(co.xy, co.z-2., 1.0);
}

