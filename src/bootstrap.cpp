#include "common.hpp"
#include "bootstrap.hpp"

bootstrap_c::bootstrap_c() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_OPENGL);
}

bootstrap_c::~bootstrap_c() {
  SDL_Quit();
}

void bootstrap_c::init() {
}

void bootstrap_c::run() {
  SDL_Event event;

  while (treat_events(event)) {
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

