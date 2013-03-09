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

#include "platform/platform.h"
#include "gfx/gfxCGShader.h"
#include "gfx/gfxDevice.h"
#include "core/stream/fileStream.h"
#include "console/console.h"

#include <stdio.h>

#ifdef WIN32
#include "gfx/D3D9/gfxD3D9Device.h"
#include "cgD3D9.h"
#else
#define cgD3D9LoadProgram(a, b, c)  {}
#define cgD3D9BindProgram(a)        {}
#endif

#include "cgGL.h"

static void _dumpCGParameters(CGprogram program)
{
    CGparameter param = cgGetFirstParameter(program, CG_GLOBAL);
    bool bGlobal = true;
    while( param )
    {
        CGparameter oldParam = param;
        if( cgGetParameterType(param) == CG_ARRAY )
        {
            param = cgGetArrayParameter(param, 0);
        }
        const char* resource = cgGetParameterResourceName(param);
        Con::printf(" (%d) %s %s : %s %s(%d) %d", cgGetParameterOrdinalNumber(param), cgGetTypeString(cgGetParameterType(param)), cgGetParameterName(param), cgGetParameterSemantic(param), resource ? resource : "", cgGetParameterResourceIndex(param), cgGetParameterIndex(param));

        param = cgGetNextParameter(oldParam);
        if( !param && bGlobal )
        {
            param = cgGetFirstParameter(program, CG_PROGRAM);
            bGlobal = false;
        }
    }
}



GFXCGShader::GFXCGShader()
      : mCGVertexProgram(0),
      mCGPixelProgram(0),
      mConstBuffer(0)
{
    VECTOR_SET_ASSOCIATION( mShaderConsts );
}

GFXCGShader::~GFXCGShader()
{
    _clearPrograms();

    if( mConstBuffer )
        delete mConstBuffer;
    mConstBuffer = 0;
}

void GFXCGShader::_clearPrograms()
{
    if( mCGVertexProgram )
        cgDestroyProgram(mCGVertexProgram);
    if( mCGPixelProgram )
        cgDestroyProgram(mCGPixelProgram);
}

bool GFXCGShader::_init()
{
    _clearPrograms();

    Vector<GFXShaderMacro> macros;
    macros.merge(mMacros);
    macros.merge( smGlobalMacros );

    // Compile the programs
    static String sCGStr( "cg" );
    if( mVertexFile.getExtension().equal( sCGStr, String::NoCase ) )
    {
        mCGVertexProgram = _compileCG(mVertexFile, macros, true);
    }
    if( mPixelFile.getExtension().equal( sCGStr, String::NoCase ) )
    {
        mCGPixelProgram = _compileCG(mPixelFile, macros, false);
    }

    bool success = (mCGVertexProgram && mCGPixelProgram);
    if( GFX->getAdapterType() == OpenGL )
    {
        CGprogram programs[] = {mCGVertexProgram, mCGPixelProgram};
        CGprogram combined = cgCombinePrograms(2, programs);
        cgDestroyProgram(mCGVertexProgram);
        cgDestroyProgram(mCGPixelProgram);
        mCGVertexProgram = combined;
        mCGPixelProgram = 0;
        AssertFatal(combined, "Failed to combine shaders");
    }

    // Load the programs
    _loadProgram(mCGVertexProgram);
    _loadProgram(mCGPixelProgram);

    _refreshShaderConstants();

    return success;
}

void GFXCGShader::_loadProgram(CGprogram program)
{
    if( program )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            cgGLLoadProgram(program);
        }
        else
        {
            cgD3D9LoadProgram(program, CG_FALSE, 0);
        }
    }
}

