// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "core/util/rgb2luv.h"

#include "core/util/rgb2xyz.h"
#include "math/mPoint3.h"
#include "math/mPoint2.h"


namespace ConvertRGB
{

ColorF toLUV( const ColorF &rgbColor )
{
   static const Point3F scXYZLUVDot( 1.0f, 15.0f, 3.0f );
   static const Point2F sc49( 4.0f, 9.0f );

   ColorF xyzColor = ConvertRGB::toXYZ( rgbColor );

   const Point2F &xyz_xy = *((Point2F *)&xyzColor);

   Point2F uvColor = sc49;
   uvColor.convolve( xyz_xy );
   uvColor /= mDot( *(Point3F *)&xyzColor, scXYZLUVDot );

   return ColorF( uvColor.x, uvColor.y, xyzColor.green, rgbColor.alpha );
}

ColorF toLUVScaled( const ColorF &rgbColor )
{
   ColorF luvColor = toLUV( rgbColor );
   luvColor.red /= 0.62f;
   luvColor.green /= 0.62f;
   return luvColor;
}

}
