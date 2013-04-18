#ifndef __BOOTSTRAP_HPP
#define __BOOTSTRAP_HPP

#if SDL_GL_CONTEXT
#  include <SDL/SDL.h>
#endif
#if GLX_GL_CONTEXT
#  include <X11/Xlib.h>
#  include <GL/glx.h>
#endif
#include <fmodex/fmod.h>
#include "mod0.hpp"
#include "mod1.hpp"
#include "mod2.hpp"

class bootstrap_c {
#if GLX_GL_CONTEXT
  Display *_dpy;
  Window _win;
  GLXContext _glc;
#endif

  /* all the mods go here */
  mod0_c *_mod0;
  mod1_c *_mod1;
  mod2_c *_mod2;

  /* soft synth go here */
  FMOD_SYSTEM *_sndsys;
  FMOD_SOUND *_track;
  FMOD_CHANNEL *_chan;

  float _track_cursor(void);
  float _track_length(void);
  void _advance_track(float t);

public :
  bootstrap_c(void);
  ~bootstrap_c(void);

  bool treat_events(void);
  void init(void);
  void run(void);
};

#endif /* guard */

