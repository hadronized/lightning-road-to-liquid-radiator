#ifndef __TEXT_WRITER_HPP
#define __TEXT_WRITER_HPP

#include <X11/Xlib.h>

class text_writer_c {
  Font _font;
  //GC _gc;
  //Pixmap _pmap;

public :
  text_writer_c(void);
  ~text_writer_c(void);

  void init(Display *pDisp);
  void destroy(Display *pDisp);
};

#endif /* guard */

