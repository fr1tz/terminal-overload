// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIIMAGELIST_H_
#define _GUIIMAGELIST_H_

#include "console/simDatablock.h"

#ifndef _GUITYPES_H_
#include "gui/core/guiTypes.h"
#endif


class GuiImageList : public SimObject
{
  private:
   typedef SimObject Parent;

  public:
   typedef struct tag_TextureEntry
   {
      StringTableEntry TexturePath;
      GFXTexHandle Handle;
      U32 id;
   }TextureEntry,*PTextureEntry;
   
   Vector<PTextureEntry> mTextures;

  protected:


    U32 mUniqueId;
	
  public:
   GuiImageList();
   
   DECLARE_CONOBJECT(GuiImageList);
   
   static void initPersistFields();

   // Image managing functions
   bool Clear();
   inline U32 Count() { return (U32)mTextures.size(); };
   U32 Insert( const char* texturePath , GFXTextureProfile *Type = &GFXDefaultGUIProfile  );

   bool FreeTextureEntry( U32 Index );
   bool FreeTextureEntry( PTextureEntry Entry );

   GFXTexHandle GetTextureHandle( U32 Index );
   GFXTexHandle GetTextureHandle( const char* TexturePath );

   const char * GetTexturePath( U32 Index );

   U32 IndexFromId ( U32 Id );
   U32 IndexFromPath ( const char* Path );

};

#endif //_GUIIMAGELISTCTRL_H_
