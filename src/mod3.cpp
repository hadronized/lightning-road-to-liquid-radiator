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
  char str = 31;
  _writer.start_draw();
  _writer.draw_string(&str, 0.f, 0.f, 0.05f);
  _writer.end_draw();
}
