#ifndef __BOOTSTRAP_HPP
#define __BOOTSTRAP_HPP

#include <SDL/SDL.h>
#include <fmodex/fmod.h>
#include "mod0.hpp"
#include "mod1.hpp"
#include "mod2.hpp"

class bootstrap_c {
  /* all the mods go here */
  mod0_c *_mod0;
  mod1_c *_mod1;
  mod2_c *_mod2;

  /* soft synth go here */
  FMOD_SYSTEM *_sndsys;
  FMOD_SOUND *_track;
  FMOD_CHANNEL *_chan;

  float _track_cursor();
  float _track_length();
  void _advance_track(float t);

public :
  bootstrap_c();
  ~bootstrap_c();

  bool treat_events(SDL_Event &event);
  void init();
  void run();
};

#endif /* guard */

