// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PALETTE_H_
#define _PALETTE_H_

#ifndef _COLOR_H_
#include "core/color.h"
#endif

struct Palette
{
   // Constants
   enum 
	{
      NumSlots = 16
	};

   ColorI colors[NumSlots];

	static Palette active;
};

#endif // _PALETTE_H_