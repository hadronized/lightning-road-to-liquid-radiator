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

float plasma(vec2 uv) {
  return
    + sin(uv.x*10.+time) + sin(uv.y*10.)
    + sin(length(uv)*16.) + sin(distance(uv, vec2(cos(time), sin(time)))*1.8)
    + sin((uv.x*uv.y)*30.)
    ;
}

float heightmap(vec2 xz) {
  return sin(xz.x+time)*sin(xz.y)/2.;
}

float intersect_terrain(vec3 cam, vec3 ray) {
  vec3 p;
  for (float s = znear; s <= zfar; s += RAY_STEP) {
    p = cam + ray*s;
    if (p.y <= plasma(p.xz/vec2(60., 30.))) { /* intersects with the terrain */
      return s;
    }
    //d = distance(p,cam)*0.1;
  }
  return 0.;
}



void main() {
  vec2 uv = get_uv();
  vec3 ray = normalize(vec3(uv.x, uv.y-0.5, -1. / tan(fovy/2.)));
  vec3 cam = vec3(0., 8., -time*10.);
  float terrain = intersect_terrain(cam, ray);
  vec3 lpos = vec3(0., 20., 0.);

  if (terrain != 0.) {
    vec3 hit = cam + ray*terrain;
    vec3 no = vec3(0., 1., 0.);
    float pl = plasma(hit.xz);
    //frag = vec4(pl, 2. - pl, 1.5 + pl/2.*sin(time), 1.);// * dot(no,normalize(lpos - hit)) * 1. / sqrt(distance(cam,hit));
    frag = vec4(hit.x+hit.y, hit.x/2.+hit.y, 0.5*hit.y, 1.) / sqrt(distance(cam, hit));
  } else {
    frag = vec4(0.);
  }
}
