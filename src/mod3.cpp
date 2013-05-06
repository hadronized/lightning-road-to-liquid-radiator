#include "common.hpp"
#include "mod3.hpp"

/* shader sources */
#include "data/final-fs.hpp"

using namespace std;

mod3_c::mod3_c() :
  _ppFS(GL_FRAGMENT_SHADER) {
  _ppFS.source(SHD_FINAL_FS);
  _ppFS.compile();
  if (!_ppFS.compiled()) {
    cerr << "Final fragment shader failed to compile:\n" << _ppFS.compile_log() << endl;
    exit(1);
  }
  _ppP.attach(_ppFS);
  _ppP.link();
  if (!_ppP.linked()) {
    cerr << "Final program shader failed to link:\n" << _ppP.link_log() << endl;
    exit(2);
  }

  _init_uniforms();
}

mod3_c::~mod3_c() {
}

void mod3_c::_init_uniforms() {
  glUseProgram(_ppP.id());
  auto ppResIndex = _ppP.map_uniform("res");
  auto ppTexIndex = _ppP.map_uniform("tex");
  glUniform2f(ppResIndex, 1.f / GLYPH_WIDTH, 1.f / GLYPH_HEIGHT);
  glUniform1i(ppTexIndex, 0);
}


void mod3_c::render(float) {
  glUseProgram(_ppP.id());
  _writer.draw_string("skypers", -0.25, 0.25, 0.8);
}
