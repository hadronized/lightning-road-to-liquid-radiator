#ifndef __LAVA_FS_HPP
#define __LAVA_FS_HPP

#include "shader_common.hpp"

std::string const SHD_LAVA_FS =
SHD_VERSION_330_CORE +
"#define RAY_STEP 0.1\n" +
SHD_UNIFORM_TIME +
SHD_UNIFORM_RES +
SHD_OUT_FRAG +
SHD_PI +
"const float PI2=2.*PI;" +
"const float PI_2=PI/2.;" +
"const float fovy=PI_2;" +
"const float zfar=300.;" +
SHD_GET_UV +
"float plasma(" + SHD_VEC2 + " uv){" +
  SHD_RETURN + " " +
      "sin(uv.x*8.+time)*sin(uv.y*8.)" +
     "+sin(length(vec2(cos(uv.x),sin(uv.y)))*24.+time)" +
     "+sin(uv.y*12.);" +
"}" +
"float intersect_terrain(" + SHD_VEC3 + " cam," + SHD_VEC3 + " ray){" +
  SHD_VEC3 + " p;" +
  "float znear=cam.y/dot(ray," + SHD_VEC3 + "(0.,-1.,0.));" +
  "for (float s=znear,d=1.;s<=zfar;s+=(RAY_STEP*d)){" +
    "p=cam+ray*s;" +
    "if(p.y<=(plasma(p.xz/20.)-3.)){" +
      SHD_RETURN + " s;" +
    "}" +
    "d*=1.008;" +
  "}" +
  SHD_RETURN + " 0.;" +
"}" +
"float sweep(float d,float dl,float t){" +
  "float a=80.*(mod(max(-1.,time-dl),6.82));" +
  "float r=abs(d-a);" +
  SHD_RETURN + " max(t-r,0.);" +
"}" +
SHD_MAIN_FUNC +
  SHD_VEC2 + " uv=get_uv();" +
  "float sinstart=time-54.0;" +
  SHD_VEC3 + " ray=normalize(vec3(uv.x,uv.y-max(0.,0.5*pow(sin((sinstart)*0.1),2)),-1./tan(fovy/2.)));" +
  SHD_VEC3 + " cam=" + SHD_VEC3 + "(sinstart*5.,4.-sin(time/2.)*4.,-sinstart*5.);" +
  "float terrain=intersect_terrain(cam,ray);" +
  SHD_VEC3 + " lpos=" + SHD_VEC3 + "(0.,8.,0.);" +
  "if(terrain!=0.){" +
    SHD_VEC3 + " hit=cam+ray*terrain;" +
    "float sweepDist=terrain;" +
    "float pl=hit.y+3.;" +
    "float atten=1.-terrain/zfar;" +
    SHD_FRAG + "=" + SHD_VEC4 + "(1.-pl/3.,0.5-pl,pl*-0.85, 1.)*atten;" +
    SHD_FRAG + "+=" + SHD_VEC4 + "(0.,0.,2.5,1.)*(" +
        "sweep(sweepDist,68.6,2.)" +
       "+sweep(sweepDist,72.0071,6.)" +
       "+sweep(sweepDist,69.,2)" +
       "+sweep(sweepDist,69.22,2.)" +
       "+sweep(sweepDist,69.8583,2.)" +
       "+sweep(sweepDist,69.6683,2.)" +
       "+sweep(sweepDist,70.0864,2.)" +
       "+sweep(sweepDist,70.9373,1.)" +
       "+sweep(sweepDist,71.1557,1.)" +
       "+sweep(sweepDist,71.3659,1.)" +
       "+sweep(sweepDist,71.5982,1.)" +
      ")*pow(atten,2);" +
  "}else{" +
    SHD_FRAG + "=" + SHD_VEC4 + "(0.);" +
  "}" +
"}";

#endif /* guard */

