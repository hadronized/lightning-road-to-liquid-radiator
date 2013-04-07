#version 130

out vec4 frag;

uniform vec2 res;
uniform float time;
uniform float fovy;

vec3 tunnel(vec3 cam, vec3 ray, float r) {
  float a = r / dot(ray, vec3(ray.xy, 0.));
  return vec3(ray.xy, ray.z+cam.z)*a;
}

void main() {
  vec3 cam = vec3(0., 0., 1. / tan(fovy/2.));
  vec3 ray = normalize(vec3(2. * gl_FragCoord.x / res.x - 1.,
                            (2. * gl_FragCoord.y / res.y - 1.) / (res.x / res.y),
                            -cam.z));
  /*
  vec3 hit = tunnel(cam, ray, 2.);
  vec3 hit2 = tunnel(cam, ray, 4.);
  float d = hit.z/100.;
  float c = sin(hit.z*2.+time*2.);
  c *= sin(dot(hit.xy, vec2(0., 1.))*4.);
  if (c <= 0.4) {
    c = sin(hit2.x) * sin(hit2.y) * sin(hit2.z+time);
    frag = vec4(0, c, 0., 1.);
  } else {
    frag = vec4(c, 0., 0., 1.);
  }
  */
  float v = (1.- length(ray.xy))*sin(time)*3.;
  frag = vec4(v, v, v, 1.);
  
}
