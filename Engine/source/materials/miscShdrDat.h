// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _MISCSHDRDAT_H_
#define _MISCSHDRDAT_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif

//**************************************************************************
// This file is an attempt to keep certain classes from having to know about
//   the ShaderGen class
//**************************************************************************


//-----------------------------------------------------------------------
// Enums
//-----------------------------------------------------------------------
enum RegisterType
{
   RT_POSITION = 0,
   RT_NORMAL,
   RT_BINORMAL,
   RT_TANGENT,
   RT_COLOR,
   RT_TEXCOORD,
   RT_VPOS,
};

enum Components
{
   C_VERT_STRUCT = 0,
   C_CONNECTOR,
   C_VERT_MAIN,
   C_PIX_MAIN,
};

#endif // _MISCSHDRDAT_H_
