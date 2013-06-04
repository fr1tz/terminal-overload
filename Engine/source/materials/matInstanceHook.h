// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MATINSTANCEHOOK_H_
#define _MATINSTANCEHOOK_H_

#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif


/// The hook type wrapper object
class MatInstanceHookType
{
protected:

   typedef HashTable<String,U32> TypeMap;

   /// Returns the map of all the hook types.  We create
   /// it as a method static so that its available to other
   /// statics regardless of initialization order.
   static inline TypeMap& getTypeMap()
   {
      static TypeMap smTypeMap;
      return smTypeMap;
   }

   /// The hook type index for this type.
   U32 mTypeIndex;

public:

   MatInstanceHookType( const char *type );

   inline MatInstanceHookType( const MatInstanceHookType &type )
      : mTypeIndex( type.mTypeIndex )
   {
   }

   inline operator U32 () const { return mTypeIndex; }
};


/// This class is used to define hook objects attached to
/// material instances and provide a registration system
/// for different hook types.
///
/// @see BaseMatInstance
/// @see MaterialManager
///
class MatInstanceHook
{
public:

   ///
   virtual ~MatInstanceHook() {}

   /// 
   virtual const MatInstanceHookType& getType() const = 0;
};

#endif // _MATINSTANCEHOOK_H_






