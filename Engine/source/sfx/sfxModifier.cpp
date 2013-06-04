// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/sfxModifier.h"
#include "sfx/sfxSource.h"


//=============================================================================
//    SFXOneShotModifier.
//=============================================================================

//-----------------------------------------------------------------------------

SFXOneShotModifier::SFXOneShotModifier( SFXSource* source, F32 triggerPos, bool removeWhenDone )
   : Parent( source, removeWhenDone ),
     mTriggerPos( triggerPos )
{
}

//-----------------------------------------------------------------------------

bool SFXOneShotModifier::update()
{
   if( mSource->getElapsedPlayTimeCurrentCycle() >= mTriggerPos )
   {
      _onTrigger();
      return mRemoveWhenDone;
   }
   else
      return true;
}

//=============================================================================
//    SFXRangeModifier.
//=============================================================================

//-----------------------------------------------------------------------------

SFXRangeModifier::SFXRangeModifier( SFXSource* source, F32 startTime, F32 endTime, bool removeWhenDone )
   : Parent( source, removeWhenDone ),
     mStartTime( startTime ),
     mEndTime( endTime ),
     mIsActive( false )
{
}

//-----------------------------------------------------------------------------

bool SFXRangeModifier::update()
{
   if( !isActive() )
   {
      SFXStatus status = mSource->getStatus();
      if( ( status == SFXStatusPlaying || status == SFXStatusBlocked )
          && mSource->getElapsedPlayTimeCurrentCycle() >= mStartTime )
      {
         mIsActive = true;
         _onStart();
      }
   }
   
   if( isActive() )
      _onUpdate();
      
   if( isActive() )
   {
      SFXStatus status = mSource->getStatus();
      if( ( status == SFXStatusPlaying || status == SFXStatusBlocked )
          && mSource->getElapsedPlayTimeCurrentCycle() > mEndTime )
      {
         _onEnd();
         mIsActive = false;
         
         return mRemoveWhenDone;
      }
   }
   
   return true;
}

//=============================================================================
//    SFXFadeModifier.
//=============================================================================

//-----------------------------------------------------------------------------

SFXFadeModifier::SFXFadeModifier( SFXSource* source, F32 time, F32 endVolume, F32 startTime, EOnEnd onEndDo, bool removeWhenDone )
   : Parent( source, startTime, startTime + time, removeWhenDone ),
     mEndVolume( endVolume ),
     mOnEnd( onEndDo )
{
   
}

//-----------------------------------------------------------------------------

SFXFadeModifier::~SFXFadeModifier()
{
   // If the fade is still ongoing, restore the source's volume.
   // For fade-in, set to end volume.  For fade-out, set to start volume.
   
   if( isActive() )
   {
      if( mStartVolume > mEndVolume )
         mSource->setVolume( mStartVolume );
      else
         mSource->setVolume( mEndVolume );
   }
}

//-----------------------------------------------------------------------------

void SFXFadeModifier::_onStart()
{
   mStartVolume = mSource->getVolume();
   mCurrentVolume = mStartVolume;
}

//-----------------------------------------------------------------------------

void SFXFadeModifier::_onUpdate()
{
   F32 multiplier = ( mSource->getElapsedPlayTimeCurrentCycle() - mStartTime ) / ( mEndTime - mStartTime );

   F32 newVolume;
   if( mStartVolume > mEndVolume )
      newVolume = mStartVolume - ( ( mStartVolume - mEndVolume ) * multiplier );
   else
      newVolume = mStartVolume + ( ( mEndVolume - mStartVolume ) * multiplier );
      
   if( newVolume != mCurrentVolume )
   {
      mCurrentVolume = newVolume;
      mSource->setVolume( mCurrentVolume );
   }
}

//-----------------------------------------------------------------------------

void SFXFadeModifier::_onEnd()
{
   mSource->setVolume( mEndVolume );
   
   switch( mOnEnd )
   {
      case ON_END_Pause:
         mSource->pause( 0.f ); // Pause without fade.
         break;
         
      case ON_END_Stop:
         mSource->stop( 0.f ); // Stop without fade.
         break;
         
      case ON_END_Nop: ;
   }
}

//=============================================================================
//    SFXMarkerModifier.
//=============================================================================

//-----------------------------------------------------------------------------

SFXMarkerModifier::SFXMarkerModifier( SFXSource* source, const String& name, F32 pos, bool removeWhenDone )
   : Parent( source, pos, removeWhenDone ),
     mMarkerName( name )
{
}

//-----------------------------------------------------------------------------

void SFXMarkerModifier::_onTrigger()
{
   Con::executef( mSource, "onMarkerPassed", mMarkerName.c_str() );
}
