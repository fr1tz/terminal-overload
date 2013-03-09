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
#ifndef _GFX_CG_SHADER_H_
#define _GFX_CG_SHADER_H_

#include "gfx/gfxShader.h"
#include "cg.h"
#include "core/util/tDictionary.h"

class GFXCGShader;

class GFXCGShaderConstHandle : public GFXShaderConstHandle
{
    String mName;
    GFXShaderConstType mVType;
    GFXShaderConstType mPType;

    CGparameter mVParam;
    CGparameter mPParam;

public:   
    GFXCGShaderConstHandle(CGparameter vparam, CGparameter pparam, const String& name);

    virtual const String& getName() const       { return mName; }
    virtual GFXShaderConstType getType() const;
    virtual U32 getArraySize() const;
    virtual S32 getSamplerRegister() const;

    CGparameter getVParameter() const           { return mVParam; }
    CGparameter getPParameter() const           { return mPParam; }

    void setValid(bool valid)                   { mValid = valid; }

    void validate(GFXCGShader* shader);
    
private:
    void _validate(CGprogram program, CGparameter& param);

};

class GFXCGShaderConstBuffer : public GFXShaderConstBuffer
{
    GFXShader* mShader;
    
    S32     mNumVertexParamsF;
    S32     mNumVertexParamsI;
    F32*    mVertexParamsF;
    S32*    mVertexParamsI;

    S32     mNumPixelParamsF;
    S32     mNumPixelParamsI;
    F32*    mPixelParamsF;
    S32*    mPixelParamsI;

public:
    GFXCGShaderConstBuffer( GFXShader* shader );
    virtual ~GFXCGShaderConstBuffer();

    virtual GFXShader* getShader()      { return mShader; }

    virtual void set(GFXShaderConstHandle* handle, const F32 f);
    virtual void set(GFXShaderConstHandle* handle, const Point2F& fv);
    virtual void set(GFXShaderConstHandle* handle, const Point3F& fv);
    virtual void set(GFXShaderConstHandle* handle, const Point4F& fv);
    virtual void set(GFXShaderConstHandle* handle, const PlaneF& fv);
    virtual void set(GFXShaderConstHandle* handle, const ColorF& fv);
    virtual void set(GFXShaderConstHandle* handle, const S32 f);
    virtual void set(GFXShaderConstHandle* handle, const Point2I& fv);
    virtual void set(GFXShaderConstHandle* handle, const Point3I& fv);
    virtual void set(GFXShaderConstHandle* handle, const Point4I& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv);
    virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv);

    /// Set a variable sized matrix shader constant.   
    virtual void set( GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType = GFXSCT_Float4x4 );

    /// Set a variable sized matrix shader constant from an array of matricies.   
    virtual void set( GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType = GFXSCT_Float4x4 );

    // GFXResource
    virtual const String describeSelf() const;
    virtual void zombify();
    virtual void resurrect();

    void activate();

private:    
    F32* _allocateParameterBufferF(CGprogram program, S32& outNumParameters);
    S32* _allocateParameterBufferI(CGprogram program, S32& outNumParameters);
    void _setParam(CGparameter param, F32* paramBuffer, S32 numParams, const F32* values, S32 valueCount);
    void _setParam(CGparameter param, S32* paramBuffer, S32 numParams, const S32* values, S32 valueCount);
    void _write(F32* paramBuffer, S32 index, const F32* values, S32 valueCount);
    void _write(S32* paramBuffer, S32 index, const S32* values, S32 valueCount);

    S32 _getRegisterNumber(CGparameter param);
};



class GFXCGShader : public GFXShader
{
    typedef Map<String, GFXCGShaderConstHandle*> CGHandleMap;

    CGprogram mCGVertexProgram;
    CGprogram mCGPixelProgram;
    CGHandleMap mCGHandles;

    Vector<GFXShaderConstDesc> mShaderConsts;

    GFXCGShaderConstBuffer* mConstBuffer;

public:

    GFXCGShader();
    virtual ~GFXCGShader();

    CGprogram getCGVertexProgram()   { return mCGVertexProgram; }
    CGprogram getCGPixelProgram()    { return mCGPixelProgram; }
    void bind();
    
    virtual bool _init();

    virtual GFXShaderConstBufferRef allocConstBuffer(); 
    void destroyConstBuffer(GFXShaderConstBuffer* buffer);
    virtual const Vector<GFXShaderConstDesc>& getShaderConstDesc() const;
    virtual GFXShaderConstHandle* getShaderConstHandle( const String& name ); 
    virtual U32 getAlignmentValue(const GFXShaderConstType constType) const;   

    
    virtual void zombify() {};
    virtual void resurrect() {};

    
    static GFXShaderConstType GFXTypeFromCGType(CGparameter param, CGtype type = CG_UNKNOWN_TYPE);

private:
    CGprogram _compileCG( const Torque::Path& cgFile, const Vector<GFXShaderMacro>& macros, bool vertexProgram );
    void _refreshShaderConstants();
    void _clearPrograms();
    void _loadProgram(CGprogram program);
};

#endif // _GFX_CG_SHADER_H_