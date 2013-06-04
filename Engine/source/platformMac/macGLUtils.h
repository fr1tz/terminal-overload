// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MACGLUTILS_H_
#define _MACGLUTILS_H_

static Vector<NSOpenGLPixelFormatAttribute> _beginPixelFormatAttributesForDisplay(CGDirectDisplayID display)
{
   Vector<NSOpenGLPixelFormatAttribute> attributes;
   attributes.reserve(16); // Most attribute lists won't exceed this
   
   attributes.push_back(NSOpenGLPFAScreenMask);
   attributes.push_back((NSOpenGLPixelFormatAttribute)CGDisplayIDToOpenGLDisplayMask(display));
   attributes.push_back(NSOpenGLPFANoRecovery);
   attributes.push_back(NSOpenGLPFADoubleBuffer);
   attributes.push_back(NSOpenGLPFAAccelerated);
   attributes.push_back(NSOpenGLPFAAuxBuffers);
   attributes.push_back((NSOpenGLPixelFormatAttribute)1);
   return attributes;
}

static void _addColorAlphaDepthStencilAttributes(Vector<NSOpenGLPixelFormatAttribute>& attributes, U32 color, U32 alpha, U32 depth, U32 stencil)
{
   attributes.push_back(NSOpenGLPFAColorSize);   attributes.push_back((NSOpenGLPixelFormatAttribute)color);
   attributes.push_back(NSOpenGLPFAAlphaSize);   attributes.push_back((NSOpenGLPixelFormatAttribute)alpha);
   attributes.push_back(NSOpenGLPFADepthSize);   attributes.push_back((NSOpenGLPixelFormatAttribute)depth);
   attributes.push_back(NSOpenGLPFAStencilSize); attributes.push_back((NSOpenGLPixelFormatAttribute)stencil);
}

static void _addFullscreenAttributes(Vector<NSOpenGLPixelFormatAttribute>& attributes)
{
   attributes.push_back(NSOpenGLPFAFullScreen);
}

static void _endAttributeList(Vector<NSOpenGLPixelFormatAttribute>& attributes)
{
   attributes.push_back((NSOpenGLPixelFormatAttribute)0);
}

static Vector<NSOpenGLPixelFormatAttribute> _createStandardPixelFormatAttributesForDisplay(CGDirectDisplayID display)
{
   Vector<NSOpenGLPixelFormatAttribute> attributes = _beginPixelFormatAttributesForDisplay(display);
   _addColorAlphaDepthStencilAttributes(attributes, 24, 8, 24, 8);
   _endAttributeList(attributes);
   
   return attributes;
}

/// returns an opengl pixel format suitable for creating shared opengl contexts.
static NSOpenGLPixelFormat* _createStandardPixelFormat()
{
   Vector<NSOpenGLPixelFormatAttribute> attributes = _createStandardPixelFormatAttributesForDisplay(kCGDirectMainDisplay);
 
   NSOpenGLPixelFormat* fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes.address()];

   return fmt;
}

#endif