// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _UTIL_DELEGATE_H_
#define _UTIL_DELEGATE_H_

#include "core/util/FastDelegate.h"

/// @def Delegate
/// The macro which abstracts the details of the delegate implementation.
#define Delegate fastdelegate::FastDelegate

/// @typedef DelegateMemento
/// An opaque structure which can hold an arbitary delegate.
/// @see Delegate
typedef fastdelegate::DelegateMemento DelegateMemento;


template<class T>
class DelegateRemapper : public DelegateMemento
{
public:
   DelegateRemapper() : mOffset(0) {}

   void set(T * t, const DelegateMemento & memento)
   {
      SetMementoFrom(memento);
      if (m_pthis)
         mOffset = ((int)m_pthis) - ((int)t);
   }

   void rethis(T * t)
   {
      if (m_pthis)
         m_pthis = (fastdelegate::detail::GenericClass *)(mOffset + (int)t);
   }

protected:
   S32 mOffset;
};

#endif // _UTIL_DELEGATE_H_