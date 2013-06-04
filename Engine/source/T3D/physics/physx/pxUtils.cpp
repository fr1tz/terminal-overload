// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "T3D/physics/physx/pxUtils.h"

#include "gfx/gfxTransformSaver.h"
#include "gfx/gfxDrawUtil.h"
#include "math/mMatrix.h"
#include "math/mPoint3.h"
#include "T3D/physics/physX/px.h"
#include "T3D/physics/physX/pxCasts.h"

namespace PxUtils {

void drawActor( NxActor *inActor )
{
   GFXDrawUtil *drawer = GFX->getDrawUtil();
   //drawer->setZRead( false );

   // Determine alpha we render shapes with.
   const U8 enabledAlpha = 255;
   const U8 disabledAlpha = 100;
   U8 renderAlpha = inActor->readActorFlag( NX_AF_DISABLE_COLLISION ) ? disabledAlpha : enabledAlpha;

   // Determine color we render actors and shapes with.
   ColorI actorColor( 0, 0, 255, 200 );   
   ColorI shapeColor = ( inActor->isSleeping() ? ColorI( 0, 0, 255, renderAlpha ) : ColorI( 255, 0, 255, renderAlpha ) );      

   MatrixF actorMat(true);
   inActor->getGlobalPose().getRowMajor44( actorMat );

   GFXStateBlockDesc desc;
   desc.setBlend( true );
   desc.setZReadWrite( true, false );
   desc.setCullMode( GFXCullNone );

   // Draw an xfm gizmo for the actor's globalPose...
   //drawer->drawTransform( desc, actorMat, Point3F::One, actorColor );
   
   // Loop through and render all the actor's shapes....

   NxShape *const*pShapeArray = inActor->getShapes();
   U32 numShapes = inActor->getNbShapes();

   for ( U32 i = 0; i < numShapes; i++ )
   {
      const NxShape *shape = pShapeArray[i];

      Point3F shapePos = pxCast<Point3F>( shape->getGlobalPosition() );
      MatrixF shapeMat(true);
      shape->getGlobalPose().getRowMajor44(shapeMat);
      shapeMat.setPosition( Point3F::Zero );

      switch ( shape->getType() )
      {
         case NX_SHAPE_SPHERE:
         {
            NxSphereShape *sphere = (NxSphereShape*)shape;     
            drawer->drawSphere( desc, sphere->getRadius(), shapePos, shapeColor );

            break;
         }
         case NX_SHAPE_BOX:
         {
            NxBoxShape *box = (NxBoxShape*)shape;
            Point3F size = pxCast<Point3F>( box->getDimensions() );            
            drawer->drawCube( desc, size*2, shapePos, shapeColor, &shapeMat );            
            break;
         }
         case NX_SHAPE_CAPSULE:
         {
            shapeMat.mul( MatrixF( EulerF( mDegToRad(90.0f), mDegToRad(90.0f), 0 ) ) );

            NxCapsuleShape *capsule = (NxCapsuleShape*)shape;
            drawer->drawCapsule( desc, shapePos, capsule->getRadius(), capsule->getHeight(), shapeColor, &shapeMat );

            break;
         }
         default:
         {
            break;
         }
      }
   }

   //drawer->clearZDefined();
}

} // namespace PxUtils