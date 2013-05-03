#include <iostream>
#include "common.hpp"
#include "bootstrap.hpp"
#include "gl.hpp"

using namespace std;

bootstrap_c::bootstrap_c() :
  _mod0(nullptr),
  _pWin(nullptr) {
  GLubyte const *glstr;

#if SDL_GL_CONTEXT
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);
  cout << "init SDL" << endl;
#endif
#if GLX_GL_CONTEXT
#endif

  glstr = glGetString(GL_VERSION);
  cout << "OpenGL Version String: " << glstr << endl;

  FMOD_System_Create(&_sndsys);
  FMOD_System_Init(_sndsys, 4, FMOD_INIT_NORMAL, NULL);
  cout << "init fmodex" << endl;
}

bootstrap_c::~bootstrap_c() {
  delete _mod0;
  delete _mod1;
#if SDL_GL_CONTEXT
  SDL_Quit();
#endif
#if GLX_GL_CONTEXT
  delete _pWin;
#endif
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
  /* auto l = _track_length(); */
  /* if(c+i<l) */
  FMOD_Channel_SetPosition(_chan, (c+t)*1000,FMOD_TIMEUNIT_MS );
}

void bootstrap_c::init() {
  /* init the lol */
  _pWin = new window_c(WIDTH, HEIGHT, FULLSCREEN);
  /* init the mods */
  _mod0 = new mod0_c;
  _mod1 = new mod1_c;
  _mod2 = new mod2_c;
  glEnable(GL_DEPTH_TEST); /* TODO: that should be done in the loop, at the beginning of a mod */
  /* init the softsynth */
  FMOD_System_CreateStream(_sndsys, TRACK_PATH.c_str(), FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &_track);
  FMOD_System_PlaySound(_sndsys, FMOD_CHANNEL_FREE, _track, 0, &_chan);
}

void bootstrap_c::run() {
  float time;

  //_advance_track(54.9f);
  while (treat_events()) {
    time = _track_cursor();
    cout << "time: " << time << endl;
    if (time < 27.5f) {
      _mod0->render(time);
    } else if (time < 54.9f) {
      _mod1->render(time);
    } else {
      _mod2->render(time);
    }
#if SDL_GL_CONTEXT
    SDL_GL_SwapBuffers();
#endif
#if GLX_GL_CONTEXT
    _pWin->swap_buffers();
#endif
  }
}

bool bootstrap_c::treat_events() {
#if SDL_GL_CONTEXT
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT :
        return false;

      case SDL_KEYUP :
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE :
            return false;

          default :;
        }
        break;

      default :;
    }
  }
#endif
#if GLX_GL_CONTEXT
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
#endif

  return true;
}

