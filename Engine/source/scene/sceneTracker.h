// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENETRACKER_H_
#define _SCENETRACKER_H_

#ifndef _SCENEOBJECT_H_
   #include "scene/sceneObject.h"
#endif


/// @file
/// This file contains an abstract framework for tracking SceneObjects.


class SceneTracker;


//-----------------------------------------------------------------------------
//    SceneObjectLink.
//-----------------------------------------------------------------------------


/// A SceneObjectLink represents the link between a SceneObject and a SceneTracker.
class SceneObjectLink
{
   public:
   
      typedef void Parent;
      friend class SceneTracker; // Administers our link fields.

   protected:
   
      /// SceneObject being linked to; always set and never changes.
      SceneObject* mObject;
      
      /// The scene tracker to which this link belongs.
      SceneTracker* mTracker;
            
      /// Next scope link on this SceneObject; NULL if last.
      SceneObjectLink* mNextLink;
      
      /// Previous scope link on this SceneObject; NULL if first.
      SceneObjectLink* mPrevLink;

   public:
   
      ///
      SceneObjectLink( SceneTracker* tracker, SceneObject* object );
      
      virtual ~SceneObjectLink();

      /// @return The SceneScopeTracker managing this link.
      SceneTracker* getTracker() const { return mTracker; }

      /// @return The object being linked to.
      SceneObject* getObject() const { return mObject; }
      
      /// @return The next link in this link chain.
      SceneObjectLink* getNextLink() const { return mNextLink; }
      
      /// @return The previous link in this link chain.
      SceneObjectLink* getPrevLink() const { return mPrevLink; }

      /// Notify the associated tracker that the transform state of the
      /// scene object represented by this link has changed.
      void update();

      ///
      static SceneObjectLink* getLinkForTracker( SceneTracker* tracker, SceneObject* fromObject );
};


//-----------------------------------------------------------------------------
//    SceneTracker.
//-----------------------------------------------------------------------------


/// A SceneTracker tracks SceneObjects.
///
/// This is an abstract base class.
class SceneTracker
{
   public:
   
      typedef void Parent;
      friend class SceneObjectLink; // SceneObjectLink::update() notifies us on SceneObject state changes.

   protected:
   
      /// If true, only client SceneObjects will be tracked; otherwise it's only server SceneObjects.
      bool mIsClientTracker;
      
      /// Type mask that SceneObjects must match in order to be allowed to register.
      U32 mObjectTypeMask;
      
      /// Return true if the given object qualifies for being managed by this SceneTracker.
      virtual bool _isTrackableObject( SceneObject* object ) const
      {
         return ( object->isClientObject() == mIsClientTracker
                  && ( object->getTypeMask() & getObjectTypeMask() ) );
      }

      /// Callback used for the initial scan of objects in init().
      static void _containerFindCallback( SceneObject* object, SceneTracker* tracker );

   public:
   
      ///
      SceneTracker( bool isClientTracker, U32 typeMask = 0xFFFFFFFF );
      
      virtual ~SceneTracker();
      
      /// Initialize the tracker from the current scene.
      virtual void init();

      /// @return The type mask that must be matched by objects in order to be allowed to register.
      U32 getObjectTypeMask() const { return mObjectTypeMask; }
      
      /// Set the type mask that objects must match in order to be allowed to register.
      void setObjectTypeMask( U32 typeMask ) { mObjectTypeMask = typeMask; }

      /// @return True if this tracker only deals with client objects; false if only server objects.
      bool isClientTracker() const { return mIsClientTracker; }

      /// Register a SceneObject for being tracked by this tracker.
      ///
      /// Only objects that fit the tracker's client/server state and
      /// object type mask will actually get registered.  For other objects,
      /// this is a NOP.
      ///
      /// @param object Scene object.
      virtual void registerObject( SceneObject* object ) = 0;

      /// Unregister the given object from the tracker.
      /// @param object Scene object.
      virtual void unregisterObject( SceneObject* object ) = 0;

      /// Notify the tracker that the transform state of the given scene object has changed.
      /// @param object Scene object.
      virtual void updateObject( SceneObjectLink* object ) = 0;
};

#endif // !_SCENETRACKER_H_
