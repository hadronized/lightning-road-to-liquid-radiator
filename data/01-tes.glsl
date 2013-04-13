#version 400

layout (triangles, equal_spacing, ccw) in;

in vec3 tpos[];

out vec3 pos;

uniform mat4 proj;

vec3 interpolate3(vec3 a, vec3 b, vec3 c) {
  return a*gl_TessCoord.x + b*gl_TessCoord.y + c*gl_TessCoord.z;
}

void main() {
  pos = interpolate3(tpos[0], tpos[1], tpos[2]);
  pos = normalize(pos);
  //pos /= length(pos);
  gl_Position = proj * vec4(pos.xy, pos.z-1., 1.);
}
