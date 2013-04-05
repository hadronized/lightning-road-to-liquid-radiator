#include <iostream>
#include "mod0.hpp"

using namespace std;

mod0::mod0() :
  _stdVS(GL_VERTEX_SHADER),
  _stdGS(GL_GEOMETRY_SHADER),
  _stdFS(GL_FRAGMENT_SHADER),
  _ppFS(GL_FRAGMENT_SHADER) {
  /* std program */
  _stdVS.source(load_source(STD_VS_PATH).c_str());
  _stdVS.compile();
  if (!_stdVS.compiled()) {
    cerr << "mod0 STD Vertex shader failed to compile:\n" << _stdVS.compile_log() << endl;
    exit(1);
  }
  _stdGS.source(load_source(STD_GS_PATH).c_str());
  _stdGS.compile();
  if (!_stdGS.compiled()) {
    cerr << "mod0 STD Geometry shader failed to compile:\n" << _stdGS.compile_log() << endl;
    exit(1);
  }
  _stdFS.source(load_source(STD_FS_PATH).c_str());
  _stdFS.compile();
  if (!_stdFS.compiled()) {
    cerr << "mod0 STD Fragment shader failed to compile:\n" << _stdFS.compile_log() << endl;
    exit(1);
  }
  _stdP.attach(_stdVS);
  _stdP.attach(_stdGS);
  _stdP.attach(_stdFS);
  _stdP.link();
  if (!_stdP.linked()) {
    cerr << "mod0 Program failed to link:\n" << _stdP.link_log() << endl;
    exit(2);
  }

  /* post-process program */
  _ppFS.source(load_source(PP_FS_PATH).c_str());
  _ppFS.compile();
  if (!_ppFS.compiled()) {
    cerr << "PP Fragment shader failed to compile:\n" << _ppFS.compile_log() << endl;
    exit(1);
  }
  _ppP.attach(_ppFS);
  _ppP.link();
  if (!_ppP.linked()) {
    cerr << "PP Program failed to link:\n" << _ppP.link_log() << endl;
    exit(2);
  }

  /* offscreen */
  _gen_offscreen_tex();
}

mod0::~mod0() {
}

void mod0::_gen_offscreen_tex() {
  glGenTextures(1, &_offtex);
  glBindTexture(GL_TEXTURE_2D, off);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void mod0::_gen_rdbf() {
  glGenRenderbuffers(1, &_rdbf);
  glBindRenderbuffer(GL_RENDERBUFFER, _rdbf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void mod0::_gen_framebuffer() {
  glGenFramebuffers(1, &_fbo);
}

void mod0::_setup_offscreen() {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rdbf);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _offtex, 0);
  
  auto ok = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
  switch (ok) {
    case GL_FRAMEBUFFER_COMPLETE :
      cout << "framebuffer complete" << endl;
      break;

    default :
      cerr << "framebuffer incomplete" << endl;
  }
      
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void mod0::_gen_buffers() {
  glGenBuffers(2, _cubeBuffers); /* 0 for VBO, 1 for IBO */
  glBindBuffer(GL_ARRAY_BUFFER, _cubeBuffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _cubeBuffers[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDICES), CUBE_INDICES, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void mod0::_gen_cube() {
  GLint coid;

  coid = stdP.map_uniform("co");
  
  glGenVertexArrays(1, &_cube);
  glBindVertexArray(_cube);
    glEnableVertexAttribArray(coid);
    glBindBuffer(GL_ARRAY_BUFFER, _cubeBuffers[0]);
    glVertexAttribPointer(coid, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _cubeBuffers[1]);
  glBindVertexArray(0);
}

void mod0::_init_uniforms() {
  auto p = gen_perspective(FOVY, RATIO, ZNEAR, ZFAR);

  _projIndex = stdP.map_uniform("proj");
  glUniformMatrix4fv(stdP.id(), 1, GL_FALSE, p._);
  _offtexIndex = ppP.map_uniform("offtex");
  glUniform1i(ppP.id(), 0);
  _stdTimeIndex = stdP.map_uniform("time");
  _ppTimeIndex = ppP.map_uniform("time");
}

void mod0::render(float time) {
  /* offscreen */
  glUseProgram(_stdP.id());
  glUniform1f(_stdTimeIndex, time);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindVertexArray(_cube);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  /* post-process */
  glUseProgram(ppP.id());
  glUniform1i(texIndex, 0); /* TODO: do that earlier */
  glUniform1f(_ppTimeIndex, time);
  glBindTexture(GL_TEXTURE_2D, _offtex);
  glRectf(-1.f, 1.f, 1.f, -1.f);
  glUseProgram(0); /* end of frame */
}

