#include <iostream>
#include "common.hpp"
#include "bootstrap.hpp"
#include "gl.hpp"

using namespace std;

bootstrap_c::bootstrap_c() :
  _mod0(nullptr) {
  GLubyte const *glstr;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);
  cout << "init SDL" << endl;

  glstr = glGetString(GL_VERSION);
  cout << "OpenGL Version String: " << glstr << endl;
}

bootstrap_c::~bootstrap_c() {
  delete _mod0;
  delete _mod1;
  SDL_Quit();
}

void bootstrap_c::init() {
  _mod0 = new mod0_c;
  _mod1 = new mod1_c;
  glEnable(GL_DEPTH_TEST);
}

void bootstrap_c::run() {
  SDL_Event event;
  float time = 0.f;

  while (treat_events(event)) {
    _mod0->render(time);
    //_mod1->render(time);
    SDL_GL_SwapBuffers();
    time += 0.001f;
  }
}

bool bootstrap_c::treat_events(SDL_Event &event) {
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

  return true;
}

