#ifndef __CUBE_VS_HPP
#define __CUBE_VS_HPP

char const *SHD_CUBE_VS =
"#version 330 core\n"
"in vec3 co;"
"out vec3 gpos;"
"uniform float time;"
"void main(){"
  "float t=time/2.;"
  "vec3 coZ=co;"
  "coZ.x=co.x*cos(t)-co.y*sin(t);"
  "coZ.y=co.x*sin(t)+co.y*cos(t);"
  "vec3 coYZ=coZ;"
  "coYZ.x=coZ.x*cos(t)+coZ.z*sin(t);"
  "coYZ.z=-coZ.x*sin(t)+coZ.z*cos(t);"
  "vec3 coXYZ=coYZ;"
  "coXYZ.y=coYZ.y*sin(t)+coYZ.z*cos(t);"
  "coXYZ.z=coYZ.y*cos(t)-coYZ.z*sin(t);"
  "gpos=coXYZ;"
"}";

#endif /* guard */

