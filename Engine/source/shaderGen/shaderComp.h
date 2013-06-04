// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _SHADERCOMP_H_
#define _SHADERCOMP_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _MISCSHDRDAT_H_
#include "materials/miscShdrDat.h"
#endif

class Stream;
struct Var;

//**************************************************************************
// Shader Component - these objects are the main logical breakdown of a
//    high level shader.  They represent the various data structures
//    and the main() procedure necessary to create a shader.
//**************************************************************************
class ShaderComponent
{
public:
   virtual ~ShaderComponent() {}
   
   virtual void print( Stream &stream ){};
};


//**************************************************************************
// Connector Struct Component - used for incoming Vertex struct and also the
//    "connection" struct shared by the vertex and pixel shader
//**************************************************************************
class ShaderConnector : public ShaderComponent
{
protected:
   enum Consts
   {
      NUM_TEX_REGS = 8,
   };

   enum Elements
   {
      POSITION = 0,
      NORMAL,
      COLOR,
      NUM_BASIC_ELEMS
   };

   Vector <Var*> mElementList;

   U32 mCurTexElem;
   U8 mName[32];

public:

   ShaderConnector();
   virtual ~ShaderConnector();

   ///
   virtual Var* getElement(   RegisterType type, 
                              U32 numElements = 1, 
                              U32 numRegisters = -1 ) = 0;

   virtual void setName( char *newName ) = 0;
   virtual void reset() = 0;
   virtual void sortVars() = 0;

   virtual void print( Stream &stream ) = 0;
};

/// This is to provide common functionalty needed by vertex and pixel main defs
class ParamsDef : public ShaderComponent
{
protected:
   virtual void assignConstantNumbers() {}
};

#endif // _SHADERCOMP_H_
