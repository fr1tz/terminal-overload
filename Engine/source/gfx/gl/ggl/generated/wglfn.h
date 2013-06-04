// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Windows WGL functions
GL_GROUP_BEGIN(ARB_win32)
GL_FUNCTION(wglCopyContext, BOOL, (HGLRC, HGLRC, UINT))
GL_FUNCTION(wglCreateContext, HGLRC, (HDC))
GL_FUNCTION(wglCreateLayerContext, HGLRC, (HDC, GLint))
GL_FUNCTION(wglDeleteContext, BOOL, (HGLRC))
GL_FUNCTION(wglGetCurrentContext, HGLRC, (VOID))
GL_FUNCTION(wglGetCurrentDC, HDC, (VOID))
GL_FUNCTION(wglGetProcAddress, PROC, (LPCSTR))
GL_FUNCTION(wglMakeCurrent, BOOL, (HDC, HGLRC))
GL_FUNCTION(wglShareLists, BOOL, (HGLRC, HGLRC))
GL_FUNCTION(wglDescribeLayerPlane, BOOL, (HDC, GLint, GLint, UINT, LPLAYERPLANEDESCRIPTOR))
GL_FUNCTION(wglSetLayerPaletteEntries, GLint, (HDC, GLint, GLint, GLint, CONST COLORREF *))
GL_FUNCTION(wglGetLayerPaletteEntries, GLint, (HDC, GLint, GLint, GLint, COLORREF *))
GL_FUNCTION(wglRealizeLayerPalette, BOOL, (HDC, GLint, BOOL))
GL_FUNCTION(wglSwapLayerBuffers, BOOL, (HDC, UINT))

// Ascii and Unicode versions
GL_FUNCTION(wglUseFontBitmapsA, BOOL, (HDC, DWORD, DWORD, DWORD))
GL_FUNCTION(wglUseFontOutlinesA, BOOL, (HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, GLint, LPGLYPHMETRICSFLOAT))
GL_FUNCTION(wglUseFontBitmapsW, BOOL, (HDC, DWORD, DWORD, DWORD))
GL_FUNCTION(wglUseFontOutlinesW, BOOL, (HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, GLint, LPGLYPHMETRICSFLOAT))

GL_GROUP_END()

