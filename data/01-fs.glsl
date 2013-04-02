#version 130

uniform float time;

in vec3 pos;
in vec3 no;
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

void main() {
  vec3 lpos = vec3(0., -2., 2.8);
  vec3 ldir = normalize(lpos - pos);
  float d = dot(ldir, no);
  float pv = plasma();
  float scanline = mod(gl_FragCoord.y, 2.);
  if (time < 10.)
    frag = vec4(1.) * d;
  else
    frag = vec4(1. - pv/3, 0.5 - pv, pv*sin(time), 1.) * d;
  //frag *= scanline;
}

