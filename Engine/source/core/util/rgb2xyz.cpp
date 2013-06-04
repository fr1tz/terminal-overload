// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "core/util/rgb2xyz.h"

#include "math/mMatrix.h"


namespace ConvertRGB
{

// http://www.w3.org/Graphics/Color/sRGB
static const F32 scRGB2XYZ[] = 
{
   0.4124f,  0.3576f,  0.1805f,  0.0f,
   0.2126f,  0.7152f,  0.0722f,  0.0f,
   0.0193f,  0.1192f,  0.9505f,  0.0f,
   0.0f,     0.0f,     0.0f,     1.0f,
};

static const F32 scXYZ2RGB[] =
{
   3.2410f,  -1.5374f,  -0.4986f, 0.0f,
   -0.9692f, 1.8760f,   0.0416f,  0.0f,
   0.0556f,  -0.2040f,  1.0570f,  0.0f, 
   0.0f,     0.0f,      0.0f,     1.0f,
};

ColorF toXYZ( const ColorF &rgbColor )
{
   const MatrixF &rgb2xyz = *((MatrixF *)scRGB2XYZ);

   ColorF retColor = rgbColor;
   rgb2xyz.mul( *(Point4F *)&retColor );
   return retColor;
}

ColorF fromXYZ( const ColorF &xyzColor )
{
   const MatrixF &xyz2rgb = *((MatrixF *)scXYZ2RGB);

   ColorF retColor = xyzColor;
   xyz2rgb.mul( *(Point4F *)&retColor );
   return retColor;
}

}
