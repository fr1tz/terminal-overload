// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "materials/matTextureTarget.h"

#include "console/console.h"
#include "platform/profiler.h"
#include "shaderGen/conditionerFeature.h"
#include "gfx/gfxTextureObject.h"
#include "gfx/gfxStructs.h"


NamedTexTarget::TargetMap NamedTexTarget::smTargets;


bool NamedTexTarget::registerWithName( const String &name )
{
   if ( mIsRegistered )
   {
      // If we're already registered with
      // this name then do nothing.
      if ( mName == name )
         return true;

      // Else unregister ourselves first.
      unregister();
   }

   // Make sure the target name isn't empty or already taken.
   if ( name.isEmpty() || smTargets.contains( name ) )
      return false;

   mName = name;
   mIsRegistered = true;
   smTargets.insert( mName, this );
   return true;
}

void NamedTexTarget::unregister()
{
   if ( !mIsRegistered )
      return;

   TargetMap::Iterator iter = smTargets.find( mName );

   AssertFatal( iter != smTargets.end() &&
                iter->value == this,
      "NamedTexTarget::unregister - Bad registration!" );

   mIsRegistered = false;
   mName = String::EmptyString;
   smTargets.erase( iter );
}

NamedTexTarget* NamedTexTarget::find( const String &name )
{
   PROFILE_SCOPE( NamedTexTarget_find );

   TargetMap::Iterator iter = smTargets.find( name );
   if ( iter != smTargets.end() )
      return iter->value;
   else
      return NULL;
}

NamedTexTarget::NamedTexTarget()
   :  mViewport( RectI::One ),
      mIsRegistered( false ),
      mConditioner( NULL )
{   
}

NamedTexTarget::~NamedTexTarget()
{
   unregister();
}

void NamedTexTarget::setTexture( U32 index, GFXTextureObject *tex )
{
   AssertFatal( index < 4, "NamedTexTarget::setTexture - Got invalid index!" );
   mTex[index] = tex;
}

void NamedTexTarget::release()
{
   mTex[0] = NULL;
   mTex[1] = NULL;
   mTex[2] = NULL;
   mTex[3] = NULL;
}

void NamedTexTarget::getShaderMacros( Vector<GFXShaderMacro> *outMacros )
{
   ConditionerFeature *cond = getConditioner();
   if ( !cond )
      return;

   // TODO: No check for duplicates is 
   // going on here which might be a problem?

   String targetName = String::ToLower( mName );

   // Add both the condition and uncondition macros.
   const String &condMethod = cond->getShaderMethodName( ConditionerFeature::ConditionMethod );
   if ( condMethod.isNotEmpty() )
   {
      GFXShaderMacro macro;
      macro.name = targetName + "Condition";
      macro.value = condMethod;
      outMacros->push_back( macro );
   }

   const String &uncondMethod = cond->getShaderMethodName( ConditionerFeature::UnconditionMethod );
   if ( uncondMethod.isNotEmpty() )
   {   
      GFXShaderMacro macro;
      macro.name = targetName + "Uncondition";
      macro.value = uncondMethod;
      outMacros->push_back( macro );
   }
}