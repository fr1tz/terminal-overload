// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SIMOBJECTLIST_H_
#define _SIMOBJECTLIST_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TALGORITHM_H_
#include "core/tAlgorithm.h"
#endif
#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif

// Forward Refs
class SimObject;

/// A vector of SimObjects.
///
/// As this inherits from VectorPtr, it has the full range of vector methods.
class SimObjectList : public VectorPtr<SimObject*>
{
   /// The script callback function for the active sort.
   /// @see scriptSort
   static String smSortScriptCallbackFn;

   /// The script callback comparision callback.
   /// @see scriptSort
   static S32 QSORT_CALLBACK _callbackSort(const void* a,const void* b);

   /// The SimObjectId comparision sort callback.
   /// @see sortId
   static S32 QSORT_CALLBACK _compareId( const void *a, const void *b );
   
public:

   bool pushBack(SimObject*);       ///< Add the SimObject* to the end of the list, unless it's already in the list.
   bool pushBackForce(SimObject*);  ///< Add the SimObject* to the end of the list, moving it there if it's already present in the list.
   bool pushFront(SimObject*);      ///< Add the SimObject* to the start of the list.
   bool remove(SimObject*);         ///< Remove the SimObject* from the list; may disrupt order of the list.

   SimObject* at(S32 index) const {  if(index >= 0 && index < size()) return (*this)[index]; return NULL; }
   
   /// Remove the SimObject* from the list; guaranteed to preserve list order.
   bool removeStable(SimObject* pObject);

   /// Performs a simple sort by SimObjectId.
   void sortId();
   
   /// Performs a sort of the objects in the set using a script
   /// callback function to do the comparision.
   /// @see SimSet::scriptSort
   void scriptSort( const String &scriptCallback );
};

#endif // _SIMOBJECTLIST_H_
