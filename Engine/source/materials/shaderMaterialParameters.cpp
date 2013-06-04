// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "materials/shaderMaterialParameters.h"

#include "console/console.h"

//
// ShaderMaterialParameters
//
ShaderMaterialParameterHandle::ShaderMaterialParameterHandle(const String& name)
{
   VECTOR_SET_ASSOCIATION( mHandles );

   mName = name;
}

ShaderMaterialParameterHandle::ShaderMaterialParameterHandle(const String& name, Vector<GFXShader*>& shaders)
{
   VECTOR_SET_ASSOCIATION( mHandles );

   mName = name;
   mHandles.setSize(shaders.size());

   for (U32 i = 0; i < shaders.size(); i++)
      mHandles[i] = shaders[i]->getShaderConstHandle(name);
}

ShaderMaterialParameterHandle::~ShaderMaterialParameterHandle()
{
}

S32 ShaderMaterialParameterHandle::getSamplerRegister( U32 pass ) const
{
   AssertFatal( mHandles.size() > pass, "ShaderMaterialParameterHandle::getSamplerRegister - out of bounds" );   
   return mHandles[pass]->getSamplerRegister();
}

//
// ShaderMaterialParameters
//
ShaderMaterialParameters::ShaderMaterialParameters()
: MaterialParameters()
{
   VECTOR_SET_ASSOCIATION( mBuffers );
}

ShaderMaterialParameters::~ShaderMaterialParameters()
{
   releaseBuffers();   
}

void ShaderMaterialParameters::setBuffers(Vector<GFXShaderConstDesc>& constDesc, Vector<GFXShaderConstBufferRef>& buffers)
{
   mShaderConstDesc = constDesc;
   mBuffers = buffers;
}

void ShaderMaterialParameters::releaseBuffers()
{
   for (U32 i = 0; i < mBuffers.size(); i++)
   {
      mBuffers[i] = NULL;
   }
   mBuffers.setSize(0);
}

U32 ShaderMaterialParameters::getAlignmentValue(const GFXShaderConstType constType)
{
   if (mBuffers.size() > 0)
      return mBuffers[0]->getShader()->getAlignmentValue(constType);
   else
      return 0;
}

#define SHADERMATPARAM_SET(handle, f) \
   AssertFatal(handle, "Handle is NULL!" ); \
   AssertFatal(handle->isValid(), "Handle is not valid!" ); \
   AssertFatal(dynamic_cast<ShaderMaterialParameterHandle*>(handle), "Invalid handle type!"); \
   ShaderMaterialParameterHandle* h = static_cast<ShaderMaterialParameterHandle*>(handle); \
   AssertFatal(h->mHandles.size() == mBuffers.size(), "Handle length differs from buffer length!"); \
   for (U32 i = 0; i < h->mHandles.size(); i++) \
{ \
   GFXShaderConstHandle* shaderHandle = h->mHandles[i]; \
   if (shaderHandle->isValid()) \
      mBuffers[i]->set(shaderHandle, f); \
} 

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const F32 f)
{
   SHADERMATPARAM_SET(handle, f);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const Point2F& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const Point3F& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const Point4F& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const PlaneF& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const ColorF& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const S32 f)
{
   SHADERMATPARAM_SET(handle, f);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const Point2I& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const Point3I& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const Point4I& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<F32>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<Point2F>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<Point3F>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<Point4F>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<S32>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<Point2I>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<Point3I>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const AlignedArray<Point4I>& fv)
{
   SHADERMATPARAM_SET(handle, fv);
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType)
{
   if ((!handle) || !handle->isValid())
      return;
   AssertFatal(dynamic_cast<ShaderMaterialParameterHandle*>(handle), "Invalid handle type!");
   ShaderMaterialParameterHandle* h = static_cast<ShaderMaterialParameterHandle*>(handle);
   AssertFatal(h->mHandles.size() == mBuffers.size(), "Handle length differs from buffer length!");
   for (U32 i = 0; i < h->mHandles.size(); i++)
   {
      GFXShaderConstHandle* shaderHandle = h->mHandles[i];
      if (shaderHandle && shaderHandle->isValid())
         mBuffers[i]->set(shaderHandle, mat, matrixType);
   } 
}

void ShaderMaterialParameters::set(MaterialParameterHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType)
{
   if ((!handle) || !handle->isValid())
      return;
   AssertFatal(dynamic_cast<ShaderMaterialParameterHandle*>(handle), "Invalid handle type!");
   ShaderMaterialParameterHandle* h = static_cast<ShaderMaterialParameterHandle*>(handle);
   AssertFatal(h->mHandles.size() == mBuffers.size(), "Handle length differs from buffer length!");
   for (U32 i = 0; i < h->mHandles.size(); i++)
   {
      GFXShaderConstHandle* shaderHandle = h->mHandles[i];
      if (shaderHandle && shaderHandle->isValid())
         mBuffers[i]->set(shaderHandle, mat, arraySize, matrixType);
   } 
}

#undef SHADERMATPARAM_SET
