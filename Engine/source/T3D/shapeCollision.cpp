// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "T3D/shapeBase.h"
#include "T3D/item.h"
#include "T3D/trigger.h"

//----------------------------------------------------------------------------

void collisionFilter(SceneObject* object,void *key)
{
   SceneContainer::CallbackInfo* info = reinterpret_cast<SceneContainer::CallbackInfo*>(key);
   ShapeBase* ptr = reinterpret_cast<ShapeBase*>(info->key);

   if (object->getTypeMask() & ItemObjectType) {
      // We've hit it's bounding box, that's close enough for items.
      Item* item = static_cast<Item*>(object);
      if (ptr != item->getCollisionObject())
         ptr->queueCollision(item,ptr->getVelocity() - item->getVelocity());
   }
   else
      if (object->getTypeMask() & TriggerObjectType) {
         // We've hit it's bounding box, that's close enough for triggers
         Trigger* pTrigger = static_cast<Trigger*>(object);
         pTrigger->potentialEnterObject(ptr);
      }
      else
         if (object->getTypeMask() & CorpseObjectType)  {
            // Ok, guess it's close enough for corpses too...
            ShapeBase* col = static_cast<ShapeBase*>(object);
            ptr->queueCollision(col,ptr->getVelocity() - col->getVelocity());
         }
         else
            object->buildPolyList(info->context,info->polyList,info->boundingBox,info->boundingSphere);
}

void defaultFilter(SceneObject* object,void * key)
{
   SceneContainer::CallbackInfo* info = reinterpret_cast<SceneContainer::CallbackInfo*>(key);
   object->buildPolyList(info->context,info->polyList,info->boundingBox,info->boundingSphere);
}

