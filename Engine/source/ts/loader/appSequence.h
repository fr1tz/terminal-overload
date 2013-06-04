// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _APPSEQUENCE_H_
#define _APPSEQUENCE_H_

#ifndef _MMATH_H_
#include "math/mMath.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif

class AppSequence
{
public:
   S32 fps;

public:
   AppSequence() { }
   virtual ~AppSequence() { }

   virtual void setActive(bool active) { }

   virtual S32 getNumTriggers() const { return 0; }
   virtual void getTrigger(S32 index, TSShape::Trigger& trigger) const { trigger.state = 0;}

   virtual const char* getName() const { return "ambient"; }

   virtual F32 getStart() const { return 0.0f; }
   virtual F32 getEnd() const { return 0.0f; }

   virtual U32 getFlags() const { return 0; }
   virtual F32 getPriority() const { return 5; }
   virtual F32 getBlendRefTime() const { return 0.0f; }
};

#endif // _APPSEQUENCE_H_
