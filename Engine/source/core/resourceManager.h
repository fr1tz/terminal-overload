// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif

#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif

using namespace Torque;

class ResourceManager
{
public:

   static ResourceManager &get();

   ResourceBase load(const Torque::Path &path);
   ResourceBase find(const Torque::Path &path);

   ResourceBase startResourceList( ResourceBase::Signature inSignature = U32_MAX );
   ResourceBase nextResource();

   void reloadResource( const Torque::Path &path, bool showMessage = false );

   typedef Signal<void(const Torque::Path &path)> ChangedSignal;

   /// Registering with this signal will give an opportunity to handle a change to the
   /// resource on disk.  For example, if a PNG file is edited by the artist and saved
   /// the ResourceManager will signal that the file has changed so the TextureManager
   /// may act appropriately - which probably means to re-init the materials using that PNG.
   /// The signal passes the Resource's signature so the callee may filter these.
   ChangedSignal &getChangedSignal() { return mChangeSignal; }

#ifdef TORQUE_DEBUG
   void  dumpToConsole();
#endif

   ~ResourceManager();

protected:

   friend class ResourceBase::Header;

   ResourceManager();

   bool remove( ResourceBase::Header* header );

   void  notifiedFileChanged( const Torque::Path &path );

   typedef HashTable<String,ResourceBase::Header*> ResourceHeaderMap;

   /// The map of resources.
   ResourceHeaderMap mResourceHeaderMap;

   /// The map of old resources which have been replaced by
   /// new resources from a file change notification.
   ResourceHeaderMap mPrevResourceHeaderMap;

   ResourceHeaderMap::Iterator mIter;

   U32 mIterSigFilter;

   ChangedSignal mChangeSignal;
};

#endif
