#version 130

uniform float time;

in vec3 pos;
in vec3 no;
out vec4 frag;

void main() {
  vec3 lpos = vec3(0., -2., 2.8);
  float d = dot(normalize(lpos - pos), no);
  frag = d * vec4(1.f);
}

