// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXSTATE_H_
#define _SFXSTATE_H_

#ifndef _SIMDATABLOCK_H_
   #include "console/simDatablock.h"
#endif
#ifndef _CONSOLETYPES_H_
   #include "console/consoleTypes.h"
#endif
#ifndef _TVECTOR_H_
   #include "core/util/tVector.h"
#endif
#ifndef _SFXCOMMON_H_
   #include "sfx/sfxCommon.h"
#endif


/// A boolean switch used to modify playlist behavior.
///
class SFXState : public SimDataBlock
{
   public:
   
      typedef SimDataBlock Parent;
      
      enum
      {
         MaxIncludedStates = 4,
         MaxExcludedStates = 4
      };
      
   protected:
   
      /// Reference count for activation.
      U32 mActiveCount;
      
      /// Reference count for disabling.
      U32 mDisableCount;
      
      /// States that will be activated when this state is activated.
      SFXState* mIncludedStates[ MaxIncludedStates ];
   
      /// States that will be disabled when this state is activated.
      SFXState* mExcludedStates[ MaxExcludedStates ];
                  
      /// Call when state has become active.
      void _onActivate();
      
      /// Call when state has gone back to being deactive.
      void _onDeactivate();
      
      /// @name Callbacks
      /// @{
      
      DECLARE_CALLBACK( void, onActivate, () );
      DECLARE_CALLBACK( void, onDeactivate, () );
      
      /// @}
      
   public:
   
      ///
      SFXState();
      
      /// Return true if the state is currently active (activated and not disabled).
      bool isActive() const { return ( !isDisabled() && mActiveCount > 0 ); }
      
      /// Return true if the state is currently disabled.
      bool isDisabled() const { return ( mDisableCount > 0 ); }
      
      /// Activate this state.  activate/deactivate calls balance each other.
      /// Activating a disabled state will not make it active.
      void activate();
      
      ///
      void deactivate();
      
      /// Re-enable this state.
      void enable();
      
      /// Disable this state so that it cannot be activated.  This is used
      /// by state exclusion.
      void disable();
      
      // SimDataBlock.
      virtual bool onAdd();
      virtual bool preload( bool server, String& errorStr );
      virtual void packData( BitStream* stream );
      virtual void unpackData( BitStream* stream );
      
      static void initPersistFields();
   
      DECLARE_CONOBJECT( SFXState );
      DECLARE_CATEGORY( "SFX" );
      DECLARE_DESCRIPTION( "A datablock describing a particular state for the SFX system." );
};

#endif // !_SFXSTATE_H_
