
in vec3 co;

uniform vec2 res;
uniform float time;
uniform mat4 proj;

void main() {
  gl_Position = proj * vec4(co, 1.);
}

