// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MRANDOMSET_H_
#define _MRANDOMSET_H_

#ifndef _MRANDOM_H_
#include "math/mRandom.h"
#endif

template <class T>
class MRandomSet
{
protected:

   MRandomLCG *mRandGen;

   Vector<T> mItems;
   Vector<F32> mProbability;
   F32 mSum;

public:

   MRandomSet( MRandomLCG *randGen = &gRandGen );

   void add( const T &item, F32 probability );
   
   /// Return a random item from the set using the specified per
   /// item probability distribution.
   T get();
};

template<class T>
inline MRandomSet<T>::MRandomSet( MRandomLCG *randGen )
 : mRandGen( randGen ),
   mSum( 0.0f )
{
}

template<class T> 
inline void MRandomSet<T>::add( const T &item, F32 probability )
{
   AssertFatal( probability > 0.0f, "MRandomDeck - item probability must be positive." );

   mItems.push_back( item );
   mProbability.push_back( probability );
   mSum += probability;
}

template<class T> 
inline T MRandomSet<T>::get()
{ 
   AssertFatal( mSum > 0.0f, "MRandomDeck - no items to get." );

   F32 rand = mRandGen->randF(0.0f, mSum);

   F32 prev = -1.0f;
   F32 curr = 0.0f;

   for ( S32 i = 0; i < mItems.size(); i++ )
   {
      curr += mProbability[i];

      if ( rand > prev && rand <= curr )
         return mItems[i];
         
      prev = curr;
   }
   
   AssertFatal( false, "MRandomSet::get() has failed." );
   return NULL;
}

#endif //_MRANDOMSET_H_
