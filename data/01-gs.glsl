#version 150

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3[] gpos;
out vec3 pos;
out vec3 no;

uniform mat4 proj;

void tess_triangle(vec3 a, vec3 b, vec3 c, int depth) {
  vec3 a2 = (a+b) * 0.5;
  vec3 b2 = (b+c) * 0.5;
  vec3 c2 = (a+c) * 0.5;

  if (depth == 1) {
    /* emit the 4 inner triangles */
    gl_Position = vec4(a, 1.); EmitVertex();
    gl_Position = vec4(a2, 1.); EmitVertex();
    gl_Position = vec4(c2, 1.); EmitVertex();
    EndPrimitive();
    gl_Position = vec4(a2, 1.); EmitVertex();
    gl_Position = vec4(b, 1.); EmitVertex();
    gl_Position = vec4(b2, 1.); EmitVertex();
    EndPrimitive();
    gl_Position = vec4(c2, 1.); EmitVertex();
    gl_Position = vec4(b2, 1.); EmitVertex();
    gl_Position = vec4(c, 1.); EmitVertex();
    EndPrimitive();
    gl_Position = vec4(a2, 1.); EmitVertex();
    gl_Position = vec4(b2, 1.); EmitVertex();
    gl_Position = vec4(c2, 1.); EmitVertex();
    EndPrimitive();
  } else {
    /* tessellate the 4 inner virtual triangles */
    int d2 = depth-1;
    tess_triangle(a, a2, c2, d2);
    tess_triangle(a2, b, b2, d2);
    tess_triangle(c2, b2, c, d2);
    tess_triangle(a2, b2, c2, d2);
  }
}

void main() {
  for (int i = 0; i < 3; ++i) {
    gl_Position = proj * vec4(vec3(gpos[i].xy, gpos[i].z-2.), 1.);
    pos = gpos[i];
    no = gno[i];
    EmitVertex();
  }
}
