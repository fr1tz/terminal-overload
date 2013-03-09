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
   bool mTexCoordMap[NUM_TEX_REGS];
   U8 mName[32];

public:

   ShaderConnector();
   virtual ~ShaderConnector();

   ///
   virtual Var* getElement(   RegisterType type, 
                              U32 numElements = 1, 
                              U32 numRegisters = 1 );
   virtual Var* getIndexedElement(  S32 index,
                                    RegisterType type, 
                                    U32 numElements = 1, 
                                    U32 numRegisters = 1 );

   virtual void setName( char *newName );
   virtual void reset();
   virtual void sortVars();

   virtual void print( Stream &stream );

private:
    S32 _allocTexCoord(U32 numRegistersNeeded, S32 requestedIndex = -1);
    bool _isTexCoordBlockAvailable(S32 index, U32 numRegistersNeeded);
    void _setTexCoordBlockAllocated(S32 index, U32 numRegisters);
};

/// This is to provide common functionalty needed by vertex and pixel main defs
class ParamsDef : public ShaderComponent
{
protected:
   virtual void assignConstantNumbers();
};

class VertexParamsDef : public ParamsDef
{
public:
   virtual void print( Stream &stream );
};


class PixelParamsDef : public ParamsDef
{
public:
   virtual void print( Stream &stream );
};

#endif // _SHADERCOMP_H_
