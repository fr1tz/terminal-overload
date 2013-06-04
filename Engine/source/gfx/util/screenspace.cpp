// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gfx/util/screenspace.h"

// The conversion from screen space to the render target
// is made more complex because screen space is relative
// to the viewport.
void ScreenSpace::RenderTargetParameters(const Point3I &targetSize, const RectI &targetViewport, Point4F &rtParams)
{
   // Top->Down
   Point2F targetOffset(   (F32)targetViewport.point.x / (F32)targetSize.x,
                           (F32)targetViewport.point.y / (F32)targetSize.y );

   // Bottom->Up
   //Point2F targetOffset(   (F32)targetViewport.point.x / (F32)targetSize.x,
   //                        ( (F32)targetSize.y - (F32)(targetViewport.point.y + targetViewport.extent.y ) ) / (F32)targetSize.y );


   // Get the scale to convert from the 
   // screen space to the target size.
   Point2F targetScale( (F32)targetViewport.extent.x / (F32)targetSize.x,
                        (F32)targetViewport.extent.y / (F32)targetSize.y );

   // Get the target half pixel size.
   const Point2F halfPixel( 0.5f / targetSize.x,
                            0.5f / targetSize.y );

   rtParams.set( targetOffset.x + halfPixel.x,
                 targetOffset.y + halfPixel.y,
                 targetScale.x,
                 targetScale.y );
}