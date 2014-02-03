// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENEAMBIENTSOUNDOBJECT_H_
#define _SCENEAMBIENTSOUNDOBJECT_H_

#include "../zones/scenePolyhedralZone.h"

class SFXAmbience;


/// Template mixin to add ability to hold a custom SFXAmbience to
/// a SceneObject.
class SceneAmbientSoundObject : public ScenePolyhedralZone
{
   public:

      typedef ScenePolyhedralZone Parent;

   protected:

      enum
      {
         SoundMask     = Parent::NextFreeMask << 0,   ///< Ambient sound properties have changed.
         NextFreeMask  = Parent::NextFreeMask << 1,
      };

      /// Ambient sound properties for this space.
      SFXAmbience* mSoundAmbience;

   public:

      SceneAmbientSoundObject();

      /// Set the ambient sound properties for the space.
      void setSoundAmbience( SFXAmbience* ambience );

      // SimObject.
      static void initPersistFields();

      // NetObject.
      virtual U32 packUpdate( NetConnection* connection, U32 mask, BitStream* stream );
      virtual void unpackUpdate( NetConnection* connection, BitStream* stream );

      // SceneObject.
      virtual SFXAmbience* getSoundAmbience() const { return mSoundAmbience; }

   private:

      // Console field getters/setters.
      static bool _setSoundAmbience( void* object, const char* index, const char* data );
};

#endif // !_SCENEAMBIENTSOUNDOBJECT_H_
