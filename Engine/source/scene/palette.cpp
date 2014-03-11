// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "palette.h"

Palette Palette::active;

void Palette::reset()
{
   for(U32 i = 0; i < NumSlots; i++)
      colors[i].set(255, 255, 255, 255);
}
