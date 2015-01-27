// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXTRACK_H_
#define _SFXTRACK_H_

#ifndef _SIMDATABLOCK_H_
   #include "console/simDatablock.h"
#endif
#ifndef _CONSOLETYPES_H_
   #include "console/consoleTypes.h"
#endif


class SFXDescription;


/// A datablock that describes sound data for playback.
class SFXTrack : public SimDataBlock
{
   public:
      
      typedef SimDataBlock Parent;
      
      enum
      {
         /// Maximum numbers of parameters that can be pre-assigned to tracks.
         MaxNumParameters = 8
      };
      
   protected:
   
      /// The description which controls playback settings.
      SFXDescription *mDescription;

      /// Name of the parameters to which sources playing this track should
      /// connect.
      StringTableEntry mParameters[ MaxNumParameters ];
   
      /// Overload this to disable direct instantiation of this class via script 'new'.
      virtual bool processArguments( S32 argc, ConsoleValueRef *argv );

   public:
         
      ///
      SFXTrack();
      
      ///
      SFXTrack( SFXDescription* description );
      
      /// Returns the description object for this sound profile.
      SFXDescription* getDescription() const { return mDescription; }

      ///
      StringTableEntry getParameter( U32 index ) const
      {
         AssertFatal( index < MaxNumParameters, "SFXTrack::getParameter() - index out of range" );
         return mParameters[ index ];
      }
      
      ///
      void setParameter( U32 index, const char* name );
      
      // SimDataBlock.
      virtual void packData( BitStream* stream );
      virtual void unpackData( BitStream* stream );
      virtual bool preload( bool server, String& errorStr );
      virtual bool onAdd();
      virtual void inspectPostApply();
      
      static void initPersistFields();
      
      DECLARE_CONOBJECT( SFXTrack );
      DECLARE_CATEGORY( "SFX" );
      DECLARE_DESCRIPTION( "Abstract base class for any kind of data that can be turned into SFXSources." );
};

#endif // !_SFXTRACK_H_
