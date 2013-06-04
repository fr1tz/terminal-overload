// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADERGEN_HLSL_H_
#define _SHADERGEN_HLSL_H_

#ifndef _SHADERGEN_H_
#include "shaderGen/shaderGen.h"
#endif


class ShaderGenPrinterHLSL : public ShaderGenPrinter
{
public:

   // ShaderGenPrinter
   virtual void printShaderHeader(Stream& stream);
   virtual void printMainComment(Stream& stream);
   virtual void printVertexShaderCloser(Stream& stream);
   virtual void printPixelShaderOutputStruct(Stream& stream, const MaterialFeatureData &featureData);
   virtual void printPixelShaderCloser(Stream& stream);
   virtual void printLine(Stream& stream, const String& line);
};

class ShaderGenComponentFactoryHLSL : public ShaderGenComponentFactory
{
public:

   /// Helper function for converting a vertex decl 
   /// type to an HLSL type string.
   static const char* typeToString( GFXDeclType type );

   // ShaderGenComponentFactory
   virtual ShaderComponent* createVertexInputConnector( const GFXVertexFormat &vertexFormat );
   virtual ShaderComponent* createVertexPixelConnector();
   virtual ShaderComponent* createVertexParamsDef();
   virtual ShaderComponent* createPixelParamsDef();
};


#endif // _SHADERGEN_HLSL_H_