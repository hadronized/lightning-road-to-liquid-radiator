#ifndef __GL_HPP
#define __GL_HPP

#ifdef __linux__ /* linux platform */
#  include <GL/gl.h>
#  include <GL/glext.h>
#else /* win32 */
#endif

/* ==================
 *  OPENGL EXTENSION
 * ================== */
extern PFNGLPATCHPARAMETERIPROC glPatchParameteriARB;

#endif /* guard */

