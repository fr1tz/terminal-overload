// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "ts/tsRenderState.h"


TSRenderState::TSRenderState()
   :  mState( NULL ),
      mCubemap( NULL ),
      mFadeOverride( 1.0f ),
      mNoRenderTranslucent( false ),
      mNoRenderNonTranslucent( false ),
      mMaterialHint( NULL ),
      mCuller( NULL ),
      mLightQuery( NULL ),
      mUseOriginSort( false )
{
}

TSRenderState::TSRenderState( const TSRenderState &state )
   :  mState( state.mState ),
      mCubemap( state.mCubemap ),
      mFadeOverride( state.mFadeOverride ),
      mNoRenderTranslucent( state.mNoRenderTranslucent ),
      mNoRenderNonTranslucent( state.mNoRenderNonTranslucent ),
      mMaterialHint( state.mMaterialHint ),
      mCuller( state.mCuller ),
      mLightQuery( state.mLightQuery ),
      mUseOriginSort( state.mUseOriginSort )
{
}