void GFXCGShader::_refreshShaderConstants()
{    
    mShaderConsts.clear();

    if( mCGVertexProgram )
    {
        CGparameter param = cgGetFirstParameter(mCGVertexProgram, CG_PROGRAM);
        while( param )
        {
            GFXShaderConstDesc desc;
            desc.name = String(cgGetParameterName(param));
            desc.constType = GFXCGShader::GFXTypeFromCGType(param);
            desc.arraySize = cgGetParameterRows(param);
            mShaderConsts.push_back(desc);

            param = cgGetNextParameter(param);
        }
    }

    if( mCGPixelProgram )
    {
        CGparameter param = cgGetFirstParameter(mCGPixelProgram, CG_PROGRAM);
        while( param )
        {
            GFXShaderConstDesc desc;
            desc.name = String(cgGetParameterName(param));
            desc.constType = GFXCGShader::GFXTypeFromCGType(param);
            desc.arraySize = cgGetParameterRows(param);
            mShaderConsts.push_back(desc);

            param = cgGetNextParameter(param);
        }
    }    
}

void GFXCGShader::bind()
{
    if( mCGVertexProgram )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            cgGLEnableProfile(GFX->getCGVertexProfile());
            cgGLEnableProfile(GFX->getCGPixelProfile());
            cgGLBindProgram(mCGVertexProgram);
        }
        else
        {
            cgD3D9BindProgram(mCGVertexProgram);
        }
    }
    if( mCGPixelProgram )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            cgGLBindProgram(mCGPixelProgram);
        }
        else
        {
            cgD3D9BindProgram(mCGPixelProgram);
        }
    }
}

CGprogram GFXCGShader::_compileCG( const Torque::Path& cgFile, const Vector<GFXShaderMacro>& macros, bool vertexProgram )
{
    FileStream s;
    if ( !s.open( cgFile, Torque::FS::File::Read ) )
    {
        if ( smLogErrors )
            Con::errorf( "GFXShader::_compileCG - Failed to open shader file '%s'.", cgFile.getFullPath().c_str() );

        return 0;
    }

    Torque::Path realPath;
    if ( !Torque::FS::GetFSPath( cgFile, realPath ) )
        realPath = cgFile;
    
    U32 bufSize = s.getStreamSize();
    FrameAllocatorMarker fam;
    char* cgSource = (char *)fam.alloc( bufSize + 1 );
    s.read( bufSize, cgSource );
    cgSource[bufSize] = 0;
    s.close();
     
    CGprofile profile = vertexProgram ? GFX->getCGVertexProfile() : GFX->getCGPixelProfile();
    
    char** args = (char**)(malloc((macros.size() + 2) * sizeof(char*)));
    int i = 0;
    for( i = 0; i < macros.size(); i++ )
    {
        U32 size = macros[i].name.length() + macros[i].value.length() + 4;
        args[i] = (char*)malloc(size);
        dSprintf(args[i], size, "-D%s%s%s", macros[i].name.c_str(), macros[i].value.length() > 0 ? "=" : "", macros[i].value.c_str());
    }
    String includePath("-I");
    includePath += cgFile.getPath();
    args[i++] = dStrdup_r(includePath.c_str(), __FILE__, __LINE__);
    args[i] = 0;

    CGprogram prg = cgCreateProgram(GFX->getCGContext(), CG_SOURCE, cgSource, profile, "main", (const char**)args);
    if( prg == 0 )
    {
        const char* errorString = cgGetErrorString(cgGetError());
        const char* listing = cgGetLastListing(GFX->getCGContext());
        for( i = 0; i < macros.size(); i++ )
        {
           Con::printf(args[i]);
        }
        Con::printf(cgSource);
        Con::printf("Failed to compile cg program (%s) : %s\r\n%s", cgFile.getFullPath().c_str(), errorString, listing);
        AssertFatal(0, "Failed to compile cg program");
    }

    Platform::createPath("shaderDebug");
    Torque::Path output(String("./shaderDebug/") + cgFile.getFileName());
    if( s.open(output, Torque::FS::File::Write) )
    {
        for( i = 0; i < macros.size(); i++ )
        {
            if( args[i] )
            {
                s.write(strlen(args[i]), args[i]);
                s.write(2, "\r\n");
            }
        }
        s.write(bufSize, cgSource);
        s.close();
    }

    for( i = 0; i < macros.size(); i++ )
    {
        if( args[i] )
            free(args[i]);
    }
    free(args);



    return prg;
}

