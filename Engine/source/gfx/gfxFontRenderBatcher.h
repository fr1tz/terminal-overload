// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXFONTBATCHER_H_
#define _GFXFONTBATCHER_H_

#include "core/dataChunker.h"
#include "gfx/gfxDevice.h"
#include "gfx/gFont.h"

#define TEXT_MAG 1

class FontRenderBatcher
{
   struct CharMarker 
   {
      S32 c;
      F32 x;
      GFXVertexColor color; 
      PlatformFont::CharInfo *ci;
   };

   struct SheetMarker
   {
      S32 numChars;
      S32 startVertex;
      CharMarker charIndex[1];
   };

   DataChunker mStorage;
   Vector<SheetMarker *> mSheets;
   GFont *mFont;
   U32 mLength;
   GFXStateBlockRef mFontSB;

   SheetMarker &getSheetMarker(U32 sheetID);

public:
   FontRenderBatcher();

   void init(GFont *font, U32 n);

   void queueChar(UTF16 c, S32 &currentX, GFXVertexColor &currentColor);

   void render(F32 rot, const Point2F &offset );
};

#endif