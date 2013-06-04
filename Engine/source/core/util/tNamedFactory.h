// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TFACTORY_H_
#define _TFACTORY_H_

#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif


/// A helper template class for registering creation 
/// methods to name strings.
template <typename Type>
class NamedFactory
{
protected:

   typedef Type*(*FactorySig)();

   typedef Map<String,FactorySig> FactoryMap;

   ///
   static FactoryMap& getFactoryMap()
   {
      static FactoryMap theMap;
      return theMap;
   }

public:

   /// Add a new creation method to the factory.
   static void add( const char *name, FactorySig func )
   {
      getFactoryMap().insert( name, func );
   }

   /// Create an object instance by name.
   static Type* create( const char *name )
   {
      typename FactoryMap::Iterator iter = getFactoryMap().find( name );
      if ( iter == getFactoryMap().end() )
         return NULL;

      return iter->value();
   }

   /// Create an object instance of the first entry in the factory.
   static Type* create()
   {
      typename FactoryMap::Iterator iter = getFactoryMap().begin();
      if ( iter == getFactoryMap().end() )
         return NULL;

      return iter->value();
   }
};


#endif //_TFACTORY_H_

