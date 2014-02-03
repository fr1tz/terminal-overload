// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADERCOMP_HLSL_H_
#define _SHADERCOMP_HLSL_H_

#ifndef _SHADERCOMP_H_
#include "shaderGen/shaderComp.h"
#endif


class ShaderConnectorHLSL : public ShaderConnector
{
public:

   // ShaderConnector
   virtual Var* getElement(   RegisterType type, 
                              U32 numElements = 1, 
                              U32 numRegisters = -1 );
   virtual Var* getIndexedElement(  U32 index,
                                    RegisterType type, 
                                    U32 numElements = 1, 
                                    U32 numRegisters = -1 );
       
   virtual void setName( char *newName );
   virtual void reset();
   virtual void sortVars();

   virtual void print( Stream &stream, bool isVertexShader );
};


class ParamsDefHLSL : public ParamsDef
{
protected:
   virtual void assignConstantNumbers();
};


class VertexParamsDefHLSL : public ParamsDefHLSL
{
public:
   virtual void print( Stream &stream, bool isVerterShader );
};


class PixelParamsDefHLSL : public ParamsDefHLSL
{
public:
   virtual void print( Stream &stream, bool isVerterShader );
};

#endif // _SHADERCOMP_HLSL_H_