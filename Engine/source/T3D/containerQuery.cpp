// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "T3D/containerQuery.h"

#include "scene/sceneObject.h"
#include "environment/waterObject.h"
#include "T3D/physicalZone.h"


void findRouter( SceneObject *obj, void *key )
{
   if (obj->getTypeMask() & WaterObjectType)
      waterFind(obj, key);
   else if (obj->getTypeMask() & PhysicalZoneObjectType)
      physicalZoneFind(obj, key);
   else {
      AssertFatal(false, "Error, must be either water or physical zone here!");
   }
}

void waterFind( SceneObject *obj, void *key )
{     
   PROFILE_SCOPE( waterFind );

   // This is called for each WaterObject the ShapeBase object is overlapping.

   ContainerQueryInfo *info = static_cast<ContainerQueryInfo*>(key);
   WaterObject *water = dynamic_cast<WaterObject*>(obj);      
   AssertFatal( water != NULL, "containerQuery - waterFind(), passed object was not of class WaterObject!");      

   // Get point at the bottom/center of the box.
   Point3F testPnt = info->box.getCenter();
   testPnt.z = info->box.minExtents.z;

   F32 coverage = water->getWaterCoverage(info->box);

   // Since a WaterObject can have global bounds we may get this call
   // even though we have zero coverage.  If so we want to early out and
   // not save the water properties.
   if ( coverage == 0.0f )
      return;

   // Add in flow force.  Would be appropriate to try scaling it by coverage
   // thought. Or perhaps have getFlow do that internally and take
   // the box parameter.
   info->appliedForce += water->getFlow( testPnt );

   // Only save the following properties for the WaterObject with the
   // greatest water coverage for this ShapeBase object.
   if ( coverage < info->waterCoverage )
      return;
   
   info->waterCoverage = coverage;
   info->liquidType = water->getLiquidType();
   info->waterViscosity = water->getViscosity();
   info->waterDensity = water->getDensity();
   info->waterHeight = water->getSurfaceHeight( Point2F(testPnt.x,testPnt.y) );   
   info->waterObject = water;
}

void physicalZoneFind(SceneObject* obj, void *key)
{    
   PROFILE_SCOPE( physicalZoneFind );

   ContainerQueryInfo *info = static_cast<ContainerQueryInfo*>(key);
   PhysicalZone* pz = dynamic_cast<PhysicalZone*>(obj);
   AssertFatal(pz != NULL, "Error, not a physical zone!");
   if (pz == NULL || pz->testBox(info->box) == false)
      return;

   if (pz->isActive()) {
      info->gravityScale *= pz->getGravityMod();
      info->appliedForce += pz->getForce();
   }
}

