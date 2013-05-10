#ifndef __CUBE_PP_FS_HPP
#define __CUBE_PP_FS_HPP

char const *SHD_CUBE_PP_FS =
"#version 330 core\n"
"out vec4 frag;"
"uniform sampler2D offtex;"
"uniform vec4 res;"
"uniform float time;"
"vec2 uv_tex(){"
  "float f=max(1.,min(70.,70.-(time-13.50)*80.));"
  "vec2 uv=vec2(floor(gl_FragCoord.x/f)/(res.x/f),floor(gl_FragCoord.y/f)/(res.y/f));"
  "return uv;"
"}"
"vec2 get_uv(){"
  "vec2 uv=2.*gl_FragCoord.xy*res.zw-1.;"
  "uv.y*=res.y*res.z;"
  "return uv;"
"}"
"void main(){"
  "vec2 uvtex=uv_tex();"
  "vec2 uv=get_uv();"
  "float c=clamp((2.-length(uv))*log((time-22.)/2.),0.,1.);"
  "frag=vec4(texture2D(offtex,uvtex))+vec4(c*1.1,c,c*1.3,1.);"
"}";

#endif /* guard */

