// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// X11 gl functions
GL_GROUP_BEGIN(ARB_glx)
GL_FUNCTION(glXQueryExtension, Bool, (Display *dpy, int *errorBase, int *eventBase))
GL_FUNCTION(glXQueryVersion, Bool, (Display *dpy, int *major, int *minor))
GL_FUNCTION(glXGetConfig, int, (Display *dpy, XVisualInfo *vis, int attrib, int *value))
GL_FUNCTION(glXChooseVisual, XVisualInfo*, (Display *dpy, int screen, int *attribList))
GL_FUNCTION(glXCreateGLXPixmap, GLXPixmap, (Display *dpy, XVisualInfo *vis, Pixmap pixmap))
GL_FUNCTION(glXDestroyGLXPixmap, void, (Display *dpy, GLXPixmap pix))
GL_FUNCTION(glXCreateContext, GLXContext, (Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct))
GL_FUNCTION(glXDestroyContext, void, (Display *dpy, GLXContext ctx))
GL_FUNCTION(glXIsDirect, Bool, (Display *dpy, GLXContext ctx))
GL_FUNCTION(glXCopyContext, void, (Display *dpy, GLXContext src, GLXContext dst, GLuint mask))
GL_FUNCTION(glXMakeCurrent, Bool, (Display *dpy, GLXDrawable drawable, GLXContext ctx))
GL_FUNCTION(glXGetCurrentContext, GLXContext, (void))
GL_FUNCTION(glXGetCurrentDrawable, GLXDrawable, (void))
GL_FUNCTION(glXWaitGL, void, (void))
GL_FUNCTION(glXWaitX, void, (void))
GL_FUNCTION(glXSwapBuffers, void, (Display *dpy, GLXDrawable drawable))
GL_FUNCTION(glXUseXFont, void, (Font font, int first, int count, int listBase))
GL_GROUP_END()

