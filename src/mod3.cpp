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

  /* :: greetings */
  _writer.draw_string(":: greetings ::", -0.4f, std::min(0.9f, t-1.f), h+0.03f);
  _writer.draw_string("xtrium, XT95, rez, latortue, sam", std::min(-0.6f, t-3.f), 0.8f, h);
  _writer.draw_string("zerkman, maracuja, piark, hellflip", std::max(-0.64f, -t+2.f), 0.7f, h);
  //_writer.draw_string(//"

  _writer.end_draw();
}
