#version 130

in vec3 co;
out vec3 gpos;

uniform float time;

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

  gpos = coXYZ;
}

