// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PXCONTACTREPORTER_H_
#define _PXCONTACTREPORTER_H_

#ifndef _PHYSX_H_
#include "T3D/physics/physX/px.h"
#endif


class PxContactReporter : public NxUserContactReport
{
protected:

   virtual void onContactNotify( NxContactPair& pair, NxU32 events );

public:

   PxContactReporter();
   virtual ~PxContactReporter();
};



class PxUserNotify : public NxUserNotify
{
public:
   virtual bool onJointBreak( NxReal breakingForce, NxJoint &brokenJoint );   
   virtual void onWake( NxActor **actors, NxU32 count ) {}
   virtual void onSleep ( NxActor **actors, NxU32 count ) {}
};


#endif // _PXCONTACTREPORTER_H_
