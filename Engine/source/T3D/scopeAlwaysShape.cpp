// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "T3D/staticShape.h"

class ScopeAlwaysShape : public StaticShape
{
      typedef StaticShape Parent;

   public:
      ScopeAlwaysShape();
      static void initPersistFields();
      DECLARE_CONOBJECT(ScopeAlwaysShape);
};

ScopeAlwaysShape::ScopeAlwaysShape()
{
   mNetFlags.set(Ghostable|ScopeAlways);
   mTypeMask |= StaticShapeObjectType;
}

void ScopeAlwaysShape::initPersistFields()
{
   Parent::initPersistFields();
}

IMPLEMENT_CO_NETOBJECT_V1(ScopeAlwaysShape);

ConsoleDocClass( ScopeAlwaysShape,
   "@brief StaticShape object which is always scoped.\n\n"

   "@note Exists for backwards compatibility, no real use anymore. Go with TSStatic or a standard StaticShape instead.\n\n"

   "@internal\n"
);
