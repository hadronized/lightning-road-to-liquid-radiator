#version 130

uniform float time;

in vec3 pos;
out vec4 frag;

float plasma() {
  return
    + sin((pos.x+pos.y)*4.)
    + sin(length(pos)*18+time*8.)
    + sin(pos.z*pos.y*8.)
    + sin(pos.x*pos.z*8.)
    + sin(distance(pos, vec3(cos(time)*2., -0.5, sin(time)*2.))*8.)
    ;
}

vec3 tex(vec3 uv) {
  float v = sin(length(uv)*4.*time);
  return vec3(v*cos(time), 0.5 + v/2., 1. - v*sin(time));
}


void main() {
  vec3 lpos = vec3(cos(time)*8., sin(time)*8., 8.);
  vec3 no = normalize(pos);
  vec3 ldir = normalize(lpos - pos);
  float d = max(0., dot(ldir, no));

  frag = vec4(tex(pos), 1.) * d;
}

