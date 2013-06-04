// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _LEVELINFO_H_
#define _LEVELINFO_H_

#ifndef _NETOBJECT_H_
   #include "sim/netObject.h"
#endif
#ifndef _COLOR_H_
   #include "core/color.h"
#endif
#ifndef _FOGSTRUCTS_H_
   #include "scene/fogStructs.h"
#endif
#ifndef _SFXCOMMON_H_
   #include "sfx/sfxCommon.h"
#endif


class SFXAmbience;
class SFXSoundscape;


class LevelInfo : public NetObject
{
      typedef NetObject Parent;
      
   private:

      F32 mWorldSize;

      FogData mFogData;
      
      F32 mNearClip;

      F32 mVisibleDistance;

      F32 mDecalBias;

      ColorI mCanvasClearColor;

      /// @name Lighting Properties
      /// @{

      bool mAdvancedLightmapSupport;

      /// Seconds it takes to go from one global ambient color
      /// to a different one.
      F32 mAmbientLightBlendPhase;

      /// Interpolation for going from one global ambient color
      /// to a different one.
      EaseF mAmbientLightBlendCurve;

      /// @}
      
      /// @name Sound Properties
      /// @{
      
      /// Global ambient sound space properties.
      SFXAmbience* mSoundAmbience;
      
      /// Distance attenuation model to use.
      SFXDistanceModel mSoundDistanceModel;
      
      ///
      SFXSoundscape* mSoundscape;
         
      /// @}
      
      /// Responsible for passing on
      /// the LevelInfo settings to the
      /// client SceneGraph, from which
      /// other systems can get at them.
      void _updateSceneGraph();

      void _onLMActivate(const char *lm, bool enable);

   public:

      LevelInfo();
      virtual ~LevelInfo();

      DECLARE_CONOBJECT(LevelInfo);

      /// @name SceneObject Inheritance
      /// @{
      
      virtual SFXAmbience* getSoundAmbience() const { return mSoundAmbience; }

      /// @}
      
      /// @name SimObject Inheritance
      /// @{

      virtual bool onAdd();
      virtual void onRemove();
      virtual void inspectPostApply();

      static void initPersistFields();

      /// @}

      /// @name NetObject Inheritance
      /// @{
      
      enum NetMaskBits 
      {
         UpdateMask = BIT(0)
      };

      virtual U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
      virtual void unpackUpdate( NetConnection *conn, BitStream *stream );

      /// @}
};

#endif // _LEVELINFO_H_