#include "text_writer.hpp"

namespace {
  char const *FONT_NAME = "-bitstream-charter-medium-r-normal--30-*-*-*-*-*-*-*-*";
}

text_writer_c::text_writer_c( ) {
}

text_writer_c::~text_writer_c() {
}

void text_writer_c::init(Display *pDisp) {
  /* load the font */
  _font = XLoadFont(pDisp, FONT_NAME);
  /* get the Graphic Context */
  //_pmap = XCreatePixmap(pDisp, win, 
}

void text_writer_c::destroy(Display *pDisp) {
  /* unload the font */
  XUnloadFont(pDisp, _font);
}
