#ifndef __TUNNEL_FS_HPP
#define __TUNNEL_FS_HPP

#include "shader_common.hpp"

std::string const SHD_TUNNEL_FS =
SHD_VERSION_330_CORE +
SHD_OUT_FRAG +
SHD_UNIFORM_RES +
SHD_UNIFORM_TIME +
SHD_PI +
"float fovy = PI/2.;" +
SHD_GET_UV +
"float tunnel(" + SHD_VEC3 + " ray,float r){" +
  SHD_RETURN + " r/(1.+ray.z);" +
"}" +
"float tex(" + SHD_VEC2 + " uv){" +
  SHD_RETURN + " sin(uv.x*PI*8.+time*8.)+sin(uv.y*PI*8.)+0.4;" +
"}" +
SHD_MAIN_FUNC +
  SHD_VEC2 + " uv=get_uv();" +
  SHD_VEC3 + " cam=" + SHD_VEC3 + "(0.,0.,1./tan(fovy/2.));" +
  SHD_VEC3 + " ray=normalize(" + SHD_VEC3 + "(uv,0.)-cam);" +
  "float hit=tunnel(ray,1.);" +
  "float d=hit/100.;" +
  "float pip=(ray.y<0.?-1.:1.);" +
  SHD_VEC2 + " lookup=" + SHD_VEC2 + "(mod(hit*0.01,1.),acos(normalize(pip*ray.xy).x)/PI);" +
  "float atten=max(1.,0.2*hit);" +
  "float f=tex(lookup+vec2(0.,time/5.))/atten;" +
  SHD_FRAG + "=" + SHD_VEC4 + "(f/2.,f*sin(time)/2.,0.,1.)*mod(gl_FragCoord.y,2.);" +
  SHD_FRAG + "+=" + SHD_VEC4 + "(atten/max(0.,20.*(time-27.5)));" +
"}";

#endif /* guard */

