// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADERMATERIALPARAMETERS_H_
#define _SHADERMATERIALPARAMETERS_H_

#ifndef _MATERIALPARAMETERS_H_
#include "materials/materialParameters.h"
#endif
#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif


class ShaderMaterialParameterHandle : public MaterialParameterHandle
{
   friend class ShaderMaterialParameters;
public:
   virtual ~ShaderMaterialParameterHandle();

   ShaderMaterialParameterHandle(const String& name);
   ShaderMaterialParameterHandle(const String& name, Vector<GFXShader*>& shaders);

   virtual const String& getName() const { return mName; } 
   virtual S32 getSamplerRegister( U32 pass ) const;

   // NOTE: We always return true here instead of querying the
   // children... often there is only one element, so lets just
   // hit the loop once on the set.
   virtual bool isValid() const { return true; };      

protected:
   Vector< GFXShaderConstHandle* > mHandles;   
   String mName;   
};

// This is the union of all of the shaders contained in a material
class ShaderMaterialParameters : public MaterialParameters
{
public:
   ShaderMaterialParameters();
   virtual ~ShaderMaterialParameters();

   void setBuffers(Vector<GFXShaderConstDesc>& constDesc, Vector<GFXShaderConstBufferRef>& buffers);   
   GFXShaderConstBuffer* getBuffer(U32 i) { return mBuffers[i]; }

   ///
   /// MaterialParameter interface
   ///

   /// Returns the material parameter handle for name.
   virtual void set(MaterialParameterHandle* handle, const F32 f);
   virtual void set(MaterialParameterHandle* handle, const Point2F& fv);
   virtual void set(MaterialParameterHandle* handle, const Point3F& fv);
   virtual void set(MaterialParameterHandle* handle, const Point4F& fv);
   virtual void set(MaterialParameterHandle* handle, const PlaneF& fv);
   virtual void set(MaterialParameterHandle* handle, const ColorF& fv);
   virtual void set(MaterialParameterHandle* handle, const S32 f);
   virtual void set(MaterialParameterHandle* handle, const Point2I& fv);
   virtual void set(MaterialParameterHandle* handle, const Point3I& fv);
   virtual void set(MaterialParameterHandle* handle, const Point4I& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<F32>& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point2F>& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point3F>& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point4F>& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<S32>& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point2I>& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point3I>& fv);
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point4I>& fv);
   virtual void set(MaterialParameterHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType = GFXSCT_Float4x4);
   virtual void set(MaterialParameterHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType = GFXSCT_Float4x4);

   virtual U32 getAlignmentValue(const GFXShaderConstType constType);

private:
   Vector<GFXShaderConstBufferRef> mBuffers;   

   void releaseBuffers();
};

#endif
