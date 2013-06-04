// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TVECTORSPEC_H_
#define _TVECTORSPEC_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

// Not exactly a specialization, just a vector to use when speed is a concern
template<class T>
class FastVector : public Vector<T>
{
public:
   // This method was re-written to prevent load-hit-stores during the simple-case.
   void push_back_noresize(const T &x)
   {
#ifdef TORQUE_DEBUG
      AssertFatal(Vector<T>::mElementCount < Vector<T>::mArraySize, "use of push_back_noresize requires that you reserve enough space in the FastVector");
#endif
      Vector<T>::mArray[Vector<T>::mElementCount++] = x;
   }
};

#endif //_TVECTORSPEC_H_

