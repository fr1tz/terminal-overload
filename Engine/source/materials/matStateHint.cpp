// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "materials/matStateHint.h"

#include "materials/processedMaterial.h"


const MatStateHint MatStateHint::Default( "Default" );

void MatStateHint::init( const ProcessedMaterial *mat )
{
   PROFILE_SCOPE( MatStateHint_init );

   mState.clear();
   
   // Write the material identifier so that we batch by material
   // specific data like diffuse color and parallax scale.
   //
   // NOTE: This doesn't actually cause more draw calls, but it 
   // can cause some extra unnessasary material setup when materials
   // are different by their properties are the same.
   //
   const Material *material = mat->getMaterial();
   mState += String::ToString( "Material: '%s', %d\n", material->getName(), material->getId() );
   
   // Go thru each pass and write its state into
   // the string in the most compact but uniquely
   // identifiable way.
   U32 passes = mat->getNumPasses();
   for ( U32 i=0; i < passes; i++ )
      mState += mat->getPass( i )->describeSelf();

   // Finally intern the state string for
   // fast pointer comparisions.
   mState = mState.intern();
}




