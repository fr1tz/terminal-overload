// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHADER_DEPENDENCY_H_
#define _SHADER_DEPENDENCY_H_

#ifndef _PATH_H_
#include "core/util/path.h"
#endif


class Stream;


/// The base class for shader dependencies
class ShaderDependency
{
public:
   virtual ~ShaderDependency() {}
   
   /// Compare this dependency to another one.
   virtual bool operator==( const ShaderDependency &cmpTo ) const 
   { 
      return this == &cmpTo; 
   }

   /// Print the dependency into the header of a shader.
   virtual void print( Stream &s ) const = 0;
};


/// A shader dependency for adding #include's into shadergen shaders.
class ShaderIncludeDependency : public ShaderDependency
{
protected:

   Torque::Path mIncludePath;

public:

   ShaderIncludeDependency( const Torque::Path &pathToInclude );

   virtual bool operator==( const ShaderDependency &cmpTo ) const;
   virtual void print( Stream &s ) const;
};

#endif // _SHADER_DEPENDENCY_H_