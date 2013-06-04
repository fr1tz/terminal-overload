// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TSMATERIALLIST_H_
#define _TSMATERIALLIST_H_

#ifndef _MATERIALLIST_H_
#include "materials/materialList.h"
#endif
#ifndef _PATH_H_
#include "core/util/path.h"
#endif


/// Specialized material list for 3space objects.
class TSMaterialList : public MaterialList
{
   typedef MaterialList Parent;

   Vector<U32> mFlags;
   Vector<U32> mReflectanceMaps;
   Vector<U32> mBumpMaps;
   Vector<U32> mDetailMaps;
   Vector<F32> mDetailScales;
   Vector<F32> mReflectionAmounts;

   bool mNamesTransformed;

   void allocate(U32 sz);

  public:

   enum
   {
      S_Wrap             = BIT(0),
      T_Wrap             = BIT(1),
      Translucent        = BIT(2),
      Additive           = BIT(3),
      Subtractive        = BIT(4),
      SelfIlluminating   = BIT(5),
      NeverEnvMap        = BIT(6),
      NoMipMap           = BIT(7),
      MipMap_ZeroBorder  = BIT(8),
      AuxiliaryMap       = BIT(27) | BIT(28) | BIT(29) | BIT(30) | BIT(31) // DEPRECATED
   };

   TSMaterialList(U32 materialCount, const char **materialNames, const U32 * materialFlags,
                  const U32 * reflectanceMaps, const U32 * bumpMaps, const U32 * detailMaps,
                  const F32 * detailScales, const F32 * reflectionAmounts);
   TSMaterialList();
   TSMaterialList(const TSMaterialList*);
   ~TSMaterialList();
   void free();

   U32 getFlags(U32 index);
   void setFlags(U32 index, U32 value);

   bool renameMaterial(U32 index, const String& newName); // use to support reskinning

   /// pre-load only
   void push_back(const String &name, U32 flags,
                  U32 a=0xFFFFFFFF, U32 b=0xFFFFFFFF, U32 c=0xFFFFFFFF,
                  F32 dm=1.0f, F32 em=1.0f);
   void push_back(const char * name, U32 flags, Material* mat);

   /// @name IO
   /// Functions for reading/writing to/from streams
   /// @{

   bool write(Stream &);
   bool read(Stream &);
   /// @}

protected:
   virtual void mapMaterial( U32 index );
};


#endif // _TSMATERIALLIST_H_
