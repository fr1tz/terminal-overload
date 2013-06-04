// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/*
** The contents of this file are subject to the GLX Public License Version 1.0
** (the "License"). You may not use this file except in compliance with the
** License. You may obtain a copy of the License at Silicon Graphics, Inc.,
** attn: Legal Services, 2011 N. Shoreline Blvd., Mountain View, CA 94043
** or at http://www.sgi.com/software/opensource/glx/license.html.
**
** Software distributed under the License is distributed on an "AS IS"
** basis. ALL WARRANTIES ARE DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY
** IMPLIED WARRANTIES OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR
** PURPOSE OR OF NON- INFRINGEMENT. See the License for the specific
** language governing rights and limitations under the License.
**
** The Original Software is GLX version 1.2 source code, released February,
** 1999. The developer of the Original Software is Silicon Graphics, Inc.
** Those portions of the Subject Software created by Silicon Graphics, Inc.
** are Copyright (c) 1991-9 Silicon Graphics, Inc. All Rights Reserved.
*/

#ifndef GFX_GLX_H
#define GFX_GLX_H

#ifndef GFX_GGL_H
   #include "../ggl.h"
#endif

#include "platform/tmm_off.h"

// AGL includes the standard gl defs, which we already provide in ggl.h
// Defining __gl_h_ here prevents osx's gl defs from being included.
#define __gl_h_
#include <Agl/agl.h>

#include "platform/tmm_on.h"

namespace GL
{

//-----------------------------------------------------------------------------
#ifndef DOXYGEN

#define GLX_VERSION_1_0 1

#define GLX_USE_GL 1
#define GLX_BUFFER_SIZE 2
#define GLX_LEVEL 3
#define GLX_RGBA 4
#define GLX_DOUBLEBUFFER 5
#define GLX_STEREO 6
#define GLX_AUX_BUFFERS 7
#define GLX_RED_SIZE 8
#define GLX_GREEN_SIZE 9
#define GLX_BLUE_SIZE 10
#define GLX_ALPHA_SIZE 11
#define GLX_DEPTH_SIZE 12
#define GLX_STENCIL_SIZE 13
#define GLX_ACCUM_RED_SIZE 14
#define GLX_ACCUM_GREEN_SIZE 15
#define GLX_ACCUM_BLUE_SIZE 16
#define GLX_ACCUM_ALPHA_SIZE 17
#define GLX_BAD_SCREEN 1
#define GLX_BAD_ATTRIBUTE 2
#define GLX_NO_EXTENSION 3
#define GLX_BAD_VISUAL 4
#define GLX_BAD_CONTEXT 5
#define GLX_BAD_VALUE 6
#define GLX_BAD_ENUM 7


//-----------------------------------------------------------------------------
// Extensions use indirection in order to support multiple contexts

struct AGLExtensionPtrs: public GLExtensionPtrs {
};

struct AGLExtensionFlags: public GLExtensionFlags {
};

#endif // Doxygen

//-----------------------------------------------------------------------------

#undef XGL_FUNCPTR
#define XGL_FUNCPTR(name) (((AGLExtensionPtrs*)GL::_GGLptr)->_##name)

} // Namespace
#endif

