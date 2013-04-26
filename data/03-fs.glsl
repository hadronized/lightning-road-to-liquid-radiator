#version 330

#define RAY_STEP 0.1

uniform float time;
uniform vec4 res;

out vec4 frag;

const float PI = 3.14159265359;
const float PI2 = 2.*PI;
const float PI_2 = PI / 2.;
const float fovy = PI_2;
const float zfar = 300.;

vec2 get_uv() {
  vec2 uv = 2. * gl_FragCoord.xy * res.zw - 1.;
  uv.y *= res.y*res.z;
  return uv;
}

float plasma(vec2 uv) {
  return 
      sin(uv.x*8.+time) * sin(uv.y*8.)
    + sin(length(vec2(cos(uv.x), sin(uv.y)))*24.+time)
    + sin(uv.y*12.)
    ;
}

float intersect_terrain(vec3 cam, vec3 ray) {
  vec3 p;
  float znear = cam.y / dot(ray, vec3(0., -1., 0.));

  for (float s = znear, d = 1.; s <= zfar; s += (RAY_STEP*d)) {
    p = cam + ray*s;
    if (p.y <= (plasma(p.xz/20.)-3.)) { /* intersects with the terrain */
      return s;
    }
    d *= 1.008;
  }
  return 0.;
}

float sweep(float d, float dl, float t) { /* d is the sweep distance, dl the time delay and r the thickness of the sweep */
  float a = 80.*(mod(max(0., time - dl), 6.82));
  float r = abs(d - a);
  return max (t - r, 0.);
}

void main() {
  vec2 uv = get_uv();
  float sinstart = time-54.0;
  vec3 ray = normalize(vec3(uv.x, uv.y-max(0., 0.5*pow(sin((sinstart)*0.1), 2)), -1. / tan(fovy/2.)));
  vec3 cam = vec3(sinstart*5., 4.-sin(time/2.)*4., -sinstart*5.);
  float terrain = intersect_terrain(cam, ray);
  vec3 lpos = vec3(0., 8., 0.);
  float v = clamp(1. - pow(length(vec2(uv.x, uv.y/(res.y*res.z))/1.35), 4), 0., 1.);

  if (terrain != 0.) {
    vec3 hit = cam + ray*terrain;
    float sweepDist = terrain;
    float pl = hit.y + 3.;
    
    float atten = 1. - terrain/zfar;
    frag = vec4(1. - pl/3., 0.5 - pl, pl*-0.85, 1.) * atten;
    frag += vec4(0., 0., 2.5, 1.) * (
        sweep(sweepDist, 68.6, 2.)
      + sweep(sweepDist, 72.0071, 6.)
      + sweep(sweepDist, 69., 2)
      + sweep(sweepDist, 69.22, 2.)
      + sweep(sweepDist, 69.8583, 2.)
      + sweep(sweepDist, 69.6683, 2.)
      + sweep(sweepDist, 70.0864, 2.)
      + sweep(sweepDist, 70.9373, 1.)
      + sweep(sweepDist, 71.1557, 1.)
      + sweep(sweepDist, 71.3659, 1.)
      + sweep(sweepDist, 71.5982, 1.)
      ) * pow(atten, 2);
  } else {
    frag = vec4(0.);
  }

  frag *= v;
  //frag = vec4(v);
}
