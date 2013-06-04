// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "T3DSceneClient.h"

//---------------------------------------------------
// T3DSceneClient
//---------------------------------------------------

void T3DSceneClient::setSceneGroupName(const char * name)
{
   _sceneGroupName = StringTable->insert(name);
   if (getOwner() != NULL)
   {
      if (_sceneGroup != NULL)
         _sceneGroup->RemoveClientObject(this);
      _sceneGroup = NULL;

      ValueWrapperInterface<T3DSceneComponent*> * iface = getInterface<ValueWrapperInterface<T3DSceneComponent*> >("sceneComponent", _sceneGroupName);
      if (iface != NULL)
      {
         _sceneGroup = iface->get();
         _sceneGroup->AddSceneClient(this);
      }
   }
}

bool T3DSceneClient::onComponentRegister(SimComponent * owner)
{
   if (!Parent::onComponentRegister(owner))
      return false;

   // lookup scene group and add ourself
   setSceneGroupName(_sceneGroupName);

   if (_sceneGroupName != NULL && dStricmp(_sceneGroupName, "none") && _sceneGroup == NULL)
      // tried to add ourself to a scene group but failed, fail to add component
      return false;

   return true;
}

void T3DSceneClient::registerInterfaces(SimComponent * owner)
{
   Parent::registerInterfaces(owner);
   registerCachedInterface("sceneClient", NULL, this, new ValueWrapperInterface<T3DSceneClient>());
}

//---------------------------------------------------
// T3DSceneClient
//---------------------------------------------------

Box3F T3DSolidSceneClient::getWorldBox()
{
   MatrixF mat = getTransform();
   Box3F box = _objectBox->get();
   mat.mul(box);
   return box;
}

const MatrixF & T3DSolidSceneClient::getTransform()
{
   if (_transform != NULL)
      return _transform->getWorldMatrix();
   else if (getSceneGroup() != NULL)
      return getSceneGroup()->getTransform3D()->getWorldMatrix();
   else
      return MatrixF::smIdentity;
}

void T3DSolidSceneClient::setTransform3D(Transform3D *  transform)
{
   if (_transform != NULL)
      _transform->setDirtyListener(NULL);
   _transform = transform;

   _transform->setDirtyListener(this);
   OnTransformDirty();
}

void T3DSolidSceneClient::OnTransformDirty()
{
   // TODO: need a way to skip this...a flag, but we don't want to add a bool just for that
   // reason we might want to skip it is if we have a renderable that orbits an object but always
   // stays within object box.  Want to be able to use that info to skip object box updates.
   if (getSceneGroup() != NULL)
      getSceneGroup()->setDirtyObjectBox(true);
}
