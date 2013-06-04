// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXENVIRONMENT_H_
#define _SFXENVIRONMENT_H_

#ifndef _SIMDATABLOCK_H_
   #include "console/simDatablock.h"
#endif
#ifndef _CONSOLETYPES_H_
   #include "console/consoleTypes.h"
#endif
#ifndef _SFXCOMMON_H_
   #include "sfx/sfxCommon.h"
#endif


/// A datablock that defines a reverb environment.
class SFXEnvironment : public SimDataBlock
{
   public:

      typedef SimDataBlock Parent;

   protected:
   
      /// The reverb properties.
      SFXReverbProperties mReverb;

   public:

      SFXEnvironment();
      
      ///
      void validate();
      
      DECLARE_CONOBJECT( SFXEnvironment );
      DECLARE_CATEGORY( "SFX" );
      DECLARE_DESCRIPTION( "A reverb environment." );
      
      static void initPersistFields();

      virtual bool onAdd();
      virtual bool preload( bool server, String& errorStr );
      virtual void packData( BitStream* stream );
      virtual void unpackData( BitStream* stream );
      virtual void inspectPostApply();

      /// @return The reverb properties of the sound environment.
      const SFXReverbProperties& getReverb() const { return mReverb; }
};


#endif // _SFXENVIRONMENT_H_