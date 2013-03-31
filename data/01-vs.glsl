#version 130

in vec3 co;
out vec3 ico;

uniform float time;
uniform mat4 proj;

float PI = 3.14159265359;
float rad30 = 30.*PI/180.;

void main() {
  /* around Z */
  vec3 coZ = co;
  coZ.x = co.x*cos(time)-co.y*sin(time);
  coZ.y = co.x*sin(time)+co.y*cos(time);
  /* around Y */
  vec3 coYZ = coZ;
  coYZ.x = coZ.x*cos(time)-coZ.y*sin(time);
  coYZ.z = coZ.x*sin(time)+coZ.y*cos(time);
  /* around X */
  vec3 coXYZ = coYZ;
  coXYZ.y = coYZ.x*sin(time)+coYZ.y*cos(time);
  coXYZ.z = coYZ.x*cos(time)-coYZ.y*sin(time);

  coXYZ.z -= 2.;


  gl_Position = proj * vec4(coXYZ, 1.0);
}

