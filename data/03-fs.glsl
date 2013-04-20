#version 130

#define RAY_STEP 0.01

uniform float time;
uniform vec2 res;

out vec4 frag;

float PI = 3.14159265359;
float fovy = PI/2.;
const float znear = 0.;
const float zfar = 500.;

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
  for (float s = znear, d = 1.; s <= zfar; s += (RAY_STEP*d)) {
    p = cam + ray*s;
    if (p.y <= (plasma(p.xz/20.)-3.)) { /* intersects with the terrain */
      return s;
    }
    d *= 1.01;
  }
  return 0.;
}

float sweep(float d) {
  float a = 80.*(mod(max(0., time - 68.5), 6.825));
  float e = 2.;
  float r = abs(d - a);

  if (r <= e) {
    return e - r;
  } else {
    return 0.;
  }
}

void main() {
  vec2 uv = get_uv();
  vec3 ray = normalize(vec3(uv.x, uv.y-max(0., 0.5*pow(sin((time-54.9)*0.1), 2)), -1. / tan(fovy/2.)));
  vec3 cam = vec3((time-54.9)*5, 4.-sin(time/2.)*4., -(time-54.9)*5.);
  float terrain = intersect_terrain(cam, ray);
  vec3 lpos = vec3(0., 8., 0.);

  if (terrain != 0.) {
    vec3 hit = cam + ray*terrain;
    float pl = plasma(hit.xz/20.);

    frag = vec4(1. - pl/3., 0.5 - pl, pl*-0.85, 1.) * (1. - terrain/zfar);
    frag += vec4(0., 0.5, 1.5 - sin(terrain), 1.) * sweep(distance(hit, vec3(cam.x, 0., cam.z))) * (1. - terrain/zfar)*0.5;
  } else {
    frag = vec4(0.);
  }
}
