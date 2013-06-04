// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADERCOMP_GLSL_H_
#define _SHADERCOMP_GLSL_H_

#ifndef _SHADERCOMP_H_
#include "shaderGen/shaderComp.h"
#endif


class VertPixelConnectorGLSL : public ShaderConnector
{
public:

   // ShaderConnector
   virtual Var* getElement(   RegisterType type, 
                              U32 numElements = 1, 
                              U32 numRegisters = -1 );
   virtual void setName( char *newName );
   virtual void reset();
   virtual void sortVars();

   virtual void print( Stream &stream );
};

class AppVertConnectorGLSL : public ShaderConnector
{
public:
   virtual Var* getElement(   RegisterType type, 
                              U32 numElements = 1, 
                              U32 numRegisters = -1 );
   virtual void setName( char *newName );
   virtual void reset();
   virtual void sortVars();
   
   virtual void print( Stream &stream );
};


class VertexParamsDefGLSL : public ParamsDef
{
public:
   virtual void print( Stream &stream );
};


class PixelParamsDefGLSL : public ParamsDef
{
public:
   virtual void print( Stream &stream );
};

#endif // _SHADERCOMP_GLSL_H_