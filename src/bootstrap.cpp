#include <iostream>
#include "common.hpp"
#include "bootstrap.hpp"
#include "gl.hpp"

using namespace std;

bootstrap_c::bootstrap_c() :
    _pWin(nullptr)
  , _textWriter(nullptr)
  , _mod0(nullptr)
  , _mod1(nullptr)
  , _mod2(nullptr)
  , _mod3(nullptr) {
  GLubyte const *glstr;

  _pWin = new window_c(WIDTH, HEIGHT, FULLSCREEN);
  cout << "init window" << endl;

  glstr = glGetString(GL_VERSION);
  cout << "OpenGL Version String: " << glstr << endl;

  FMOD_System_Create(&_sndsys);
  FMOD_System_Init(_sndsys, 4, FMOD_INIT_NORMAL, NULL);
  cout << "init fmodex" << endl;
}

bootstrap_c::~bootstrap_c() {
  delete _mod0;
  delete _mod1;
  delete _mod2;
  delete _mod3;
  delete _textWriter;
  delete _pWin;
  FMOD_System_Release(_sndsys);
}

float bootstrap_c::_track_cursor() {
  unsigned int i;
  FMOD_Channel_GetPosition(_chan, &i, FMOD_TIMEUNIT_MS);
  return i / 1000.f;
}

float bootstrap_c::_track_length() {
  unsigned int i;
  FMOD_Sound_GetLength(_track, &i, FMOD_TIMEUNIT_MS);
  return i / 1000.f;
}
void bootstrap_c::_advance_track(float t) {
  auto c = _track_cursor();
  FMOD_Channel_SetPosition(_chan, (c+t)*1000,FMOD_TIMEUNIT_MS );
}

void bootstrap_c::init() {
  /* init the lol */
  //_pWin = new window_c(WIDTH, HEIGHT, FULLSCREEN);
  /* init the text writer */
  _textWriter = new text_writer_c;
  /* init the mods */
  _mod0 = new mod0_c(*_textWriter);
  _mod1 = new mod1_c(*_textWriter);
  _mod2 = new mod2_c(*_textWriter, _mod0->cube_program(), _mod0->cube());
  _mod3 = new mod3_c(*_textWriter);
  glEnable(GL_DEPTH_TEST);
  /* init the softsynth */
  FMOD_System_CreateStream(_sndsys, TRACK_PATH.c_str(), FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &_track);
  FMOD_System_PlaySound(_sndsys, FMOD_CHANNEL_FREE, _track, 0, &_chan);
}

void bootstrap_c::run() {
  float time;

  _advance_track(80.0f);
  while ((time = _track_cursor()) <= 159.f && treat_events()) {
    cout << "time: " << time << endl;
    if (time < 27.5f) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _mod0->render(time);
    } else if (time < 54.8732f) {
      _mod1->render(time);
    } else if (time < 137.2f) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _mod2->render(time);
    } else {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _mod3->render(time);
    }
    _pWin->swap_buffers();
  }
}

bool bootstrap_c::treat_events() {
  XEvent event;
  auto disp = _pWin->display();

  while (XPending(disp)) {
    XNextEvent(disp, &event);
    switch (event.type) {
      case KeyPress :
        if (XKeycodeToKeysym(disp, event.xkey.keycode, 0) == XK_Escape)
          return false;
        break;

      case DestroyNotify :
        return false;
        break;

      default :;
    }
  }

  return true;
}

