// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/resourceManager.h"
#include "core/volume.h"

#include "console/console.h"


FreeListChunker<ResourceHolderBase> ResourceHolderBase::smHolderFactory;

ResourceBase::Header ResourceBase::smBlank;


U32   ResourceBase::Header::getChecksum() const
{
   Torque::FS::FileNodeRef fileRef = Torque::FS::GetFileNode( mPath );

   if ( fileRef == NULL )
   {
      Con::errorf("ResourceBase::getChecksum could not access file: [%s]", mPath.getFullPath().c_str() );
      return 0;
   }

   return fileRef->getChecksum();
}

void ResourceBase::Header::destroySelf()
{
   if (this == &smBlank)
      return;
      
   if( mNotifyUnload )
      mNotifyUnload( getPath(), getResource() );

   if ( mResource != NULL )
   {
      mResource->~ResourceHolderBase();
      ResourceHolderBase::smHolderFactory.free( mResource );
   }

   ResourceManager::get().remove( this );
   delete this;
}

void  ResourceBase::assign(const ResourceBase &inResource, void* resource)
{
   mResourceHeader = inResource.mResourceHeader;

   if ( mResourceHeader == NULL || mResourceHeader.getPointer() == &(ResourceBase::smBlank) )
      return;

   if (mResourceHeader->getSignature())
   {
      AssertFatal(inResource.mResourceHeader->getSignature() == getSignature(),"Resource::assign: mis-matching signature");
   }
   else
   {
      mResourceHeader->mSignature = getSignature();

      const Torque::Path   path = mResourceHeader->getPath();

      if (resource == NULL)
      {
         if ( !getStaticLoadSignal().trigger(path, &resource) && (resource != NULL) )
         {
            mResourceHeader->mResource = createHolder(resource);
            mResourceHeader->mNotifyUnload = _getNotifyUnloadFn();
            _triggerPostLoadSignal();
            return;
         }

         resource = create(path);
      }

      if (resource)
      {
         mResourceHeader->mResource = createHolder(resource);
         mResourceHeader->mNotifyUnload = _getNotifyUnloadFn();
         _triggerPostLoadSignal();
      }
      else
      {
         // Failed to create...delete signature so we can attempt to successfully create resource later
         Con::warnf("Failed to create resource: [%s]", path.getFullPath().c_str() );

         mResourceHeader->mSignature = 0;
      }
   }
}

