// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLCARDPROFILE_H
#define _GFXGLCARDPROFILE_H

#include "gfx/gfxCardProfile.h"

/// A note on workarounds - The following settings are used exclusively to work around driver bugs:
/// GL::Workaround::needsExplicitGenerateMipmap
/// GL::Workaround::X1600DepthBufferCopy
/// GL::Workaround::HD2600DepthBufferCopy
/// If you find that you need to work around additional driver bugs, add a new setting
/// of the form GL::Workaround::<name> and set it to false in GFXGLCardProfiler::setupCardCapabilities()
/// Enclose your workaround code in if(GFX->getCardProfiler()->queryProfile("GL::Workaround::<name>")) {
/// <workaround> }
/// Remember to set the work around to true in the card profile script!

class GFXGLCardProfiler : public GFXCardProfiler
{
public:
   void init();

protected:
   virtual const String& getRendererString() const { return mRendererString; }
   virtual void setupCardCapabilities();
   virtual bool _queryCardCap(const String& query, U32& foundResult);
   virtual bool _queryFormat(const GFXFormat fmt, const GFXTextureProfile *profile, bool &inOutAutogenMips);

private:
   String mRendererString;
   typedef GFXCardProfiler Parent;
};

#endif
