#version 330 core

out vec3 gco;

uniform float time;

float rand(vec2 co){
  return (sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
  int id = 10*gl_VertexID + 1;
  vec3 p = vec3(rand(vec2(id, id*2.)),
                rand(vec2(-id*3., id*5.)),
                rand(vec2(id*7., -id*9.)));
  p = vec3(normalize(p.xy), p.z);
  //p.z = -mod(gl_VertexID-time*3., 50.);
  p.z = mod(-gl_VertexID+(time-27.8), 1.);
  gco = p;
}