const Vector<GFXShaderConstDesc>& GFXCGShader::getShaderConstDesc() const
{
    return mShaderConsts;
}

U32 GFXCGShader::getAlignmentValue(const GFXShaderConstType constType) const
{   
    const U32 mRowSizeF = 16;
    const U32 mRowSizeI = 16;

    switch (constType)
    {
        case GFXSCT_Float :
        case GFXSCT_Float2 :
        case GFXSCT_Float3 : 
        case GFXSCT_Float4 :
            return mRowSizeF;
            break;
            // Matrices
        case GFXSCT_Float2x2 :
            return mRowSizeF * 2;
            break;
        case GFXSCT_Float3x3 : 
            return mRowSizeF * 3;
            break;
        case GFXSCT_Float4x4 :
            return mRowSizeF * 4;
            break;   
            //// Scalar
        case GFXSCT_Int :
        case GFXSCT_Int2 :
        case GFXSCT_Int3 : 
        case GFXSCT_Int4 :
            return mRowSizeI;
            break;
        default:
            AssertFatal(false, "Unsupported type!");
            return 0;
            break;
    }
}


GFXCGShaderConstHandle::GFXCGShaderConstHandle(CGparameter vparam, CGparameter pparam, const String& name)
    : mName(name),
    mVParam(vparam),
    mPParam(pparam)
{
    mValid = true;
    mVType = vparam ? GFXCGShader::GFXTypeFromCGType(vparam) : GFXSCT_Unknown;
    mPType = pparam ? GFXCGShader::GFXTypeFromCGType(pparam) : GFXSCT_Unknown;
}

GFXShaderConstType GFXCGShaderConstHandle::getType() const  
{ 
    if( mVParam )
        return mVType;
    if( mPParam )
        return mPType;
    return GFXSCT_Unknown; 
}

U32 GFXCGShaderConstHandle::getArraySize() const            
{
    U32 size = 0;

    if( mVParam )
        size = cgGetArraySize(mVParam, 0);
    else if( mPParam )
        size = cgGetArraySize(mPParam, 0);

    return size; 
} 
    
S32 GFXCGShaderConstHandle::getSamplerRegister() const
{ 
    S32 sampler = -1;
    if( mVType == GFXSCT_Sampler )
    {
        sampler = cgGetParameterResourceIndex(mVParam);
    }
    else if( mPType == GFXSCT_Sampler )
    {
        sampler = cgGetParameterResourceIndex(mPParam);
    }

    return sampler; 
}

void GFXCGShaderConstHandle::_validate(CGprogram program, CGparameter& param)
{
    if( param && cgIsParameter(param) != CG_TRUE )
    {
        param = cgGetNamedParameter(program, mName.c_str());
    }
}

void GFXCGShaderConstHandle::validate(GFXCGShader* shader)
{
    _validate(shader->getCGVertexProgram(), mVParam);
    _validate(shader->getCGPixelProgram(), mPParam);
}

