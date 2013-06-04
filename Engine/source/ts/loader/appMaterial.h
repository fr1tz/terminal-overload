// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _APPMATERIAL_H_
#define _APPMATERIAL_H_


struct AppMaterial
{
   U32 flags;
   F32 reflectance;

   AppMaterial() : flags(0), reflectance(1.0f) { }
   virtual ~AppMaterial() {}
   
   virtual String getName() const { return "unnamed"; }
   virtual U32 getFlags() { return flags; }
   virtual F32 getReflectance() { return reflectance; }
};

#endif // _APPMATERIAL_H_
