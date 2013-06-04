// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GBUFFER_CONDITIONER_GLSL_H_
#define _GBUFFER_CONDITIONER_GLSL_H_

#ifndef _CONDITIONER_BASE_H_
#include "shaderGen/conditionerFeature.h"
#endif
#ifndef _SHADEROP_H_
#include "shaderGen/shaderOp.h"
#endif


///
class GBufferConditionerGLSL : public ConditionerFeature
{
   typedef ConditionerFeature Parent;

public:
   enum NormalStorage
   {
      CartesianXYZ,
      CartesianXY,
      Spherical,
   };
   
protected:

   NormalStorage mNormalStorageType;
   bool mCanWriteNegativeValues;
   U32 mBitsPerChannel;

public:

   GBufferConditionerGLSL( const GFXFormat bufferFormat );
   virtual ~GBufferConditionerGLSL();


   virtual void processVert( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual Resources getResources( const MaterialFeatureData &fd );
   virtual String getName() { return "GBuffer Conditioner"; }

protected:

   virtual Var *printMethodHeader( MethodType methodType, const String &methodName, Stream &stream, MultiLine *meta );

   virtual GenOp* _posnegEncode( GenOp *val );
   virtual GenOp* _posnegDecode( GenOp *val );
   virtual Var* _conditionOutput( Var *unconditionedOutput, MultiLine *meta );
   virtual Var* _unconditionInput( Var *conditionedInput, MultiLine *meta );
};

#endif // _GBUFFER_CONDITIONER_GLSL_H_
