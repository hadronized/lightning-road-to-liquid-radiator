#version 130

out vec4 frag;

uniform vec2 res;
uniform float time;
uniform float fovy;

float PI = 3.14159265359;

vec2 get_uv() {
  return vec2(2. * gl_FragCoord.x / res.x - 1.,
             (2. * gl_FragCoord.y / res.y - 1.) / (res.x / res.y));
}

vec3 tunnel(vec3 cam, vec3 ray, float r) {
  float a = r / dot(ray, vec3(ray.xy, 0.));
  return vec3(ray.xy, ray.z+cam.z)*a;
}

float inner_tunnel(vec2 uv) {
  return sin(uv.x*18.) + sin(uv.y*18.) + 0.4;
}

float middle_tunnel(vec2 uv) {
  return sin(uv.x*8.) + sin(uv.y*8.) * 0.38;
}

float outer_tunnel(vec2 uv) {
  return clamp(clamp(2. - floor(mod(uv.x, 50.)), 0., 1.)
       + clamp(2. - floor(mod(uv.y, 50.)), 0., 1.), 0., 1.);
}

void main() {
  vec2 uv = get_uv();
  vec3 cam = vec3(0., 0., 1. / tan(fovy/2.));
  vec3 ray = normalize(vec3(uv, 0.) - cam);
  vec3 hit = tunnel(cam, ray, 2.);
  float d = hit.z/100.;
  vec2 lookup = vec2(0.5*acos(dot(ray.xy,vec2(1., 0.))) / PI, hit.z);
  lookup.x *= 10.;
  lookup.y += time;
  frag = vec4(inner_tunnel(lookup));
}
