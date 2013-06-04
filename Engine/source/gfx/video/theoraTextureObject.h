// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _THEORATEXTUREOBJECT_H_
#define _THEORATEXTUREOBJECT_H_

#ifdef TORQUE_OGGTHEORA

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif

#ifndef _THEORATEXTURE_H_
#include "gfx/video/theoraTexture.h"
#endif

#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif


class SFXDescription;


class TheoraTextureObject : public SimObject
{
   typedef SimObject Parent;

protected:

   /// Is the video currently playing
   bool mIsPlaying;

   /// Should the video loop
   bool mLoop;

   /// The Theora file we should play.
   String mFilename;

   /// Name for the NamedTexTarget.
   String mTexTargetName;

   /// Theora video player backend.
   TheoraTexture mTheoraTexture;

   /// The texture target which can be referenced in materials.
   NamedTexTarget mTexTarget;

   /// Sound description to use for the video's audio channel.
   SFXDescription* mSFXDescription;

   /// Method that is hooked up with the texture target's delegate.
   GFXTextureObject* _texDelegate( U32 index );

public:

   TheoraTextureObject();

   void play();
   void stop() { mTheoraTexture.stop(); mIsPlaying = false; }
   void pause() { mTheoraTexture.pause(); mIsPlaying = false; }

   // SimObject.
   DECLARE_CONOBJECT( TheoraTextureObject );

   virtual bool onAdd();
   virtual void onRemove();

   static void initPersistFields();
};

#endif // TORQUE_OGGTHEORA
#endif // _THEORATEXTUREOBJECT_H_