GFXShaderConstType GFXCGShader::GFXTypeFromCGType(CGparameter param, CGtype type)
{
    GFXShaderConstType gfxType = GFXSCT_Unknown;
    if( type == CG_UNKNOWN_TYPE )
        type = cgGetParameterType(param);
    switch( type )
    {
        case CG_ARRAY:
            gfxType = GFXTypeFromCGType(param, cgGetArrayType(param));
            break;
        case CG_SAMPLER:
        case CG_SAMPLER2D:
            gfxType = GFXSCT_Sampler;
            break;  
        case CG_SAMPLERCUBE:
            gfxType = GFXSCT_SamplerCube;
            break;
        case CG_FLOAT:             
        case CG_FLOAT1:    
            gfxType = GFXSCT_Float;
            break;
        case CG_FLOAT2:
            gfxType = GFXSCT_Float2;
            break;
        case CG_FLOAT3:
            gfxType = GFXSCT_Float3;
            break;
        case CG_FLOAT4:
            gfxType = GFXSCT_Float4;
            break;
        case CG_FLOAT2x2:
            gfxType = GFXSCT_Float2x2;
            break;
        case CG_FLOAT3x3:
            gfxType = GFXSCT_Float3x3;
            break; 
        case CG_FLOAT4x4:
            gfxType = GFXSCT_Float4x4;
            break;
        case CG_INT:
        case CG_INT1:
            gfxType = GFXSCT_Int;
            break;
        case CG_INT2:
            gfxType = GFXSCT_Int2;
            break;
        case CG_INT3:
            gfxType = GFXSCT_Int3;
            break;
        case CG_INT4:
            gfxType = GFXSCT_Int4;
            break;
        case CG_STRUCT:
            gfxType = GFXSCT_Struct;
            break;
        default:
            Con::printf("Unsupported shader param type: %s", cgGetTypeString(type));
            gfxType = GFXSCT_Unknown;
            break;
    }

    return gfxType;
}

GFXShaderConstHandle* GFXCGShader::getShaderConstHandle(const String& name)
{
    GFXShaderConstHandle* handle = 0;
    if( mCGVertexProgram || mCGPixelProgram )
    {
        String stripped(name);
        if( name[0] == '$' )
            stripped.erase(0, 1);


        CGHandleMap::Iterator i = mCGHandles.find(stripped);
        if ( i != mCGHandles.end() )
        {
            i->value->validate(this);
            return i->value;
        } 
        else 
        {
            CGprogram vprog = mCGVertexProgram;
            CGparameter vparam = cgGetNamedParameter(vprog, stripped.c_str());
            CGparameter pparam = mCGPixelProgram ? cgGetNamedParameter(mCGPixelProgram, stripped.c_str()) : 0;
            GFXCGShaderConstHandle* cgHandle = new GFXCGShaderConstHandle(vparam, pparam, stripped);
            mCGHandles[stripped] = cgHandle;
            handle = cgHandle;
            cgHandle->setValid(( vparam || pparam ));            
        }      
    }

    return handle;
}

GFXShaderConstBufferRef GFXCGShader::allocConstBuffer()
{
    if( GFX->getAdapterType() == OpenGL )
    {
        if( !mConstBuffer )
        {
            mConstBuffer = new GFXCGShaderConstBuffer(this);
        }

        return mConstBuffer;
    }
    else
    {
        GFXShaderConstBuffer* buffer = new GFXCGShaderConstBuffer(this);
        return buffer;
    }
}
    
// This is only intended to be called from the destructor of the const buffer
void GFXCGShader::destroyConstBuffer(GFXShaderConstBuffer* buffer)
{
    if( buffer == mConstBuffer )
        mConstBuffer = 0;
}


GFXCGShaderConstBuffer::GFXCGShaderConstBuffer( GFXShader* shader )
    : mShader(shader)
{
    GFXCGShader* cgShader = (GFXCGShader*)shader;
    //Con::printf("Setting up const buffer for shader: %s", mShader->getVertexShaderFile().c_str());
    //_dumpParameters(cgShader->getCGVertexProgram());
    //Con::printf("Setting up const buffer for shader: %s", mShader->getPixelShaderFile().c_str());
    //_dumpParameters(cgShader->getCGPixelProgram());

    if( GFX->getAdapterType() == OpenGL )
    {
        mVertexParamsF = 0;
        mVertexParamsI = 0;
        mPixelParamsF = 0;
        mPixelParamsI = 0;
    }
    else
    {
        mVertexParamsF = _allocateParameterBufferF(cgShader->getCGVertexProgram(), mNumVertexParamsF);
        mVertexParamsI = _allocateParameterBufferI(cgShader->getCGVertexProgram(), mNumVertexParamsI);
        mPixelParamsF = _allocateParameterBufferF(cgShader->getCGPixelProgram(), mNumPixelParamsF);
        mPixelParamsI = _allocateParameterBufferI(cgShader->getCGPixelProgram(), mNumPixelParamsI);
    }
}

