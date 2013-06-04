// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "materials/baseMatInstance.h"

#include "core/util/safeDelete.h"


BaseMatInstance::~BaseMatInstance()
{
   deleteAllHooks();
}

void BaseMatInstance::addHook( MatInstanceHook *hook )
{
   AssertFatal( hook, "BaseMatInstance::addHook() - Got null hook!" );

   const MatInstanceHookType &type = hook->getType();

   while ( mHooks.size() <= type )
      mHooks.push_back( NULL );

   delete mHooks[type];
   mHooks[type] = hook;
}

MatInstanceHook* BaseMatInstance::getHook( const MatInstanceHookType &type ) const
{
   if ( type >= mHooks.size() )
      return NULL;

   return mHooks[ type ];
}

void BaseMatInstance::deleteHook( const MatInstanceHookType &type )
{
   if ( type >= mHooks.size() )
      return;

   delete mHooks[ type ];
   mHooks[ type ] = NULL;
}

U32 BaseMatInstance::deleteAllHooks()
{
   U32 deleteCount = 0;

   Vector<MatInstanceHook*>::iterator iter = mHooks.begin();
   for ( ; iter != mHooks.end(); iter++ )
   {
      if ( *iter )
      {
         delete (*iter);
         (*iter) = NULL;
         ++deleteCount;
      }
   }

   return deleteCount;
}