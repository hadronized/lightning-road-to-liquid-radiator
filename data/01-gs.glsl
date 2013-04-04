#version 150

layout(triangles) in;
layout(triangle_strip, max_vertices = 146) out;

in vec3[] gpos;
out vec3 pos;

uniform mat4 proj;

void tess_triangle(vec3 a, vec3 b, vec3 c, int n) {
  int l = int(pow(2, n));
  float gap = 1. / float(l);
  vec3 l1 = (c-a)*gap;
  vec3 l2 = (b-c)*gap;
  vec3 a2 = a;
  vec3 t;

  for (int i = 0; i < l; ++i) {
    a2 = a + l1*i;
    for (int j = 0; j <= i; a2 += l2, ++j) {
      t = normalize(a2); gl_Position = proj * vec4(vec3(t.xy, t.z-1.), 1.); pos = t; EmitVertex();
      t = normalize(a2 + l1); gl_Position = proj * vec4(vec3(t.xy, t.z-1.), 1.); pos = t; EmitVertex();
      t = normalize(a2 + l1 + l2); gl_Position = proj * vec4(vec3(t.xy, t.z-1.), 1.); pos = t; EmitVertex();
      EndPrimitive();
    }
  }

  for (int i = 1; i < l; ++i) {
    a2 = a + l1*i;
    for (int j = 0; j < i; a2 += l2, ++j) {
      t = normalize(a2); gl_Position = proj * vec4(vec3(t.xy, t.z-1.), 1.); pos = t; EmitVertex();
      t = normalize(a2 + l2); gl_Position = proj * vec4(vec3(t.xy, t.z-1.), 1.); pos = t; EmitVertex();
      t = normalize(a2 + l2 + l1); gl_Position = proj * vec4(vec3(t.xy, t.z-1.), 1.); pos = t; EmitVertex();
      EndPrimitive();
    }
  }
}

void main() {
  tess_triangle(gpos[0], gpos[1], gpos[2], 0);
}
