// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platformWin32/platformWin32.h"
#include "platform/platformVFS.h"
#include "console/console.h"

#include "core/stream/memstream.h"
#include "core/util/zip/zipArchive.h"

#include "core/util/safeDelete.h"

#include "VFSRes.h"

//-----------------------------------------------------------------------------

struct Win32VFSState
{
   S32 mRefCount;

   HGLOBAL mResData;

   MemStream *mZipStream;
   Zip::ZipArchive *mZip;

   Win32VFSState() : mResData(NULL), mZip(NULL), mRefCount(0), mZipStream(NULL)
   {
   }
};

static Win32VFSState gVFSState;

//-----------------------------------------------------------------------------

Zip::ZipArchive *openEmbeddedVFSArchive()
{
   if(gVFSState.mZip)
   {
      ++gVFSState.mRefCount;
      return gVFSState.mZip;
   }

   HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_ZIPFILE), dT("RT_RCDATA"));

   if(hRsrc == NULL)
      return NULL;
   
   if((gVFSState.mResData = LoadResource(NULL, hRsrc)) == NULL)
      return NULL;

   void * mem = LockResource(gVFSState.mResData);
   if(mem != NULL)
   {
      U32 size = SizeofResource(NULL, hRsrc);
      gVFSState.mZipStream = new MemStream(size, mem, true, false);
      gVFSState.mZip = new Zip::ZipArchive;

      if(gVFSState.mZip->openArchive(gVFSState.mZipStream))
      {
         ++gVFSState.mRefCount;
         return gVFSState.mZip;
      }

      SAFE_DELETE(gVFSState.mZip);
      SAFE_DELETE(gVFSState.mZipStream);
   }

   FreeResource(gVFSState.mResData);
   gVFSState.mResData = NULL;

   return NULL;
}

void closeEmbeddedVFSArchive()
{
   if(gVFSState.mRefCount == 0)
      return;

   --gVFSState.mRefCount;

   if(gVFSState.mRefCount < 1)
   {
      SAFE_DELETE(gVFSState.mZip);
      SAFE_DELETE(gVFSState.mZipStream);
      
      if(gVFSState.mResData)
      {
         FreeResource(gVFSState.mResData);
         gVFSState.mResData = NULL;
      }
   }
}
