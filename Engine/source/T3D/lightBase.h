// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _LIGHTBASE_H_
#define _LIGHTBASE_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _LIGHTINFO_H_
#include "lighting/lightInfo.h"
#endif
#ifndef _ITICKABLE_H_
#include "core/iTickable.h"
#endif
#ifndef _LIGHTFLAREDATA_H_
#include "T3D/lightFlareData.h"
#endif
#ifndef _LIGHTANIMDATA_H_
#include "T3D/lightAnimData.h"
#endif

class LightAnimData;

class LightBase : public SceneObject, public ISceneLight, public virtual ITickable
{
   typedef SceneObject Parent;
   friend class LightAnimData;
   friend class LightFlareData;

protected:

   bool mIsEnabled;

   ColorF mColor;

   F32 mBrightness;

   bool mCastShadows;

   F32 mPriority;

   LightInfo *mLight;

   LightAnimData *mAnimationData; 
   LightAnimState mAnimState;

   LightFlareData *mFlareData;
   LightFlareState mFlareState;   
   F32 mFlareScale;

   static bool smRenderViz;

   virtual void _conformLights() {}

   void _onRenderViz(   ObjectRenderInst *ri, 
                        SceneRenderState *state, 
                        BaseMatInstance *overrideMat );

   virtual void _renderViz( SceneRenderState *state ) {}

   enum LightMasks
   {
      InitialUpdateMask = Parent::NextFreeMask,
      EnabledMask       = Parent::NextFreeMask << 1,
      TransformMask     = Parent::NextFreeMask << 2,
      UpdateMask        = Parent::NextFreeMask << 3,
      DatablockMask     = Parent::NextFreeMask << 4,      
      NextFreeMask      = Parent::NextFreeMask << 5
   };

   // SimObject.
   virtual void _onSelected();
   virtual void _onUnselected();

public:

   LightBase();
   virtual ~LightBase();

   // SimObject
   virtual bool onAdd();
   virtual void onRemove();

   // ConsoleObject
   void inspectPostApply();
   static void initPersistFields();
   DECLARE_CONOBJECT(LightBase);

   // NetObject
   U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   void unpackUpdate( NetConnection *conn, BitStream *stream );  

   // ISceneLight
   virtual void submitLights( LightManager *lm, bool staticLighting );
   virtual LightInfo* getLight() { return mLight; }

   // SceneObject
   virtual void setTransform( const MatrixF &mat );
   virtual void prepRenderImage( SceneRenderState *state );

   // ITickable
   virtual void interpolateTick( F32 delta );
   virtual void processTick();
   virtual void advanceTime( F32 timeDelta );

   /// Toggles the light on and off.
   void setLightEnabled( bool enabled );
   bool getLightEnabled() { return mIsEnabled; };

   /// Animate the light.
   virtual void pauseAnimation( void );
   virtual void playAnimation( void );
   virtual void playAnimation( LightAnimData *animData );
};

#endif // _LIGHTBASE_H_
