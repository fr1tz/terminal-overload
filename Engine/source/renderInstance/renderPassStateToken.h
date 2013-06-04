// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RENDERPASSSTATETOKEN_H_
#define _RENDERPASSSTATETOKEN_H_

#ifndef _RENDERBINMANAGER_H_
#include "renderInstance/renderBinManager.h"
#endif

class RenderPassStateBin;


class RenderPassStateToken : public SimObject
{
   typedef SimObject Parent;

public:
   DECLARE_CONOBJECT(RenderPassStateToken);

   static void initPersistFields();

   // These must be re-implemented, and will assert if called on the base class.
   // They just can't be pure-virtual, due to SimObject.
   virtual void process(SceneRenderState *state, RenderPassStateBin *callingBin);
   virtual void reset();
   virtual void enable(bool enabled = true);
   virtual bool isEnabled() const;
};

//------------------------------------------------------------------------------

class RenderPassStateBin : public RenderBinManager
{
   typedef RenderBinManager Parent;

protected:
   SimObjectPtr< RenderPassStateToken > mStateToken;
   
   static bool _setStateToken( void* object, const char* index, const char* data )
   {
      RenderPassStateToken* stateToken;
      Sim::findObject( data, stateToken );
      reinterpret_cast< RenderPassStateBin* >( object )->mStateToken = stateToken;
      return false;
   }
   static const char* _getStateToken( void* object, const char* data )
   {
      RenderPassStateBin* bin = reinterpret_cast< RenderPassStateBin* >( object );
      if( bin->mStateToken.isValid() )
         return bin->mStateToken->getIdString();
      else
         return "0";
   }
   
public:
   DECLARE_CONOBJECT(RenderPassStateBin);
   static void initPersistFields();

   RenderPassStateBin();
   virtual ~RenderPassStateBin();

   void render(SceneRenderState *state);
   void clear();
   void sort();
};

#endif // _RENDERPASSSTATETOKEN_H_
