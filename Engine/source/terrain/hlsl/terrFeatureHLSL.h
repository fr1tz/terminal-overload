// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TERRFEATUREHLSL_H_
#define _TERRFEATUREHLSL_H_

#ifndef _SHADERGEN_HLSL_SHADERFEATUREHLSL_H_
#include "shaderGen/HLSL/shaderFeatureHLSL.h"
#endif
#ifndef _LANG_ELEMENT_H_
#include "shaderGen/langElement.h"
#endif


/// A shared base class for terrain features which
/// includes some helper functions.
class TerrainFeatHLSL : public ShaderFeatureHLSL
{
protected:

   Var* _getInDetailCoord(Vector<ShaderComponent*> &componentList );

   Var* _getInMacroCoord(Vector<ShaderComponent*> &componentList );

   Var* _getNormalMapTex();

   static Var* _getUniformVar( const char *name, const char *type, ConstantSortPosition csp );

   Var* _getDetailIdStrengthParallax();
   Var* _getMacroIdStrengthParallax();

};


class TerrainBaseMapFeatHLSL : public TerrainFeatHLSL
{
public:

   virtual void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd );

   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );
          
   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Base Texture"; }
};


class TerrainDetailMapFeatHLSL : public TerrainFeatHLSL
{
protected:

   ShaderIncludeDependency mTorqueDep;
   ShaderIncludeDependency mTerrainDep;

public:

   TerrainDetailMapFeatHLSL();

   virtual void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd );

   virtual void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd );

   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Detail Texture"; }
};


class TerrainMacroMapFeatHLSL : public TerrainFeatHLSL
{
protected:

   ShaderIncludeDependency mTorqueDep;
   ShaderIncludeDependency mTerrainDep;

public:

   TerrainMacroMapFeatHLSL();

   virtual void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd );

   virtual void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd );

   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Macro Texture"; }
};


class TerrainNormalMapFeatHLSL : public TerrainFeatHLSL
{
public:

   virtual void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd );

   virtual void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd );

   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Normal Texture"; }
};

class TerrainLightMapFeatHLSL : public TerrainFeatHLSL
{
public:

   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );
          
   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Lightmap Texture"; }
};


class TerrainAdditiveFeatHLSL : public TerrainFeatHLSL
{
public:

   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Additive"; }
};

#endif // _TERRFEATUREHLSL_H_
