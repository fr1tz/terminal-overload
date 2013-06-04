// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADERGEN_GLSL_H_
#define _SHADERGEN_GLSL_H_

#ifndef _SHADERGEN_H_
#include "shaderGen/shaderGen.h"
#endif


class ShaderGenPrinterGLSL : public ShaderGenPrinter
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

class ShaderGenComponentFactoryGLSL : public ShaderGenComponentFactory
{
public:

   /// Helper function for converting a vertex decl 
   /// type to an GLSL type string.
   static const char* typeToString( GFXDeclType type );

   // ShaderGenComponentFactory
   virtual ShaderComponent* createVertexInputConnector( const GFXVertexFormat &vertexFormat );
   virtual ShaderComponent* createVertexPixelConnector();
   virtual ShaderComponent* createVertexParamsDef();
   virtual ShaderComponent* createPixelParamsDef();
};

#endif