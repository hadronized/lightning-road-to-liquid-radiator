#version 330 core

out vec3 gco;

uniform float time;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


void main() {
  vec3 p = vec3(rand(vec2(gl_VertexID, gl_VertexID*2.)),
                rand(vec2(gl_VertexID*3., gl_VertexID*5.)),
                rand(vec2(gl_VertexID*7., gl_VertexID*9.)));
  p = normalize(p);
  p.z -= sin(time);
}
