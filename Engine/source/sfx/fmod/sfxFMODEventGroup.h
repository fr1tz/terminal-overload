// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXFMODEVENTGROUP_H_
#define _SFXFMODEVENTGROUP_H_

#ifndef _SIMDATABLOCK_H_
   #include "console/simDatablock.h"
#endif
#ifndef _TVECTOR_H_
   #include "core/util/tVector.h"
#endif
#ifndef _CONSOLETYPES_H_
   #include "console/consoleTypes.h"
#endif

#include "fmod_event.h"


class SFXFMODProject;
class SFXFMODEvent;


///
class SFXFMODEventGroup : public SimDataBlock
{
   public:
   
      typedef SimDataBlock Parent;
      friend class SFXFMODProject;
      friend class SFXFMODEvent; // mHandle
      friend class SFXFMODEventSource; // mHandle
      
   protected:
   
      ///
      String mName;
      
      ///
      U32 mNumEvents;
      
      ///
      U32 mNumGroups;
      
      ///
      SFXFMODProject* mProject;

      ///
      SFXFMODEventGroup* mParent;

      ///
      SFXFMODEventGroup* mChildren;
      
      ///
      SFXFMODEventGroup* mSibling;
   
      ///
      SFXFMODEvent* mEvents;
      
      ///
      FMOD_EVENTGROUP* mHandle;
      
      ///
      U32 mLoadCount;
      
      /// Project ID for client net sync.
      S32 mParentId;
      
      /// Project ID for client net sync.
      S32 mProjectId;
                  
      ///
      void _load();
      
      ///
      void _addEvent( SFXFMODEvent* event );
      
      ///
      void _addGroup( SFXFMODEventGroup* group );
      
      ///
      void _removeEvent( SFXFMODEvent* event );
      
      ///
      void _removeGroup( SFXFMODEventGroup* group );
      
   public:
   
      ///
      SFXFMODEventGroup();
   
      ///
      SFXFMODEventGroup( SFXFMODProject* project, const String& name, SFXFMODEventGroup* parent = NULL );

      ///
      SFXFMODEventGroup( SFXFMODProject* project, FMOD_EVENTGROUP* handle, SFXFMODEventGroup* parent = NULL );
      
      ~SFXFMODEventGroup();
      
      /// Create the event group object on the FMOD device.
      void acquire( bool recursive = false );
      
      /// Release the event group object on the FMOD device.
      void release();
      
      ///
      const String& getGroupName() const { return mName; }

      ///
      String getQualifiedName() const;
      
      ///
      SFXFMODProject* getProject() const { return mProject; }
      
      /// Return true if the event data for this group has been loaded.
      bool isDataLoaded() const;

      /// Load the event data for this group.
      ///
      /// @note Loading is reference-counted.
      bool loadData( bool samples = true, bool streams = true );
      
      ///
      void freeData( bool force = false );
      
      // SimDataBlock.
      virtual bool onAdd();
      virtual void onRemove();
      virtual bool preload( bool server, String& errorStr );
      virtual void packData( BitStream* stream );
      virtual void unpackData( BitStream* stream );
      
      static void initPersistFields();
      
      DECLARE_CONOBJECT( SFXFMODEventGroup );
      DECLARE_CATEGORY( "SFX FMOD" );
      DECLARE_DESCRIPTION( "An event group in an FMOD Designer project." );
};

#endif // !_SFXFMODEVENTGROUP_H_
