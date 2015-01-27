// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _CUBEMAPDATA_H_
#define _CUBEMAPDATA_H_

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif

#ifndef _GFXCUBEMAP_H_
#include "gfx/gfxCubemap.h"
#endif

#ifndef _GFXTARGET_H_
#include "gfx/gfxTarget.h"
#endif

#ifndef _SCENEMANAGER_H_
#include "scene/sceneManager.h"
#endif


/// A script interface for creating static or dynamic cubemaps.
class CubemapData : public SimObject
{
   typedef SimObject Parent;   

public:   

   GFXCubemapHandle  mCubemap;

   CubemapData();
   ~CubemapData();

   bool onAdd();
   static void initPersistFields();

   DECLARE_CONOBJECT(CubemapData);

   // Force creation of cubemap
   void createMap();   

   // Update a static cubemap @ pos
	void updateFaces();

protected:

   FileName mCubeFaceFile[6];
   GFXTexHandle mCubeFace[6];

   GFXTexHandle mDepthBuff;
   GFXTextureTargetRef mRenderTarget;
};

#endif // CUBEMAPDATA

