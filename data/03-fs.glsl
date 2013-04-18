#version 130

#define RAY_STEP 0.1

uniform float time;
uniform vec2 res;

out vec4 frag;

float PI = 3.14159265359;
float fovy = PI/2.;
const float znear = 0.;
const float zfar = 100.;

vec2 get_uv() {
  vec2 uv = 2. * gl_FragCoord.xy / res.xy - 1.;
  uv.y /= res.x/res.y;
  return uv;
}

float rand(vec2 co){
  return fract(sin(dot(co,vec2(12.9898,78.233))) * 43758.5453);
}

float plasma(vec2 uv) {
  return
      sin(uv.x*8.+time) * sin(uv.y*8.)
    + sin(length(vec2(sin(uv.x+PI/2.), sin(uv.y)))*24.+time)
    + sin(uv.y*12.)
    ;
}

float heightmap(vec2 xz) {
  return sin(xz.x+time)*sin(xz.y)/2.;
}

float intersect_terrain(vec3 cam, vec3 ray) {
  vec3 p;
  for (float s = znear, d = 0.; s <= zfar; s += (RAY_STEP+d)) {
    p = cam + ray*s;
    if (p.y <= plasma(p.xz/20.)) { /* intersects with the terrain */
      return s;
    }
    d = distance(p,cam)*0.005;
  }
  return 0.;
}



void main() {
  vec2 uv = get_uv();
  vec3 ray = normalize(vec3(uv.x, uv.y-0.8, -1. / tan(fovy/2.)));
  vec3 cam = vec3(0., 12., -time*4.);
  float terrain = intersect_terrain(cam, ray);
  vec3 lpos = vec3(0., 8., 0.);

  if (terrain != 0.) {
    vec3 hit = cam + ray*terrain;
    vec3 no = vec3(0., 1., 0.);
    float pl = plasma(hit.xz/20.);

    frag = vec4(pl/2., 0.5 - pl/3., 0.5 + pl/2., 1.);
    frag *= vec4(hit.y*0.5);
  } else {
    frag = vec4(0.);
  }
#if 0
  float pl = plasma(uv);
  frag = vec4(pl, 0.5 - pl/3., 0.5 + pl/2.*sin(time), 1.);
#endif
}
