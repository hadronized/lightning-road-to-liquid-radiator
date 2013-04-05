#ifndef __BOOTSTRAP_HPP
#define __BOOTSTRAP_HPP

#include <SDL/SDL.h>

class bootstrap_c {
  /* all the mods go here */

public :
  bootstrap_c();
  ~bootstrap_c();

  bool treat_events(SDL_Event &event);
  void init();
  void run();
};

#endif /* guard */

