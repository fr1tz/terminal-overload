// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PHYSX_MATERIAL_H
#define _PHYSX_MATERIAL_H

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif
#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

class NxMaterial;

class PxMaterial : public SimDataBlock 
{
   typedef SimDataBlock Parent;

protected:

   F32 restitution;
   F32 staticFriction;
   F32 dynamicFriction;

   NxMaterial *mNxMat;
   S32 mNxMatId;

   bool mServer;

public:

   DECLARE_CONOBJECT( PxMaterial );

   PxMaterial();
   ~PxMaterial();

   static void consoleInit();
   static void initPersistFields();
   virtual void onStaticModified( const char *slotName, const char *newValue );

   bool preload( bool server, String &errorBuffer );
   virtual void packData( BitStream* stream );
   virtual void unpackData( BitStream* stream );

   S32 getMaterialId() const { return mNxMatId; }

};

#endif // _PHYSX_MATERIAL_H