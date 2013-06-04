// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "forest/forestWindAccumulator.h"

#include "forest/forestWindMgr.h"
#include "forest/forestItem.h"
#include "platform/profiler.h"


ForestWindAccumulator::ForestWindAccumulator( const TreePlacementInfo &info )
:  mCurrentStrength( 0.0f )
{
   mCurrentDir.set( 0, 0 );   
   mPosition.set( info.pos );
   mScale = info.scale;

   mDataBlock = info.dataBlock;

   dMemset( &mParticles[0], 0, sizeof( VerletParticle ) );
   dMemset( &mParticles[1], 0, sizeof( VerletParticle ) );
}

ForestWindAccumulator::~ForestWindAccumulator()
{
}

void ForestWindAccumulator::presimulate( const VectorF &windVector, U32 ticks )
{
   PROFILE_SCOPE( ForestWindAccumulator_Presimulate );

   for ( U32 i = 0; i < ticks; i++ )
      updateWind( windVector, TickSec );
}

void ForestWindAccumulator::updateWind( const VectorF &windForce, F32 timeDelta )
{
   PROFILE_SCOPE( ForestWindAccumulator_UpdateWind );

   // Update values from datablock... this way we can
   // change settings live and see instant results.
   const F32 tightnessCoefficient = mDataBlock->mTightnessCoefficient;
   const F32 dampingCoefficient = mDataBlock->mDampingCoefficient;
   const F32 mass = mDataBlock->mMass * mScale;
   const F32 rigidity = mDataBlock->mRigidity * mScale;

   // This will be the accumulated
   // target strength for flutter.
   //F32 targetStrength = windForce.len();

   // This will be the accumulated
   // target displacement vector.
   Point2F target( windForce.x, windForce.y );

   // This particle is the spring target.
   // It has a mass of 0, which we count as
   // an infinite mass.
   mParticles[0].position = target;

   Point2F relVel = target * timeDelta;

   Point2F diff( 0, 0 );
   Point2F springForce( 0, 0 );

   // Spring length is the target
   // particle's position minus the
   // current displacement/direction vector.
   diff = mParticles[0].position - mCurrentDir;

   // F = diff * tightness - v * -damping
   diff *= tightnessCoefficient;
   springForce = diff - ( (mParticles[1].position - mParticles[1].lastPosition) * -dampingCoefficient );

   Point2F accel( 0, 0 );
   accel = springForce * (rigidity * 0.001f) / (mass * 0.001f);

   _updateParticle( &mParticles[1], accel, timeDelta );

   mCurrentDir *= 0.989f;
   mCurrentDir += mParticles[1].position;

   mCurrentStrength += windForce.len() * timeDelta;
   mCurrentStrength *= 0.98f;
}

void ForestWindAccumulator::_updateParticle( VerletParticle *particle, const Point2F &accel, F32 timeDelta )
{
   // Verlet integration:
   // x' = 2x - x* + a * dt^2
   // x' is the new position.
   // x is the current position.
   // x* is the last position.
   // a is the acceleration for this frame.
   // dt is the delta time.
  
   particle->position = ((particle->position * 2.0f) - particle->lastPosition) + accel * (timeDelta * timeDelta);
   particle->lastPosition = particle->position;
}

void ForestWindAccumulator::applyImpulse( const VectorF &impulse )
{
   // First build the current force.
   VectorF force( mCurrentDir.x, mCurrentDir.y, 0 );

   // Add in our mass corrected force.
   const F32 mass = mDataBlock->mMass * mScale;
   force += impulse / mass;

   // Set the new direction and force.
   mCurrentDir.set( force.x, force.y );  
   mCurrentStrength += impulse.len() * TickSec;
}
