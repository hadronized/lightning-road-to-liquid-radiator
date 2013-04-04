#version 130

in vec3 co;
out vec3 pos;
out vec3 no;

uniform float time;
uniform mat4 proj;

void main() {
  /* around Z */
  vec3 coZ = co;
  coZ.x = co.x*cos(time)-co.y*sin(time);
  coZ.y = co.x*sin(time)+co.y*cos(time);
  /* around Y */
  vec3 coYZ = coZ;
  coYZ.x = coZ.x*cos(time)+coZ.z*sin(time);
  coYZ.z = -coZ.x*sin(time)+coZ.z*cos(time);
  /* around X */
  vec3 coXYZ = coYZ;
  coXYZ.y = coYZ.y*sin(time)+coYZ.z*cos(time);
  coXYZ.z = coYZ.y*cos(time)-coYZ.z*sin(time);

  no = normalize(coXYZ);
  pos = coXYZ;
  //coXYZ.z -= max(100.-time*100., 6.);
  coXYZ.z -= 2.;

  gl_Position = proj * vec4(coXYZ, 1.0);
}