GFXCGShaderConstBuffer::~GFXCGShaderConstBuffer()
{
    GFXCGShader* cgShader = (GFXCGShader*)mShader;
    cgShader->destroyConstBuffer(this);
    if( mVertexParamsF )
    {
        free(mVertexParamsF);
        mVertexParamsF = 0;
    }
    if( mVertexParamsI )
    {
        free(mVertexParamsI);
        mVertexParamsI = 0;
    }
    if( mPixelParamsF )
    {
        free(mPixelParamsF);
        mPixelParamsF = 0;
    }
    if( mPixelParamsI )
    {
        free(mPixelParamsI);
        mPixelParamsI = 0;
    }
}

F32* GFXCGShaderConstBuffer::_allocateParameterBufferF(CGprogram program, S32& outNumParameters)
{
    // Count the number of float parameters
    outNumParameters = 0;
    bool bGlobalMode = true;
    CGparameter param = cgGetFirstParameter(program, CG_GLOBAL);
    while( param )
    {
        CGtype type = cgGetParameterType(param);
        if( type != CG_UNKNOWN_TYPE )
        {
            GFXShaderConstType gfxType = GFXCGShader::GFXTypeFromCGType(param);
            if( gfxType == GFXSCT_Unknown )
            {
                Con::printf("Unsupported parameter type for param (%s)", cgGetParameterName(param));
            }
        }
        
        switch( type )
        {
            case CG_ARRAY:
                {
                    CGtype arrayType = cgGetArrayType(param);
                    switch( arrayType )
                    {
                        case CG_FLOAT:
                        case CG_FLOAT1:
                        case CG_FLOAT2:
                        case CG_FLOAT3:
                        case CG_FLOAT4:
                            outNumParameters += cgGetArraySize(param, 0);
                            break;
                    }
                }
                break;
            case CG_FLOAT:
            case CG_FLOAT1:
            case CG_FLOAT2:
            case CG_FLOAT3:
            case CG_FLOAT4:
                outNumParameters++;
                break;
            case CG_FLOAT2x2:
                outNumParameters += 2;
                break;
            case CG_FLOAT3x3:
                outNumParameters += 3;
                break;
            case CG_FLOAT4x4:
                outNumParameters += 4;
                break;
        }        
        param = cgGetNextParameter(param);
        if( !param && bGlobalMode )
        {
            bGlobalMode = false;
            param = cgGetFirstParameter(program, CG_PROGRAM);
        }
    }

    F32* buffer = 0;

    if( outNumParameters > 0 )
    {
        // Allocate space
        buffer = (F32*)malloc(sizeof(F32) * 4 * outNumParameters);
    }
    
    // Hand the buffer to the caller
    return buffer;
}

S32* GFXCGShaderConstBuffer::_allocateParameterBufferI(CGprogram program, S32& outNumParameters)
{
    // Count the number of float parameters
    outNumParameters = 0;
    bool bGlobalMode = true;
    CGparameter param = cgGetFirstParameter(program, CG_GLOBAL);
    while( param )
    {
        CGtype type = cgGetParameterType(param);
        switch( type )
        {
            case CG_ARRAY:
                {
                    CGtype arrayType = cgGetArrayType(param);
                    switch( arrayType )
                    {
                        case CG_INT:
                        case CG_INT1:
                        case CG_INT2:
                        case CG_INT3:
                        case CG_INT4:
                            outNumParameters += cgGetArraySize(param, 0);
                            break;
                    }
                }
                break;
            case CG_INT:
            case CG_INT1:
            case CG_INT2:
            case CG_INT3:
            case CG_INT4:
                outNumParameters++;
                break;
        }        
        param = cgGetNextParameter(param);
        if( !param && bGlobalMode )
        {
            bGlobalMode = false;
            param = cgGetFirstParameter(program, CG_PROGRAM);
        }
    }

    S32* buffer = 0;

    if( outNumParameters > 0 )
    {
        // Allocate space
        buffer = (S32*)malloc(sizeof(S32) * 4 * outNumParameters);
    }
    
    // Hand the buffer to the caller
    return buffer;
}

