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

void main() {
  vec3 lpos = vec3(0., -1., 2.8);
  vec3 no = pos;
  vec3 ldir = normalize(lpos - pos);
  float d = max(0., dot(ldir, no));
  vec3 r = reflect(no, normalize(pos - vec3(0., 0., 2.)));
  float s = pow(max(0., dot(-ldir,r)), 2.);
  float pv = plasma();
  //float scanline = mod(gl_FragCoord.y, 2.);

  frag = vec4(1.) * (d+s);
}

