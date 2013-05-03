#include "window.hpp"
#include "common.hpp"

namespace {
  char const *TITLE = "-- ENTER NAME OF COMPO HERE --";
  int /* const */ DOUBLE_BUFF_VISUAL[] = {
      GLX_RGBA
    , GLX_DEPTH_SIZE, 24
    , GLX_DOUBLEBUFFER
    , None
  };
//    {'r','g','b','a','_','i','n','t','r','o',0}
}
window_c::window_c(unsigned width, unsigned height, bool full) {
  XVisualInfo *pVI;
  Colormap cmap;
  XSetWindowAttributes winAttr;
  char const *argv[] = { TITLE, 0 };

  _pDisp = XOpenDisplay(nullptr);
  if (!_pDisp)
    throw std::runtime_error("X failed to open display");

  /* make sure GLX is supported */
  if (!glXQueryExtension(_pDisp, nullptr, nullptr))
    throw std::runtime_error("GLX not supported");

  pVI = glXChooseVisual(_pDisp, DefaultScreen(_pDisp), DOUBLE_BUFF_VISUAL);
  if (!pVI)
    throw std::runtime_error("GLX failed to choose the visual");

  _cntx = glXCreateContext(_pDisp, pVI, nullptr, GL_TRUE);
  if (!_cntx)
    throw std::runtime_error("GLX failed to create the OpenGL context");

  auto rootwin = RootWindow(_pDisp, pVI->screen);
  cmap = XCreateColormap(_pDisp, rootwin, pVI->visual, AllocNone);

  winAttr.colormap     = cmap;
  winAttr.border_pixel = 0;
  winAttr.event_mask   = ExposureMask           |
    VisibilityChangeMask   |
    KeyPressMask           |
    KeyReleaseMask         |
    //ButtonPressMask        |
    //ButtonReleaseMask      |
    //PointerMotionMask      |
    StructureNotifyMask    |
    SubstructureNotifyMask |
    FocusChangeMask;

  _win = XCreateWindow(_pDisp, rootwin, 0, 0, width, height, 0, pVI->depth, InputOutput, pVI->visual, 
                       CWBorderPixel | CWColormap | CWEventMask, &winAttr );
  if (!_win)
    throw std::runtime_error("X failed to create the window");

  char wclss[] = { 0, 0, 0, full, 'r', 'g', 'b', 'a', '_', 'i', 'n', 't', 'r', 'o', 0 };
  XSetStandardProperties(_pDisp, _win, wclss, wclss, None, const_cast<char**>(argv), 1, NULL);
  glXMakeCurrent(_pDisp, _win, _cntx);

  XMapWindow(_pDisp, _win);
}

window_c::~window_c() {
  XDestroyWindow(_pDisp, _win);
  XCloseDisplay(_pDisp);
}

void window_c::swap_buffers() {
  glXSwapBuffers(_pDisp, _win);
}

Display * window_c::display() {
  return _pDisp;
}
