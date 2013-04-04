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
  vec3 lpos = vec3(0., -1., 2.8);
  vec3 ldir = normalize(lpos - pos);
  float d = dot(ldir, no);
  vec3 r = reflect(no, normalize(pos - vec3(0., 0., 2.)));
  float s = pow(max(0., dot(ldir,r)), 3.);
  float pv = plasma();
  float scanline = mod(gl_FragCoord.y, 2.);
  if (time < 10.) { /* phong */
    frag = vec4(1.) * (d+s);
  } else if (time < 14.) { /* blue line swap */
      if (pos.y < (time-12.)) {
        frag = vec4(1. - pv/3, 0.5 - pv, pv*sin(time), 1.) * d;
      } else if (pos.y >= (time-12.) && pos.y <= (time+0.01-12.)) {
        frag = vec4(0., 0.5, 0.33, 1.);
        frag *= scanline;
      } else {
        frag = vec4(1.) * (d+s);
      }
  } else {
    frag = vec4(1. - pv/3, 0.5 - pv, pv*sin(time), 1.) * (d+s);
    frag *= scanline;
  }
}

