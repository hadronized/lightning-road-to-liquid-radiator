#version 400

layout (triangles, equal_spacing, ccw) in;

in vec3 tpos[];
in vec3 tno[];

out vec3 pos;

uniform mat4 proj;

vec3 interpolate3D(vec3 a, vec3 b, vec3 c) {
  return a*gl_TessCoord.x + b*gl_TessCoord.y + c*gl_TessCoord.z;
}

void main() {
  pos = interpolate3D(tpos[0], tpos[1], tpos[2]);
  //pos /= length(pos);
  gl_Position = proj * vec4(pos, 1.);
}
