#include "platform/platformGL.h"
#include "gfx/gl/tGL/tXGL.h"

void PlatformGL::setVSync(const int i)
{
    Display *dpy = glXGetCurrentDisplay();
    GLXDrawable drawable = glXGetCurrentDrawable();
    const int interval = i;

    glXSwapIntervalEXT(dpy, drawable, interval);
}

