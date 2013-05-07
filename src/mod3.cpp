#include "common.hpp"
#include "mod3.hpp"

/* shader sources */
#include "data/final-fs.hpp"

using namespace std;

mod3_c::mod3_c() {
}

mod3_c::~mod3_c() {
}

void mod3_c::render(float) {
  char const *str = "b j t v x z";
  _writer.start_draw();
  _writer.draw_string(str, -1.f, 0.f, 0.5f);
  _writer.end_draw();
}
