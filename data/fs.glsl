#version 130

precision highp float;

uniform float time;
uniform vec2 resolution;

vec2 getUV() {
  vec2 uv = vec2(1. - 2. * gl_FragCoord.x / resolution.x,
                 1. - 2. * gl_FragCoord.y / resolution.y);
  uv.x *= (resolution.x / resolution.y);
  return uv;
}
 
float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
  
float plasma(vec2 uv) {
  return
    sin(uv.x*6.-time) + sin(uv.y*8.)
  + sin((uv.x+uv.y)*8.+time)
  + sin(length(uv)*4.+time)
  + sin(uv.x*uv.y*8.+time)
  + sin(distance(uv, vec2(sin(time),cos(time)))*5.+time);
}
   
void main() {
  vec2 uv = getUV();
  float scanline = mod(gl_FragCoord.y, 2.0);
  //gl_FragColor = scanline * vec4(1.-plasma(uv)/3., 0.5-plasma(uv), plasma(uv)*sin(time), 1.);
}

