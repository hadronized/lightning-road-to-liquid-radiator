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
  _writer.start_draw();
  _writer.draw_string("s", 0.f, 0.f, 0.4f);
  _writer.end_draw();
}
