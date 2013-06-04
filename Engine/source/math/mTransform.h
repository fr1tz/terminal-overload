// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MTRANSFORM_H_
#define _MTRANSFORM_H_

#ifndef _MPOINT3_H_
   #include "math/mPoint3.h"
#endif
#ifndef _MANGAXIS_H_
   #include "math/mAngAxis.h"
#endif
#ifndef _MMATRIX_H_
   #include "math/mMatrix.h"
#endif

/// A transform expressed as a combination of a position vector and an angular
/// orientation.
class TransformF
{
   public:
   
      Point3F mPosition;
      AngAxisF mOrientation;
      bool mHasRotation;

      static const TransformF Identity;

      TransformF()
         :  mPosition( Point3F::Zero ),
            mOrientation( Point3F( 0, 0, 1 ), 0 ),
            mHasRotation(true)
      {
      }

      TransformF( const Point3F& position, const AngAxisF& orientation )
      {
         set( position, orientation );
         mHasRotation = true;
      }

      TransformF( const MatrixF& mat )
      {
         set( mat );
         mHasRotation = true;
      }

      bool hasRotation() const { return mHasRotation; }

      void set( const Point3F& position, const AngAxisF& orientation )
      {
         mPosition = position;
         mOrientation = orientation;
      }

      void set( const MatrixF& mat )
      {
         mPosition = mat.getPosition();
         mOrientation.set( mat );
      }

      /// Return the position vector of the transform.
      const Point3F& getPosition() const { return mPosition; }
      
      /// REturn the orientation of the transform.
      const AngAxisF& getOrientation() const { return mOrientation; }

      MatrixF getMatrix() const
      {
         MatrixF mat;
         mOrientation.setMatrix( &mat );
         mat.setPosition( mPosition );

         return mat;
      }
};

#endif // !_MTRANSFORM_H_
