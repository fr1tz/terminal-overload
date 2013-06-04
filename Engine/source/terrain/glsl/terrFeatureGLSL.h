// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TERRFEATUREGLSL_H_
#define _TERRFEATUREGLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif
#ifndef _LANG_ELEMENT_H_
#include "shaderGen/langElement.h"
#endif

/// A shared base class for terrain features which
/// includes some helper functions.
class TerrainFeatGLSL : public ShaderFeatureGLSL
{
protected:
   
   Var* _getInDetailCoord(Vector<ShaderComponent*> &componentList );
   
   Var* _getNormalMapTex();
   
   static Var* _getUniformVar( const char *name, const char *type, ConstantSortPosition csp );
   
   Var* _getDetailIdStrengthParallax();
      
};

class TerrainBaseMapFeatGLSL : public TerrainFeatGLSL
{
public:

   virtual void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd );

   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );
          
   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Base Texture"; }
};

class TerrainDetailMapFeatGLSL : public TerrainFeatGLSL
{
protected:

   ShaderIncludeDependency mTerrainDep;

public:

   TerrainDetailMapFeatGLSL();

   virtual void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd );

   virtual void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd );

   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Detail Texture"; }
};


class TerrainNormalMapFeatGLSL : public TerrainFeatGLSL
{
public:

   virtual void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd );

   virtual void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd );

   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Normal Texture"; }
};

class TerrainParallaxMapFeatGLSL : public TerrainFeatGLSL
{
protected:

   ShaderIncludeDependency mIncludeDep;

public:

   TerrainParallaxMapFeatGLSL();
   
   virtual void processVert(  Vector<ShaderComponent*> &componentList,
                            const MaterialFeatureData &fd );
   
   virtual void processPix(   Vector<ShaderComponent*> &componentList, 
                           const MaterialFeatureData &fd );
   
   virtual Resources getResources( const MaterialFeatureData &fd );
   
   virtual String getName() { return "Terrain Parallax Texture"; }
};

class TerrainLightMapFeatGLSL : public TerrainFeatGLSL
{
public:

   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );
          
   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Lightmap Texture"; }
};


class TerrainAdditiveFeatGLSL : public TerrainFeatGLSL
{
public:

   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );

   virtual String getName() { return "Terrain Additive"; }
};

#endif // _TERRFEATUREGLSL_H_
