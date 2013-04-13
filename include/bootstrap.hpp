#ifndef __BOOTSTRAP_HPP
#define __BOOTSTRAP_HPP

#include <SDL/SDL.h>
#include <fmodex/fmod.h>
#include "mod0.hpp"
#include "mod1.hpp"

class bootstrap_c {
  /* all the mods go here */
  mod0_c *_mod0;
  mod1_c *_mod1;

  /* soft synth go here */
  FMOD_SYSTEM *_sndsys;
  FMOD_SOUND *_track;
  FMOD_CHANNEL *_chan;

  float _track_cursor();

public :
  bootstrap_c();
  ~bootstrap_c();

  bool treat_events(SDL_Event &event);
  void init();
  void run();
};

#endif /* guard */

