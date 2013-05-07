#include "common.hpp"
#include "mod3.hpp"
#include <cmath>

/* shader sources */
#include "data/final-fs.hpp"

using namespace std;

mod3_c::mod3_c() {
}

mod3_c::~mod3_c() {
}

void mod3_c::render(float time) {
  float const h = 0.05f;

  float t = time - 137.2f;
  _writer.start_draw();

  if (time < 150.9f) {
    /* :: greetings */
    _writer.draw_string(":: greetings ::", -0.45f, std::min(0.2f, t-1.f), h+0.03f);
    _writer.draw_string("xtrium, XT95, rez, latortue, sam", std::min(-0.6f, t-3.f), 0.1f, h);
    _writer.draw_string("zerkman, maracuja, piark, hellflip", std::max(-0.64f, -t+2.f), 0.f, h);
    _writer.draw_string("den, fra, Mooz, LLB, titeiko, stfsux", std::min(-0.67f, t-2.f), -0.1f, h);
    _writer.draw_string("all #demofr sceners! ...", -0.45f, std::max(-0.2f, -t+3.f), h);
    _writer.draw_string("... and everyone at Outline!", -0.95f, std::max(-0.4f, -4.f*(t-5.f)), h+0.04f);
  } else {
    _writer.draw_string("Ligthning Road To Liquid Radiator", -0.9f, 0.f, h+0.02f);
    _writer.draw_string("Outline 2013\n"
                        "May 9th-12th\n"
                        "Eersel, North Brabant, The Netherlands",
                        -0.9f, -0.8f, h);
  }

  _writer.end_draw();
}
