// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TSELECTION_H_
#define _TSELECTION_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif


template <class T>
class Selection : public Vector<T>
{
public:

   // Use explicit specialization to define these for your type.
   MatrixF getOrientation() { return MatrixF(); }
   Point3F getOrigin() { return Point3F(); }
   Point3F getScale() { return Point3F(); }

   void offset( const Point3F &delta );
   void rotate( const EulerF &delta );
   void scale( const Point3F &delta );

protected:
   
   // Use explicit specialization to define these for your type.
   virtual void offsetObject( T &object, const Point3F &delta ) {}
   virtual void rotateObject( T &object, const EulerF &delta, const Point3F &origin ) {}
   virtual void scaleObject( T &object, const Point3F &delta ) {}

protected:

   //Point3F        mCentroid;
   //Point3F        mBoxCentroid;
   //Box3F          mBoxBounds;
   //bool           mCentroidValid;
};


template<class T> inline void Selection<T>::offset( const Point3F &delta )
{
   typename Selection<T>::iterator itr = this->begin();

   for ( ; itr != this->end(); itr++ )   
      offsetObject( *itr, delta );      
}

template<class T> inline void Selection<T>::rotate( const EulerF &delta )
{
   typename Selection<T>::iterator itr = this->begin();
   Point3F origin = getOrigin();

   for ( ; itr != this->end(); itr++ )   
      rotateObject( *itr, delta, origin );
}

template<class T> inline void Selection<T>::scale( const Point3F &delta )
{
   // Can only scale a single selection.
   if ( this->size() != 1 )
      return;

   scaleObject( this->mArray[0], delta );   
}

#endif // _TSELECTION_H_