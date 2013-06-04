// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MATSTATEHINT_H_
#define _MATSTATEHINT_H_

#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif

class ProcessedMaterial;


/// A simple object for generating and comparing string based
/// hints used for sorting and identifying materials uniquely
/// by its shaders and states.
class MatStateHint
{
public:

   /// Constructor.
   MatStateHint() {}

   /// Constructor for building special hints.
   MatStateHint( const String &state ) 
	   : mState( state.intern() )
   {
   }

   /// Initialize the state hint from a ProcessMaterial.  This
   /// assumes that the ProcessedMaterial has properly initialized
   /// its passes to describe the material uniquely.
   void init( const ProcessedMaterial *mat );

   /// Clears the hint.
   void clear() { mState.clear(); }

   /// Returns a 32bit hash key used for sorting by material state.
   operator U32() const { return mState.getHashCaseSensitive(); }

   /// Fast comparision of state for equality.
   bool operator ==( const MatStateHint& hint ) const { return mState == hint.mState; }

   /// Fast comparision of state for inequality.
   bool operator !=( const MatStateHint& hint ) const { return mState != hint.mState; }

   /// A default state hint.
   static const MatStateHint Default;

protected:

   /// An interned string of the combined material shader and state info
   /// for evert pass of the processed material.
   String mState;
   
};

#endif // _MATSTATEHINT_H_
