// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gfx/sim/cubemapData.h"

#include "core/stream/bitStream.h"
#include "console/consoleTypes.h"
#include "gfx/gfxCubemap.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxTransformSaver.h"
#include "gfx/gfxDebugEvent.h"
#include "scene/sceneManager.h"
#include "console/engineAPI.h"
#include "math/mathUtils.h"


IMPLEMENT_CONOBJECT( CubemapData );

CubemapData::CubemapData()
{
   mCubemap = NULL;
}

CubemapData::~CubemapData()
{
   mCubemap = NULL;
}

ConsoleDocClass( CubemapData, 
   "@brief Used to create static or dynamic cubemaps.\n\n"
   "This object is used with Material, WaterObject, and other objects for cubemap reflections.\n\n"
   "A simple declaration of a static cubemap:\n"
   "@tsexample\n"
   "singleton CubemapData( SkyboxCubemap )\n"
   "{\n"
   "   cubeFace[0] = \"./skybox_1\";\n"
   "   cubeFace[1] = \"./skybox_2\";\n"
   "   cubeFace[2] = \"./skybox_3\";\n"
   "   cubeFace[3] = \"./skybox_4\";\n"
   "   cubeFace[4] = \"./skybox_5\";\n"
   "   cubeFace[5] = \"./skybox_6\";\n"
   "};\n"
   "@endtsexample\n"
   "@note The dynamic cubemap functionality in CubemapData has been depreciated in favor of ReflectorDesc.\n"
   "@see ReflectorDesc\n"
   "@ingroup GFX\n" );

void CubemapData::initPersistFields()
{
   addField( "cubeFace", TypeStringFilename, Offset(mCubeFaceFile, CubemapData), 6,
      "@brief The 6 cubemap face textures for a static cubemap.\n\n"
      "They are in the following order:\n"
      "  - cubeFace[0] is -X\n"
      "  - cubeFace[1] is +X\n"
      "  - cubeFace[2] is -Z\n"
      "  - cubeFace[3] is +Z\n"
      "  - cubeFace[4] is -Y\n"
      "  - cubeFace[5] is +Y\n" );
   Parent::initPersistFields();
}

bool CubemapData::onAdd()
{
   if( !Parent::onAdd() )
      return false;

   // Do NOT call this here as it forces every single cubemap defined to load its images, immediately, without mercy
   // createMap();

   return true;
}

void CubemapData::createMap()
{
   if( !mCubemap )
   {
       bool initSuccess = true;
       
       for( U32 i=0; i<6; i++ )
       {
           if( !mCubeFaceFile[i].isEmpty() )
           {
               if(!mCubeFace[i].set(mCubeFaceFile[i], &GFXDefaultStaticDiffuseProfile, avar("%s() - mCubeFace[%d] (line %d)", __FUNCTION__, i, __LINE__) ))
               {
                   Con::errorf("CubemapData::createMap - Failed to load texture '%s'", mCubeFaceFile[i].c_str());
                   initSuccess = false;
               }
           }
       }
       if( initSuccess )
       {
           mCubemap = GFX->createCubemap();
           mCubemap->initStatic( mCubeFace );
       }
   }
}

void CubemapData::updateFaces()
{
	bool initSuccess = true;

	for( U32 i=0; i<6; i++ )
   {
      if( !mCubeFaceFile[i].isEmpty() )
      {
         if(!mCubeFace[i].set(mCubeFaceFile[i], &GFXDefaultStaticDiffuseProfile, avar("%s() - mCubeFace[%d] (line %d)", __FUNCTION__, i, __LINE__) ))
         {
				initSuccess = false;
            Con::errorf("CubemapData::createMap - Failed to load texture '%s'", mCubeFaceFile[i].c_str());
         }
      }
   }

	if( initSuccess )
	{
		mCubemap = NULL;
		mCubemap = GFX->createCubemap();

		mCubemap->initStatic( mCubeFace );
	}
}

DefineEngineMethod( CubemapData, updateFaces, void, (),,
   "Update the assigned cubemaps faces." )
{
	object->updateFaces();
}

DefineEngineMethod( CubemapData, getFilename, const char*, (),,
   "Returns the script filename of where the CubemapData object was "
   "defined.  This is used by the material editor." )
{
   return object->getFilename();
}