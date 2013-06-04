// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SIMOBJECTREF_H_
#define _SIMOBJECTREF_H_


#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

#ifndef _SIM_H_
#include "console/sim.h"
#endif



// SimObjectRef<T>

template< class T >
class SimObjectRef
{
public:         

   static S32 _smTypeId;

   SimObjectRef()
      : mId( 0 ),
        mObject( NULL ),
        mName( "" )
   {
   }
   
   T* operator-> () { return _get(); }   

   operator T*() { return _get(); }

   operator bool () { return _get() != NULL; }   

   SimObjectRef<T>& operator= ( U32 id )
   {
      _set( id );
      return *this;
   }

   SimObjectRef<T>& operator= ( const char *name )
   {
      _set( name );
      return *this;
   }

protected:

   T* _get();
   void _set( U32 id );      
   void _set( const char *name );      

protected:

   StringTableEntry mName;
   U32 mId;
   T *mObject;
};


// static initialization

template<class T>
S32 SimObjectRef<T>::_smTypeId = 0;


// inline methods

template<class T>
void SimObjectRef<T>::_set( const char *name )
{
   mName = StringTable->insert( name );
   mObject = NULL;
   mId = 0;
}

template<class T>
void SimObjectRef<T>::_set( U32 id )
{
   mId = id;   
   mObject = NULL;
   mName = "";
}

template<class T> 
T* SimObjectRef<T>::_get()
{  
   if ( mObject == NULL )   
   {
      if ( mId != 0 )
         Sim::findObject( mId, mObject );   
      else if ( mName != NULL && dStrlen( mName ) != 0 )
         Sim::findObject( mName, mObject );
   }

   return mObject;
}


// SimObjectRefConsoleBaseType<T>

template< class T >
class SimObjectRefConsoleBaseType : public ConsoleBaseType
{
public:

   typedef ConsoleBaseType Parent;
   
   SimObjectRefConsoleBaseType( const char *typeName )
      : Parent( sizeof(SimObjectRef<T>), &SimObjectRef<T>::_smTypeId, typeName ) 
   {
   }

public:

   virtual const char* getData( void *dptr, const EnumTable*, BitSet32 )
   {      
      SimObjectRef<T> *objRef = static_cast< SimObjectRef<T>* >( dptr );
      T *obj = *objRef;
      return T::__getObjectId( obj );
   }

   virtual void setData( void* dptr, S32 argc, const char** argv, const EnumTable*, BitSet32 )
   {
      SimObjectRef<T> *objRef = static_cast< SimObjectRef<T>* >( dptr );

      if ( argc != 1 ) 
         return;

      *objRef = argv[0];
   }

   virtual const bool isDatablock() 
   { 
      return T::__smIsDatablock; 
   };

   virtual const char* getTypeClassName()
   {
      return T::getStaticClassRep()->getClassName();
   }
      
   virtual void* getNativeVariable() 
   { 
      SimObjectRef<T> *var = new SimObjectRef<T>(); 
      return (void*)var; 
   }
   
   virtual void deleteNativeVariable( void *var ) 
   { 
      SimObjectRef<T> *nativeVar = reinterpret_cast< SimObjectRef<T>* >( var ); 
      delete nativeVar; 
   }   
};


#endif // _SIMOBJECTREF_H_