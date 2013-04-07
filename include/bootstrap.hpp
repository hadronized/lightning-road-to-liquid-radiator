#ifndef __BOOTSTRAP_HPP
#define __BOOTSTRAP_HPP

#include <SDL/SDL.h>
#include "mod0.hpp"
#include "mod1.hpp"

class bootstrap_c {
  /* all the mods go here */
  mod0_c *_mod0;
  mod1_c *_mod1;

public :
  bootstrap_c();
  ~bootstrap_c();

  bool treat_events(SDL_Event &event);
  void init();
  void run();
};

#endif /* guard */
