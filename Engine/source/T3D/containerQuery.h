// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _CONTAINERQUERY_H_
#define _CONTAINERQUERY_H_

#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _STRINGTABLE_H_
#include "core/stringTable.h"
#endif
#ifndef _MBOX_H_
#include "math/mBox.h"
#endif

class SceneObject;
class WaterObject;

struct ContainerQueryInfo
{
   ContainerQueryInfo()
      : waterCoverage(0.0f),
        waterHeight(0.0f),                
        waterDensity(0.0f),
        waterViscosity(0.0f),
        gravityScale(1.0f),
        appliedForce(0,0,0),
        box(-1,-1,-1,1,1,1),
        mass(1.0f),
        waterObject(NULL)
   {        
   }

   //SceneObject *sceneObject;
   Box3F box;
   F32 mass;
   F32 waterCoverage;
   F32 waterHeight;
   F32 waterDensity;
   F32 waterViscosity;
   String liquidType;
   F32 gravityScale;
   Point3F appliedForce;
   WaterObject *waterObject;
};

extern void findRouter( SceneObject *obj, void *key );
extern void waterFind( SceneObject *obj, void *key );
extern void physicalZoneFind( SceneObject *obj, void *key );

#endif // _CONTAINERQUERY_H_