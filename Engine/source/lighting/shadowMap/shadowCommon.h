// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADOW_COMMON_H_
#define _SHADOW_COMMON_H_

#ifndef _DYNAMIC_CONSOLETYPES_H_
   #include "console/dynamicTypes.h"
#endif


///
enum ShadowType
{   
   ShadowType_None = -1,

   ShadowType_Spot,
   ShadowType_PSSM,

   ShadowType_Paraboloid,
   ShadowType_DualParaboloidSinglePass,
   ShadowType_DualParaboloid,
   ShadowType_CubeMap,

   ShadowType_Count,
};

DefineEnumType( ShadowType );


/// The different shadow filter modes used when rendering 
/// shadowed lights.
/// @see setShadowFilterMode
enum ShadowFilterMode
{
   ShadowFilterMode_None,
   ShadowFilterMode_SoftShadow,
   ShadowFilterMode_SoftShadowHighQuality
};

DefineEnumType( ShadowFilterMode );

#endif // _SHADOW_COMMON_H_
