// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PXUTILS_H_
#define _PXUTILS_H_


class NxActor;


namespace PxUtils {

   /// Debug render an actor, loops through all shapes
   /// and translates primitive types into drawUtil calls.
   void drawActor( NxActor *inActor );

} // namespace PxUtils

#endif // _PXUTILS_H_