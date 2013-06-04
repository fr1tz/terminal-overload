// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TERRMATERIAL_H_
#define _TERRMATERIAL_H_

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif


/// The TerrainMaterial class orginizes the material settings 
/// for a single terrain material layer.
class TerrainMaterial : public SimObject
{
   typedef SimObject Parent;

protected:

   ///
   FileName mDiffuseMap;

   /// The size of the diffuse base map in meters 
   /// used to generate its texture coordinates.
   F32 mDiffuseSize;

   ///
   FileName mNormalMap;

   ///
   FileName mDetailMap;

   /// The size of the detail map in meters used
   /// to generate the texture coordinates for the
   /// detail and normal maps.
   F32 mDetailSize;

   /// 
   F32 mDetailStrength;

   /// 
   F32 mDetailDistance;

   /// Normally the detail is projected on to the xy 
   /// coordinates of the terrain.  If this flag is true
   /// then this detail is projected along the xz and yz
   /// planes.
   bool mSideProjection;

   FileName mMacroMap;
   F32 mMacroSize;
   F32 mMacroStrength;
   F32 mMacroDistance;

   ///
   F32 mParallaxScale;

public:

   TerrainMaterial();
   virtual ~TerrainMaterial();

   bool onAdd();
   static void initPersistFields();

   DECLARE_CONOBJECT( TerrainMaterial );

   /// This method locates the TerrainMaterial if it exists, tries 
   /// to create a new one if a valid texture path was passed, or
   /// returns a debug material if all else fails.
   static TerrainMaterial* findOrCreate( const char *nameOrPath );

   /// Returns the default warning terrain material used when
   /// a material is not found or defined.
   static TerrainMaterial* getWarningMaterial();

   const String& getDiffuseMap() const { return mDiffuseMap; }

   F32 getDiffuseSize() const { return mDiffuseSize; }

   const String& getNormalMap() const { return mNormalMap; }

   const String& getDetailMap() const { return mDetailMap; }

   const String& getMacroMap() const { return mMacroMap; }

   F32 getDetailSize() const { return mDetailSize; }

   F32 getDetailStrength() const { return mDetailStrength; }

   F32 getDetailDistance() const { return mDetailDistance; }

   F32 getMacroSize() const { return mMacroSize; }

   F32 getMacroDistance() const { return mMacroDistance; }

   F32 getMacroStrength() const { return mMacroStrength; }

   bool useSideProjection() const { return mSideProjection; }

   F32 getParallaxScale() const { return mParallaxScale; }

};

#endif // _TERRMATERIAL_H_
