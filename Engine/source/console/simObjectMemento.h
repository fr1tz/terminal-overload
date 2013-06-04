// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _CONSOLE_SIMOBJECTMEMENTO_H_
#define _CONSOLE_SIMOBJECTMEMENTO_H_

#ifndef _SIM_H_
#include "console/sim.h"
#endif


/// This simple class is used to store an SimObject and 
/// its state so it can be recreated at a later time.
///
/// The success of restoring the object completely depends
/// on the results from SimObject::write().
class SimObjectMemento
{
protected:

   /// The captured object state.
   UTF8 *mState;

   /// The captured object's name.
   String mObjectName;
	bool mIsDatablock;

public:

   SimObjectMemento();
   virtual ~SimObjectMemento();

   /// Returns true if we have recorded state.
   bool hasState() const { return mState; }

   ///
   void save( SimObject *object );

   ///
   SimObject *restore() const;

};


#endif // _CONSOLE_SIMOBJECTMEMENTO_H_
