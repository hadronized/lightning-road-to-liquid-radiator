#include <iostream>
#include "common.hpp"
#include "mod2.hpp"

using namespace std;

mod2_c::mod2_c(program_c &cubeP, GLuint cube) :
    _stdFS(GL_FRAGMENT_SHADER)
  , _cubeP(cubeP)
  , _cube(cube) {
  _stdFS.source(load_source(STD_LAVA_FS_PATH).c_str());
  _stdFS.compile();
  if (!_stdFS.compiled()) {
    cerr << "STD Lava fragment shader failed to compile:\n" << _stdFS.compile_log() << endl;
    exit(1);
  }
  _stdP.attach(_stdFS);
  _stdP.link();
  if (!_stdP.linked()) {
    cerr << "STD Lava shader program failed to link:\n" << _stdP.link_log() << endl;
    exit(2);
  }

  _init_uniforms();
}

mod2_c::~mod2_c() {
}

void mod2_c::_init_uniforms() {
  /* lava */
  glUseProgram(_stdP.id());
  _stdTimeIndex = _stdP.map_uniform("time");
  _stdRes = _stdP.map_uniform("res");
  _stdFovy = _stdP.map_uniform("fovy");
  glUniform4f(_stdRes, WIDTH, HEIGHT, IWIDTH, IHEIGHT);
  glUniform1f(_stdFovy, FOVY);

  /* cube */
  glUseProgram(_cubeP.id());
  _cubeTimeIndex = _cubeP.map_uniform("time");
}

void mod2_c::render(float time) {
  glDisable(GL_BLEND);
  glUseProgram(_stdP.id());
  glUniform1f(_stdTimeIndex, time);
  glRectf(-1.f, 1.f, 1.f, -1.f);

  if (time >= 109.7) { /* WOOUH THAT'S DIRTY! DO YOU THINK SO, WELL I BETTER NOT SHOW YOU WHERE’S THE LIMONADE IS MADE, SWEET LIMONADE */
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glUseProgram(_cubeP.id());
    glUniform1f(_cubeTimeIndex, time);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(_cube);
    glDrawElements(GL_PATCHES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}
