// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "scene/sceneTracker.h"


//=============================================================================
//    SceneObjectLink.
//=============================================================================

//-----------------------------------------------------------------------------

SceneObjectLink::SceneObjectLink( SceneTracker* tracker, SceneObject* object )
   : mTracker( tracker ),
     mObject( object ),
     mNextLink( NULL ),
     mPrevLink( NULL )
{
   if( object )
   {
      mNextLink = object->mSceneObjectLinks;
      if( mNextLink )
         mNextLink->mPrevLink = this;
      object->mSceneObjectLinks = this;
   }
}

//-----------------------------------------------------------------------------

SceneObjectLink::~SceneObjectLink()
{
   if( mObject )
   {
      // Unlink from SceneObject's tracker list.

      if( mNextLink )
         mNextLink->mPrevLink = mPrevLink;
      if( mPrevLink )
         mPrevLink->mNextLink = mNextLink;
      else
         mObject->mSceneObjectLinks = mNextLink;
   }
}

//-----------------------------------------------------------------------------

void SceneObjectLink::update()
{
   getTracker()->updateObject( this );
}

//-----------------------------------------------------------------------------

SceneObjectLink* SceneObjectLink::getLinkForTracker( SceneTracker* tracker, SceneObject* fromObject )
{
   for( SceneObjectLink* link = fromObject->mSceneObjectLinks; link != NULL; link = link->getNextLink() )
      if( link->getTracker() == tracker )
         return link;

   return NULL;
}

//=============================================================================
//    SceneObjectLink.
//=============================================================================

//-----------------------------------------------------------------------------

SceneTracker::SceneTracker( bool isClientTracker, U32 typeMask )
   : mIsClientTracker( isClientTracker ),
     mObjectTypeMask( typeMask )
{
   // Hook up to SceneObject add/remove notifications.

   SceneObject::smSceneObjectAdd.notify( this, &SceneTracker::registerObject );
   SceneObject::smSceneObjectRemove.notify( this, &SceneTracker::unregisterObject );
}

//-----------------------------------------------------------------------------

SceneTracker::~SceneTracker()
{
   SceneObject::smSceneObjectAdd.remove( this, &SceneTracker::registerObject );
   SceneObject::smSceneObjectRemove.remove( this, &SceneTracker::unregisterObject );
}

//-----------------------------------------------------------------------------

void SceneTracker::init()
{
   // Register existing scene graph objects.

   SceneContainer* container;
   if( isClientTracker() )
      container = &gClientContainer;
   else
      container = &gServerContainer;

   container->findObjects( getObjectTypeMask(),
                           ( SceneContainer::FindCallback ) &_containerFindCallback,
                           this );
}

//-----------------------------------------------------------------------------

void SceneTracker::_containerFindCallback( SceneObject* object, SceneTracker* tracker )
{
   tracker->registerObject( object );
}
