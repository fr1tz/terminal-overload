// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _H_GUIDEFAULTCONTROLRENDER_
#define _H_GUIDEFAULTCONTROLRENDER_

#ifndef _MRECT_H_
#include "math/mRect.h"
#endif

class GuiControlProfile;
class ColorI;

void renderRaisedBox( const RectI &bounds, GuiControlProfile *profile);
void renderSlightlyRaisedBox( const RectI &bounds, GuiControlProfile *profile);
void renderLoweredBox( const RectI &bounds, GuiControlProfile *profile);
void renderSlightlyLoweredBox( const RectI &bounds, GuiControlProfile *profile);
void renderBorder( const RectI &bounds, GuiControlProfile *profile);
void renderFilledBorder( const RectI &bounds, GuiControlProfile *profile );
void renderFilledBorder( const RectI &bounds, const ColorI &borderColor, const ColorI &fillColor, U32 thickness = 1 );
void renderSizableBitmapBordersFilled( const RectI &bounds, S32 baseMultiplier, GuiControlProfile *profile); //  Added
void renderSizableBitmapBordersFilledIndex( const RectI &bounds, S32 startIndex, GuiControlProfile *profile);
void renderFixedBitmapBordersFilled( const RectI &bounds, S32 baseMultiplier, GuiControlProfile *profile); //  Added
void renderFixedBitmapBordersFilled( const RectI &bounds, S32 startIndex, GuiControlProfile *profile);

#endif
