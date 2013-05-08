#include <GL/glx.h>
#include "gl.hpp"

/* ==================
 *  OPENGL EXTENSION
 * ================== */
PFNGLPATCHPARAMETERIPROC glPatchParameteriARB = reinterpret_cast<PFNGLPATCHPARAMETERIPROC>(glXGetProcAddress(reinterpret_cast<GLubyte const*>("glPatchParameteri")));


