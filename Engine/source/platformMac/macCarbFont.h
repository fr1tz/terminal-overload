// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include <ApplicationServices/ApplicationServices.h>
#include "platform/platformFont.h"


class MacCarbFont : public PlatformFont
{
private:
   // Caches style, layout and colorspace data to speed up character drawing.
   // TODO: style colors
   ATSUStyle      mStyle;       
   ATSUTextLayout mLayout;       
   CGColorSpaceRef mColorSpace;
   
   // Cache the baseline and height for the getter methods below.
   U32               mHeight;    // distance between lines
   U32               mBaseline;  // distance from drawing point to typographic baseline,
                                 // think of the drawing point as the upper left corner of a text box.
                                 // note: 'baseline' is synonymous with 'ascent' in Torque.
                                 
   // Cache the size and name requested in create()
   U32               mSize;
   StringTableEntry  mName;
   
public:
   MacCarbFont();
   virtual ~MacCarbFont();
   
   /// Look up the requested font, cache style, layout, colorspace, and some metrics.
   virtual bool create( const char* name, U32 size, U32 charset = TGE_ANSI_CHARSET);
   
   /// Determine if the character requested is a drawable character, or if it should be ignored.
   virtual bool isValidChar( const UTF16 ch) const;
   virtual bool isValidChar( const UTF8 *str) const;
   
   /// Get some vertical data on the font at large. Useful for drawing multiline text, and sizing text boxes.
   virtual U32 getFontHeight() const;
   virtual U32 getFontBaseLine() const;
   
   // Draw the character to a temporary bitmap, and fill the CharInfo with various text metrics.
   virtual PlatformFont::CharInfo &getCharInfo(const UTF16 ch) const;
   virtual PlatformFont::CharInfo &getCharInfo(const UTF8 *str) const;
};

inline U32 MacCarbFont::getFontHeight() const
{
   return mHeight;
}

inline U32 MacCarbFont::getFontBaseLine() const
{
   return mBaseline;
}