S32 GFXCGShaderConstBuffer::_getRegisterNumber(CGparameter param)
{
    if( cgGetParameterType(param) == CG_ARRAY )
    {
        param = cgGetArrayParameter(param, 0);
    }
    return cgGetParameterResourceIndex(param);
}

void GFXCGShaderConstBuffer::_setParam(CGparameter param, F32* paramBuffer, S32 numParams, const F32* values, S32 valueCount)
{
    if( param && valueCount )
    {
        
        /*
            char outStr[4096];
            dSprintf(outStr, sizeof(outStr), "cgSetParameterValuefr(%s %s, %d", cgGetTypeString(cgGetParameterType(param)), cgGetParameterName(param), valueCount);
            char value[256];
            for( int i = 0; i < valueCount; i++ )
            {
                dSprintf(value, sizeof(value), ", %f", values[i]);
                dStrcat(outStr, value);
            }
            dStrcat(outStr, ")");
            //Con::printf(outStr);
        */

        if( GFX->getAdapterType() == OpenGL )
        {
            //cgSetParameterValuefr(param, valueCount, values);
            CGtype type = cgGetParameterType(param);
            switch( type )
            {
                case CG_ARRAY:
                    switch( cgGetArrayType(param) )
                    {
                        case CG_FLOAT:
                        case CG_FLOAT1:
                        case CG_FLOAT2:
                        case CG_FLOAT3:
                            AssertFatal(0, "Need to work on this");
                            break;
                        case CG_FLOAT4:
                            cgGLSetParameterArray4f(param, 0, valueCount / 4, values);
                            break;
                    }
                    break;
                case CG_FLOAT:
                case CG_FLOAT1:
                    cgGLSetParameter1fv(param, values);
                    break;
                case CG_FLOAT2:
                    cgGLSetParameter2fv(param, values);
                    break;
                case CG_FLOAT3:
                    cgGLSetParameter3fv(param, values);
                    break;
                case CG_FLOAT4:
                    cgGLSetParameter4fv(param, values);
                    break;
                case CG_FLOAT2x2:
                case CG_FLOAT3x3:
                    AssertFatal(0, "Ugh");
                    break;
                case CG_FLOAT4x4:
                    cgGLSetMatrixParameterfr(param, values);
                    break;
                default:
                    Con::printf("setting unsupported param type: %s", cgGetTypeString(type));
                    break;
            }

        }
        else
        {
            int registerNumber = _getRegisterNumber(param);
            if( registerNumber < numParams )
            {
                S32 valueLines = ((valueCount - 1) / 4) + 1;
                bool shouldWrite = (registerNumber + valueLines) <= numParams;
                AssertFatal(shouldWrite, "Setting this parameter would overwrite the allocated buffer!");
                if( shouldWrite )
                    _write(paramBuffer, registerNumber, values, valueCount);
            }
            else
            {
                Con::printf("Invalid ordinal number (%d/%d) for parameter (%s) in shader: %s", registerNumber, numParams, cgGetParameterName(param), mShader->getPixelShaderFile().c_str());
                Con::printf("");
                GFXCGShader* shader = (GFXCGShader*)mShader;
                _dumpCGParameters(shader->getCGVertexProgram());
                Con::printf("");
                _dumpCGParameters(shader->getCGPixelProgram());
            }
        }
    }
}

void GFXCGShaderConstBuffer::_setParam(CGparameter param, S32* paramBuffer, S32 numParams, const S32* values, S32 valueCount)
{
    if( param && valueCount )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            cgSetParameterValueir(param, valueCount, values);
        }
        else
        {
            int registerNumber = _getRegisterNumber(param);
            if( registerNumber < numParams )
            {
                S32 valueLines = ((valueCount - 1) / 4) + 1;
                bool shouldWrite = (registerNumber + valueLines) <= numParams;
                AssertFatal(shouldWrite, "Setting this parameter would overwrite the allocated buffer!");
                if( shouldWrite )
                    _write(paramBuffer, registerNumber, values, valueCount);
            }
        }
    }
}

