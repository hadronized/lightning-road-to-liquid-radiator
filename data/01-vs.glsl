#version 130

in vec3 co;
out vec3 ico;

uniform float time;
uniform mat4 proj;

void main() {
  ico = co + vec3(cos(time)*sin(time), sin(time), sin(time));
  ico.z -= 2.;
  gl_Position = proj * vec4(ico, 1.0);
}

