// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _BASEMATERIALDEFINITION_H_
#define _BASEMATERIALDEFINITION_H_

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif

class BaseMatInstance;

class BaseMaterialDefinition : public SimObject
{
   typedef SimObject Parent;
public:
   virtual BaseMatInstance* createMatInstance() = 0;
   virtual bool isTranslucent() const = 0;
   virtual bool isDoubleSided() const = 0;
   virtual bool isLightmapped() const = 0;
   virtual bool castsShadows() const = 0;
};

#endif // _BASEMATERIALDEFINITION_H_