void GFXCGShaderConstBuffer::_write(F32* paramBuffer, S32 index, const F32* values, S32 valueCount)
{
    F32* writePointer = paramBuffer + (index * 4);
    memcpy(writePointer, values, valueCount * sizeof(F32));
}

void GFXCGShaderConstBuffer::_write(S32* paramBuffer, S32 index, const S32* values, S32 valueCount)
{
    S32* writePointer = paramBuffer + (index * 4);
    memcpy(writePointer, values, valueCount * sizeof(S32));
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const F32 f)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, &f, 1);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, &f, 1);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2F& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, &fv.x, 2);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, &fv.x, 2);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3F& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, &fv.x, 3);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, &fv.x, 3);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4F& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, &fv.x, 4);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, &fv.x, 4);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const PlaneF& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, &fv.x, 4);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, &fv.x, 4);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const ColorF& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, &fv.red, 4);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, &fv.red, 4);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const S32 f)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, &f, 1);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, &f, 1);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point2I& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, &fv.x, 2);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, &fv.x, 2);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point3I& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, &fv.x, 3);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, &fv.x, 3);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const Point4I& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, &fv.x, 4);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, &fv.x, 4);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv)
{
    int floatCount = fv.size() * 4;
    F32* temp = (F32*)malloc(floatCount * sizeof(float));
    for( int i = 0; i < fv.size(); i++ )
    {
        int tempIndex = i * 4;
        temp[tempIndex] = fv[i];
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, temp, floatCount);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, temp, floatCount);

    free(temp);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv)
{
    int floatCount = fv.size() * 4;
    F32* temp = (F32*)malloc(floatCount * sizeof(float));
    for( int i = 0; i < fv.size(); i++ )
    {
        int tempIndex = i * 4;
        temp[tempIndex] = fv[i].x;
        temp[tempIndex + 1] = fv[i].y;
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, temp, floatCount);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, temp, floatCount);

    free(temp);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv)
{
    int floatCount = fv.size() * 4;
    F32* temp = (F32*)malloc(floatCount * sizeof(float));
    for( int i = 0; i < fv.size(); i++ )
    {
        int tempIndex = i * 4;
        temp[tempIndex] = fv[i].x;
        temp[tempIndex + 1] = fv[i].y;
        temp[tempIndex + 2] = fv[i].z;
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, temp, floatCount);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, temp, floatCount);

    free(temp);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, (const F32*)fv.getBuffer(), fv.size() * 4);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, (const F32*)fv.getBuffer(), fv.size() * 4);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv)
{
    int intCount = fv.size() * 4;
    S32* temp = (S32*)malloc(intCount * sizeof(S32));
    for( int i = 0; i < fv.size(); i++ )
    {
        int tempIndex = i * 4;
        temp[tempIndex] = fv[i];
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, temp, intCount);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, temp, intCount);

    free(temp);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv)
{
    int intCount = fv.size() * 4;
    S32* temp = (S32*)malloc(intCount * sizeof(S32));
    for( int i = 0; i < fv.size(); i++ )
    {
        int tempIndex = i * 4;
        temp[tempIndex] = fv[i].x;
        temp[tempIndex + 1] = fv[i].y;
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, temp, intCount);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, temp, intCount);

    free(temp);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv)
{
    int intCount = fv.size() * 4;
    S32* temp = (S32*)malloc(intCount * sizeof(S32));
    for( int i = 0; i < fv.size(); i++ )
    {
        int tempIndex = i * 4;
        temp[tempIndex] = fv[i].x;
        temp[tempIndex + 1] = fv[i].y;
        temp[tempIndex + 2] = fv[i].z;
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, temp, intCount);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, temp, intCount);

    free(temp);
}

