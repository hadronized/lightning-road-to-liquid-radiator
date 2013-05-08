#ifndef __BOOTSTRAP_HPP
#define __BOOTSTRAP_HPP

#include <fmodex/fmod.h>
#include "window.hpp"
#include "mod0.hpp"
#include "mod1.hpp"
#include "mod2.hpp"
#include "mod3.hpp"
#include "text_writer.hpp"

class bootstrap_c {
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

  /* soft synth go here */
  FMOD_SYSTEM *_sndsys;
  FMOD_SOUND *_track;
  FMOD_CHANNEL *_chan;

  float _track_cursor(void);
  float _track_length(void);
  void _advance_track(float t);

public :
  bootstrap_c(float width, float height, bool full);
  ~bootstrap_c(void);

  bool treat_events(void);
  void init(void);
  void run(void);
};

#endif /* guard */

