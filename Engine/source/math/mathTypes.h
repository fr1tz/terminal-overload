// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MATHTYPES_H_
#define _MATHTYPES_H_

#ifndef _DYNAMIC_CONSOLETYPES_H_
   #include "console/dynamicTypes.h"
#endif


void RegisterMathFunctions(void);


class Point2I;
class Point2F;
class Point3I;
class Point3F;
class Point4F;
class RectI;
class RectF;
class MatrixF;
class Box3F;
class EaseF;
class AngAxisF;
class TransformF;


DECLARE_SCOPE( MathTypes );


DECLARE_STRUCT( Point2I );
DECLARE_STRUCT( Point2F );
DECLARE_STRUCT( Point3I );
DECLARE_STRUCT( Point3F );
DECLARE_STRUCT( Point4F );
DECLARE_STRUCT( RectI );
DECLARE_STRUCT( RectF );
DECLARE_STRUCT( MatrixF );
DECLARE_STRUCT( AngAxisF );
DECLARE_STRUCT( TransformF );
DECLARE_STRUCT( Box3F );
DECLARE_STRUCT( EaseF );


// Legacy console types.
DefineConsoleType( TypePoint2I, Point2I )
DefineConsoleType( TypePoint2F, Point2F )
DefineConsoleType( TypePoint3I, Point3I )
DefineConsoleType( TypePoint3F, Point3F )
DefineConsoleType( TypePoint4F, Point4F )
DefineConsoleType( TypeRectI, RectI )
DefineConsoleType( TypeRectF, RectF )
DefineConsoleType( TypeMatrixF, MatrixF )
DefineConsoleType( TypeMatrixPosition, MatrixF)
DefineConsoleType( TypeMatrixRotation, MatrixF )
DefineConsoleType( TypeAngAxisF, AngAxisF )
DefineConsoleType( TypeTransformF, TransformF )
DefineConsoleType( TypeBox3F, Box3F )
DefineConsoleType( TypeEaseF, EaseF )


#endif
