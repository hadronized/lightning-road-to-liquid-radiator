#version 130

out vec4 frag;

uniform sampler2D offtex;
uniform vec2 res;
uniform float time;

vec2 uv_tex() {
  float f = max(1., min(100., 100. - (time-12.80)*80.));
  vec2 uv = vec2(floor(gl_FragCoord.x / f) / (res.x/f), floor(gl_FragCoord.y / f) / (res.y/f));
  
  return uv;
}

vec2 get_uv() {
  return vec2(2. * gl_FragCoord.x / res.x - 1.,
             (2. * gl_FragCoord.y / res.y - 1.) / (res.x/res.y));
}

void main() {
  vec2 uvtex = uv_tex();
  vec2 uv = get_uv();
  float c = clamp((2. - length(uv))*log((time-22.)/2.), 0., 1.);
  frag = vec4(texture2D(offtex, uvtex)) + vec4(c*1.1, c, c*1.3, 1.);
} 
