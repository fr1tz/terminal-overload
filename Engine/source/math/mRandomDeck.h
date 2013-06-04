// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MRANDOMDECK_H_
#define _MRANDOMDECK_H_

#ifndef _MRANDOM_H_
#include "math/mRandom.h"
#endif

template <class T>
class MRandomDeck
{
protected:

   MRandomLCG *mRandGen;

   Vector<T> mDeck;

   Vector<T> mPile;

public:

   MRandomDeck( MRandomLCG *randGen = &gRandGen );

   void addToPile( const T &item );

   void addToPile( const Vector<T> &items );

   void shuffle();

   S32 draw( T *item, bool reshuffle = true );

   void removeAll( Vector<T> *outItems );

};

template<class T>
inline MRandomDeck<T>::MRandomDeck( MRandomLCG *randGen )
   : mRandGen( randGen )
{
}

template<class T> 
inline void MRandomDeck<T>::shuffle()
{
   // Move everything to the pile.
   mPile.merge( mDeck );

   if ( mPile.empty() )
      return;
   T& last = mPile.last();
   mDeck.clear();

   // Randomly draw from the pile
   // and place them in the deck.
   while ( !mPile.empty() )
   {
      U32 i = mRandGen->randI( 0, mPile.size() - 1 );
      mDeck.push_back( mPile[i] );
      mPile.erase_fast( i );
   }

   // Make sure that the first drawn item
   // is not the same as the last drawn item.
   if ( mDeck.last() == last )
   {
      mDeck.pop_back();
      mDeck.push_front( last );
   }
}

template<class T> 
inline S32 MRandomDeck<T>::draw( T *item, bool reshuffle )
{ 
   if ( mDeck.size() == 0 )
   {
      if ( mPile.size() == 0 )
         return -1;
      
      if ( reshuffle )
         shuffle();
      else
         return -1;
   }

   *item = mDeck.last();
   mPile.push_back( *item );
   mDeck.pop_back();   

   return mDeck.size();
}

template<class T>
inline void MRandomDeck<T>::addToPile( const T &item )
{
   mPile.push_back( item );
}

template<class T>
inline void MRandomDeck<T>::addToPile( const Vector<T> &items )
{
   mPile.merge( items );
}

template<class T>
inline void MRandomDeck<T>::removeAll( Vector<T> *outItems )
{
   if ( outItems )
   {
      outItems->merge( mPile );
      outItems->merge( mDeck );
   }

   mPile.clear();
   mDeck.clear();
}

#endif //_MRANDOMDECK_H_
