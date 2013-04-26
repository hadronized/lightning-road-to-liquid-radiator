#version 330 core

//out vec3 gco;

uniform float time;
uniform mat4 proj;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

const vec2 data[4] = vec2[] (
  vec2(-1.,  1.),
  vec2(-1., -1.),
  vec2( 1.,  1.),
  vec2( 1., -1.)
);

void main() {
#if 0
  vec3 p = vec3(rand(vec2(gl_VertexID, gl_VertexID*2.)),
                rand(vec2(gl_VertexID*3., gl_VertexID*5.)),
                rand(vec2(gl_VertexID*7., gl_VertexID*9.)));
  p = vec3(normalize(p.xy), p.z);
  p.z = 0.;
  //gco = p;
#endif
  //gl_Position = vec4(p, 1.);
  gl_Position = vec4(data[gl_VertexID+1], 0., 1.);
}
