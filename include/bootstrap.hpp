#ifndef __BOOTSTRAP_HPP
#define __BOOTSTRAP_HPP

#if FMOD_SYNTH
#include <fmodex/fmod.h>
#endif
#include <pthread.h>
#include "window.hpp"
#include "mod0.hpp"
#include "mod1.hpp"
#include "mod2.hpp"
#include "mod3.hpp"
#include "text_writer.hpp"
/* xtrium stuff */
#include "nsd.hpp"
#include "audiodevice.hpp"

class bootstrap_c {
  /* multithreading and so on */
  pthread_t _trackThread;

  /* size */
  float _width;
  float _height;

  window_c *_pWin;

  /* text writer, to write glyphs :) */
  text_writer_c *_textWriter;

  /* all the mods go here */
  mod0_c *_mod0;
  mod1_c *_mod1;
  mod2_c *_mod2;
  mod3_c *_mod3;

#if FMOD_SYNTH
  /* soft synth go here */
  FMOD_SYSTEM *_sndsys;
  FMOD_SOUND *_track;
  FMOD_CHANNEL *_chan;
#endif

  void _init_softsynth(void);
  void _launch_track(void);
  float _track_cursor(void);
#if FMOD_SYNTH
  float _track_length(void);
  void _advance_track(float t);
#endif

public :
  bootstrap_c(float width, float height, bool full);
  ~bootstrap_c(void);

  bool treat_events(void);
  void init(void);
  void run(void);
};

#endif /* guard */

