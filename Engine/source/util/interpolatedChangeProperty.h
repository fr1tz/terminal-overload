// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _INTERPOLATEDCHANGEPROPERTY_H_
#define _INTERPOLATEDCHANGEPROPERTY_H_

#ifndef _SIM_H_
#include "console/sim.h"
#endif

#ifndef _MEASE_H_
#include "math/mEase.h"
#endif

#ifndef _TIMESOURCE_H_
#include "core/util/timeSource.h"
#endif



/// A property that smoothly transitions to new values instead of assuming
/// them right away.
///
/// @param T Value type.  Must have "interpolate( from, to, factor )" method.
/// @param TimeSource Time source to which interpolation is synchronized.
template< typename T, class TimeSource = GenericTimeSource< SimMSTimer > >
class InterpolatedChangeProperty
{
   public:

      enum
      {
         /// Default time (in milliseconds) to go from one value
         /// to a new one.
         DEFAULT_TRANSITION_TIME = 2000
      };

      typedef TimeSource TimeSourceType;
      typedef typename TimeSource::TickType TimeType;

   protected:

      /// The current value.
      mutable T mCurrentValue;

      /// @name Transitioning
      ///
      /// Transitioning allows to smoothly go from one value to
      /// a different one over a period of time.
      ///
      /// @{

      ///
      TimeSourceType mTimeSource;

      /// Number of milliseconds it takes to go from one value
      /// to a different one.
      TimeType mBlendPhaseTime;

      /// Interpolation to use for going from source to target.
      EaseF mTransitionCurve;

      /// The time the transition started.  If 0, no transition is in progress.
      mutable TimeType mTransitionStartTime;

      /// The value we are transitioning from.
      T mSourceValue;

      /// The value we are transitioning to.
      T mTargetValue;

      /// @}

      /// Update #mCurrentValue.
      void _update() const;

   public:

      ///
      InterpolatedChangeProperty( const T& initialValue = T() )
         :  mCurrentValue( initialValue ),
            mTargetValue( initialValue ),
            mBlendPhaseTime( DEFAULT_TRANSITION_TIME ),
            mTransitionStartTime( 0 )
      {
         // By default, start time source right away.
         mTimeSource.start();
      }

      /// Get the current value.  If a transition is in progress, this will be
      /// an interpolation of the last value and the new one.
      const T& getCurrentValue() const
      {
         _update();
         return mCurrentValue;
      }

      /// Set the interpolation to use for going from one ambient color to
      /// a different one.
      void setTransitionCurve( const EaseF& ease ) { mTransitionCurve = ease; }

      /// Set the amount of time it takes to go from one ambient color to
      /// a different one.
      void setTransitionTime( TimeType time ) { mBlendPhaseTime = time; }

      /// Set the desired value.  If this differs from the current value,
      /// a smooth blend to the given color will be initiated.
      ///
      /// @param value Desired value.
      void setTargetValue( const T& value );

      /// Return the time source to which interpolation synchronizes.
      const TimeSourceType& geTimeSource() const { return mTimeSource; }
      TimeSourceType& getTimeSource() { return mTimeSource; }
};


//-----------------------------------------------------------------------------

template< typename T, typename TimeSource >
void InterpolatedChangeProperty< T, TimeSource >::setTargetValue( const T& value )
{
   if( mTargetValue == value )
      return;

   if( mBlendPhaseTime == 0 )
   {
      mTargetValue = value;
      mCurrentValue = value;
   }
   else
   {
      // Set the source value to the current value (which may be interpolated)
      // and then start a transition to the given target.

      mSourceValue = getCurrentValue();
      mTargetValue = value;
      mTransitionStartTime = mTimeSource.getPosition();
   }
}

//-----------------------------------------------------------------------------

template< typename T, typename TimeSource >
void InterpolatedChangeProperty< T, TimeSource >::_update() const
{
   // Nothing to do if no transition in progress.

   if( !mTransitionStartTime )
      return;

   // See if we have finished the transition.

   TimeType deltaTime = mTimeSource.getPosition() - mTransitionStartTime;
   if( deltaTime >= mBlendPhaseTime )
   {
      // We're done.
      mCurrentValue = mTargetValue;
      mTransitionStartTime = 0;

      return;
   }

   // Determine the interpolated value.

   F32 blendFactor = F32( deltaTime ) / F32( mBlendPhaseTime );
   blendFactor = mTransitionCurve.getUnitValue( blendFactor );

   mCurrentValue.interpolate( mSourceValue, mTargetValue, blendFactor );
}

#endif // !_INTERPOLATEDCHANGEPROPERTY_H_
