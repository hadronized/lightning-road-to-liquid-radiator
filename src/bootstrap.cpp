#include <iostream>
#include "common.hpp"
#include "bootstrap.hpp"

using namespace std;

bootstrap_c::bootstrap_c() :
  _mod0(nullptr) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);
  cout << "init SDL" << endl;
}

bootstrap_c::~bootstrap_c() {
  delete _mod0;

  SDL_Quit();
}

void bootstrap_c::init() {
  _mod0 = new mod0_c;
  glEnable(GL_DEPTH_TEST);
}

void bootstrap_c::run() {
  SDL_Event event;
  float time = 0.f;

  while (treat_events(event)) {
    _mod0->render(time);
    SDL_GL_SwapBuffers();
    time += 0.01f;
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

