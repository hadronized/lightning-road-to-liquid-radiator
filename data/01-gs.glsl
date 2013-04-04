#version 150

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3[] gpos;
out vec3 pos;
out vec3 no;

uniform mat4 proj;

void emit_triangle(vec3 a, vec3 b, vec3 c) {
  gl_Position = vec4(a, 1.);
  pos = a;
  no = normalize(a);
  EmitVertex();
  gl_Position = vec4(b, 1.);
  pos = b;
  no = normalize(b);
  EmitVertex();
  gl_Position = vec4(c, 1.);
  pos = c;
  no = normalize(c);
  EmitVertex();
  EndPrimitive();
}

void tess_triangle(vec3 a, vec3 b, vec3 c, int n) {
  float gap = 1. / pow(2., n);
  vec3 l1 = normalize(c-a)*gap;
  vec3 l2 = nomalize(b-c)*gap;
  vec3 a2 = a;

  for (int i = 0; ;) {
    a2
    for (int j = 0; ;) {

    }
  }
}

void main() {
  /*
  for (int i = 0; i < 3; ++i) {
    gl_Position = proj * vec4(vec3(gpos[i].xy, gpos[i].z-2.), 1.);
    pos = gpos[i];
    no = normalize(gpos[i]);
    EmitVertex();
  }
  */
  tess_triangle(gpos[0], gpos[1], gpos[2], 1);
}
