#version 330

in vec3 co;
out vec3 gpos;

uniform float time;

void main() {
  float t = time/2.;
  /* around Z */
  vec3 coZ = co;
  coZ.x = co.x*cos(t)-co.y*sin(t);
  coZ.y = co.x*sin(t)+co.y*cos(t);
  /* around Y */
  vec3 coYZ = coZ;
  coYZ.x = coZ.x*cos(t)+coZ.z*sin(t);
  coYZ.z = -coZ.x*sin(t)+coZ.z*cos(t);
  /* around X */
  vec3 coXYZ = coYZ;
  coXYZ.y = coYZ.y*sin(t)+coYZ.z*cos(t);
  coXYZ.z = coYZ.y*cos(t)-coYZ.z*sin(t);

  gpos = coXYZ;
}

