#include "common.hpp"
#include "mod3.hpp"
#include <cmath>

/* shader sources */
#include "data/final-fs.hpp"
#include "data/final-colors-fs.hpp"

using namespace std;

mod3_c::mod3_c(float width, float height, text_writer_c &writer) :
    _writer(writer)
  , _plasmaFS(GL_FRAGMENT_SHADER) {
  _init_shader();
  _init_uniforms(width, height);
  _init_offscreen(width, height);
}

mod3_c::~mod3_c() {
}

void mod3_c::_init_offscreen(float width, float height) {
  /* prepare the offscreen texture */
  glGenTextures(1, &_offtex);
  glBindTexture(GL_TEXTURE_2D, _offtex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* prepare the renderbuffer */
  glGenRenderbuffers(1, &_rdbf);
  glBindRenderbuffer(GL_RENDERBUFFER, _rdbf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  /* prepare the FBO */
  glGenFramebuffers(1, &_fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rdbf);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _offtex, 0);

#if DEBUG
    auto ok = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    switch (ok) {
      case GL_FRAMEBUFFER_COMPLETE :
        std::cout << "framebuffer complete" << std::endl;
        break;

      default :
        std::cerr << "framebuffer incomplete" << std::endl;
    }
#endif

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void mod3_c::_init_shader() {
  _plasmaFS.source(SHD_FINAL_COLORS_FS);
  _plasmaFS.compile();
  if (!_plasmaFS.compiled()) {
    std::cerr << "Final colors fragment shader failed to compile\n:" << _plasmaFS.compile_log() << std::endl;
    exit(1);
  }
  _plasmaSP.attach(_plasmaFS);
  _plasmaSP.link();
  if (!_plasmaSP.linked()) {
    std::cerr << "Final colors fragment shader failed to compile:\n" << _plasmaSP.link_log() << std::endl;
    exit(2);
  }
}

void mod3_c::_init_uniforms(float width, float height) {
  glUseProgram(_plasmaSP.id());
  _plasmaTimeIndex = _plasmaSP.map_uniform("time");
  auto plasmaResIndex = _plasmaSP.map_uniform("res");
  auto plasmaTexIndex = _plasmaSP.map_uniform("tex");

  glUniform2f(plasmaResIndex, 1.f/width, 1.f/height);
  glUniform1i(plasmaTexIndex, 0);
}

void mod3_c::render(float time) {
  float const h = 0.05f;

  float t = time - 137.2f;

  /* offscreen */
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _writer.start_draw();
  if (time < 150.5f) {
    /* greetings */
    _writer.draw_string(":: greetings ::", -0.45f, std::min(0.2f, t-1.f), h+0.03f);
    _writer.draw_string("xtrium, XT95, rez, latortue, sam", std::min(-0.6f, t-3.f), 0.1f, h);
    _writer.draw_string("zerkman, maracuja, piark, hellflip", std::max(-0.64f, -t+2.f), 0.f, h);
    _writer.draw_string("den, fra, Mooz, LLB, titeiko, stfsux", std::min(-0.67f, t-2.f), -0.1f, h);
    _writer.draw_string("all #demofr sceners! ...", -0.45f, std::max(-0.2f, -t+3.f), h);
    _writer.draw_string("... and everyone at Outline!", -0.95f, std::max(-0.4f, -4.f*(t-5.f)), h+0.04f);
  } else {
    /* end of the intro */
    _writer.draw_string("Ligthning Road To Liquid Radiator", -0.9f, 0.f, h+0.02f);
    _writer.draw_string("Outline 2013\n"
                        "May 9th-12th\n"
                        "Eersel, North Brabant, The Netherlands",
                        -0.9f, -0.8f, h);
  }
  _writer.end_draw();
  
  /* colored texts */
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, _offtex);
  glUseProgram(_plasmaSP.id());
  glUniform1f(_plasmaTimeIndex, time);
  glRectf(-1., 1.f, 1.f, -1.f);
  glBindTexture(GL_TEXTURE_2D, 0);
}
