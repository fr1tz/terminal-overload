// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MOREADVANCEDCOMPONENT_H_
#define _MOREADVANCEDCOMPONENT_H_

#ifndef _SIMPLECOMPONENT_H_
#include "component/simpleComponent.h"
#endif

/// This is a slightly more advanced component which will be used to demonstrate
/// components which are dependent on other components.
class MoreAdvancedComponent : public SimComponent
{
   typedef SimComponent Parent;

protected:
   // This component is going to be dependent on a SimpleComponentInterface being
   // queried off of it's parent object. This will store that interface that
   // will get queried during onComponentRegister()
   SimpleComponentInterface *mSCInterface;

public:
   DECLARE_CONOBJECT(MoreAdvancedComponent);

   // Firstly, take a look at the documentation for this function in simComponent.h.
   // We will be overloading this method to query the component heirarchy for our
   // dependent interface, as noted above.
   virtual bool onComponentRegister( SimComponent *owner );

   // This function will try to execute a function through the interface that this
   // component is dependent on.
   virtual bool testDependentInterface();
};

#endif