void GFXCGShaderConstBuffer::set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv)
{
    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsI, mNumVertexParamsI, (const S32*)fv.getBuffer(), fv.size() * 4);
    _setParam(cgParam->getPParameter(), mPixelParamsI, mNumPixelParamsI, (const S32*)fv.getBuffer(), fv.size() * 4);
}

void GFXCGShaderConstBuffer::set( GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType )
{
    S32 floatCount = 0;
    switch( matrixType )
    {
        case GFXSCT_Float2x2:
            floatCount = 8;
            break;
        case GFXSCT_Float3x3:
            floatCount = 12;
            break;
        case GFXSCT_Float4x4:
            floatCount = 16;
            break;
        default:
            AssertFatal(0, "Unknown matrix type passed to GFXCGShaderConstBuffer::set");
            return;
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    cgParam->validate((GFXCGShader*)mShader);
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, &mat[0], floatCount);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, &mat[0], floatCount);
}

void GFXCGShaderConstBuffer::set( GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType )
{    
    S32 floatCount = 0;
    switch( matrixType )
    {
        case GFXSCT_Float2x2:
            floatCount = 8;
            break;
        case GFXSCT_Float3x3:
            floatCount = 12;
            break;
        case GFXSCT_Float4x4:
            floatCount = 16;
            break;
        default:
            AssertFatal(0, "Unknown matrix type passed to GFXCGShaderConstBuffer::set");
            return;
    }
    S32 totalFloatCount = floatCount * arraySize;
    F32* temp = (F32*)malloc(totalFloatCount * sizeof(F32));
    for( U32 i = 0; i < arraySize; i++ )
    {
        S32 tempIndex = i * floatCount;
        memcpy(&temp[tempIndex], &mat[i], floatCount * sizeof(F32));
    }

    GFXCGShaderConstHandle* cgParam = (GFXCGShaderConstHandle*)handle;
    _setParam(cgParam->getVParameter(), mVertexParamsF, mNumVertexParamsF, temp, totalFloatCount);
    _setParam(cgParam->getPParameter(), mPixelParamsF, mNumPixelParamsF, temp, totalFloatCount);

    free(temp);
}

const String GFXCGShaderConstBuffer::describeSelf() const
{
   String ret;
   ret = String("   GFXCGShaderConstBuffer\n");

   return ret;
}

void GFXCGShaderConstBuffer::zombify()
{
}

void GFXCGShaderConstBuffer::resurrect()
{
}

void GFXCGShaderConstBuffer::activate()
{
    if( GFX->getAdapterType() == OpenGL )
        return;

#ifdef WIN32
    if( mVertexParamsF )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            glUniform4fv(0, mNumVertexParamsF, mVertexParamsF);
        }
        else
        {
            GFXD3D9Device* device = static_cast<GFXD3D9Device*>( GFX );
            device->getDevice()->SetVertexShaderConstantF(0, mVertexParamsF, mNumVertexParamsF);
        }
    }
    if( mVertexParamsI )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            glUniform4iv(0, mNumVertexParamsI, mVertexParamsI);
        }
        else
        {
            GFXD3D9Device* device = static_cast<GFXD3D9Device*>( GFX );
            device->getDevice()->SetVertexShaderConstantI(0, mVertexParamsI, mNumVertexParamsI);
        }
    }
    if( mPixelParamsF )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            glUniform4fv(0, mNumPixelParamsF, mPixelParamsF);
        }
        else
        {
            GFXD3D9Device* device = static_cast<GFXD3D9Device*>( GFX );
            device->getDevice()->SetPixelShaderConstantF(0, mPixelParamsF, mNumPixelParamsF);
        }
    }
    if( mPixelParamsI )
    {
        if( GFX->getAdapterType() == OpenGL )
        {
            glUniform4iv(0, mNumPixelParamsI, mPixelParamsI);
        }
        else
        {
            GFXD3D9Device* device = static_cast<GFXD3D9Device*>( GFX );
            device->getDevice()->SetPixelShaderConstantI(0, mPixelParamsI, mNumPixelParamsI);
        }
    }
#endif
}