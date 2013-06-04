// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FORESTWINDACCUMULATOR_H_
#define _FORESTWINDACCUMULATOR_H_

#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif


struct TreePlacementInfo;
class ForestItemData;


/// This simple class holds the state of the accumulated 
/// wind effect for a single tree.
class ForestWindAccumulator
{
protected:

   struct VerletParticle
   {
      Point2F position;
      Point2F lastPosition;
   };

   F32 mCurrentStrength;
   Point2F mCurrentDir;

   Point3F mPosition;
   F32 mScale;
   ForestItemData *mDataBlock;

   VerletParticle mParticles[2];

   void _updateParticle( VerletParticle *particle, const Point2F &force, F32 timeDelta );

public:

   ForestWindAccumulator( const TreePlacementInfo &info );
   ~ForestWindAccumulator();

   void presimulate( const VectorF &windVector, U32 ticks );

   void updateWind( const VectorF &windVector, F32 timeDelta );

   void setDirection( const VectorF &dir ) { mCurrentDir.set( dir.x, dir.y ); }
   VectorF getDirection() const { return VectorF( mCurrentDir.x, mCurrentDir.y, 0 ); }

   void setStrength( F32 strength ) { mCurrentStrength = strength; }
   F32 getStrength() const { return mCurrentStrength; }

   void setPosition( const Point3F &pos ) { mPosition = pos; }
   Point3F getPosition() const { return mPosition; }

   void applyImpulse( const VectorF &impulse );
};

#endif // _FORESTWINDACCUMULATOR_H_