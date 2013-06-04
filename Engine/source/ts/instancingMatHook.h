// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _INSTANCINGMATHOOK_H_
#define _INSTANCINGMATHOOK_H_

#ifndef _MATINSTANCEHOOK_H_
#include "materials/matInstanceHook.h"
#endif

class BaseMatInstance;


class InstancingMaterialHook : public MatInstanceHook
{
public:

   /// The material hook type.
   static const MatInstanceHookType Type;

   InstancingMaterialHook();
   virtual ~InstancingMaterialHook();

   // MatInstanceHook
   virtual const MatInstanceHookType& getType() const { return Type; }

   /// Returns the instancing material instance or the input material 
   /// instance if one could not be created.
   static BaseMatInstance* getInstancingMat( BaseMatInstance *matInst );

protected:

   /// The instancing material.
   BaseMatInstance *mMatInst;

};

#endif // _INSTANCINGMATHOOK_H_
