//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#ifndef _ADVANCEDLIGHTINGFEATURES_H_
#define _ADVANCEDLIGHTINGFEATURES_H_

#include "gfx/gfxEnums.h"

#include "shaderGen/shaderFeature.h"
#include "shaderGen/bump.h"
#include "shaderGen/pixSpecular.h"

class AdvancedLightingFeatures
{
public:
    static void registerFeatures( const GFXFormat &prepassTargetFormat, const GFXFormat &lightInfoTargetFormat );
    static void unregisterFeatures();

private:
    static bool smFeaturesRegistered;
};

/// Lights the pixel by sampling from the light prepass buffer.
/// It will fall back to forward lighting  functionality for non-deferred rendered surfaces.
///
/// Also note that this feature is only used in the forward rendering pass.  
/// It is not used during the prepass step.
///
class DeferredRTLightingFeat : public RTLightingFeat
{
    typedef RTLightingFeat Parent;

protected:

    U32 mLastTexIndex;

public:

    virtual void processVert( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual void processPix(   Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual void processPixMacros(   Vector<GFXShaderMacro> &macros, const MaterialFeatureData &fd );

    virtual Material::BlendOp getBlendOp(){ return Material::None; }

    virtual Resources getResources( const MaterialFeatureData &fd );

    virtual void setTexData(   Material::StageData &stageDat, const MaterialFeatureData &fd, RenderPassData &passData, U32 &texIndex );

    virtual String getName()
    {
        return "Deferred RT Lighting";
    }
};


/// This is used during the 
class DeferredBumpFeat : public BumpFeat
{
    typedef BumpFeat Parent;

public:
    virtual void processVert(  Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual void processPix(   Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual Material::BlendOp getBlendOp() { return Material::LerpAlpha; }

    virtual Resources getResources( const MaterialFeatureData &fd );

    virtual void setTexData(   Material::StageData &stageDat, const MaterialFeatureData &fd, RenderPassData &passData, U32 &texIndex );

    virtual String getName()
    {
        return "Bumpmap [Deferred]";
    }
};


/// Generates specular highlights in the forward pass 
/// from the light prepass buffer.
class DeferredPixelSpecular : public PixelSpecular
{
    typedef PixelSpecular Parent;

public:
    virtual void processVert(  Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual void processPix(   Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual Resources getResources( const MaterialFeatureData &fd );

    virtual String getName()
    {
        return "Pixel Specular [Deferred]";
    }
};


///
class DeferredMinnaert : public ShaderFeature
{
    typedef ShaderFeature Parent;

public:
    virtual void processPix(   Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
    virtual void processVert(  Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual void processPixMacros(   Vector<GFXShaderMacro> &macros, const MaterialFeatureData &fd );

    virtual Resources getResources( const MaterialFeatureData &fd );

    virtual void setTexData(   Material::StageData &stageDat, const MaterialFeatureData &fd, RenderPassData &passData, U32 &texIndex );

    virtual String getName()
    {
        return "Minnaert Shading [Deferred]";
    }
};


///
class DeferredSubSurface : public ShaderFeature
{
    typedef ShaderFeature Parent;

public:
    virtual void processPix(   Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );

    virtual String getName()
    {
        return "Sub-Surface Approximation [Deferred]";
    }
};

#endif // _ADVANCEDLIGHTINGFEATURES_H_
