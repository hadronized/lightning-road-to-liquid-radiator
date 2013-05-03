#ifndef __WINDOW_HPP
#define __WINDOW_HPP

#include <stdexcept>
#include <X11/Xlib.h>
#include <GL/glx.h>

class window_c {
  Display *_pDisp;
  GLXContext _cntx;
  Window _win;

public :
  window_c(unsigned width, unsigned height, bool full);
  ~window_c(void);

  void swap_buffers(void);
  Display * display(void);
};

#endif /* guard */

