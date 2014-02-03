// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _POSTEFFECTCOMMON_H_
#define _POSTEFFECTCOMMON_H_

#ifndef _DYNAMIC_CONSOLETYPES_H_
   #include "console/dynamicTypes.h"
#endif


/// 
enum PFXRenderTime
{
   /// Before a RenderInstManager bin.
   PFXBeforeBin,

   /// After a RenderInstManager bin.
   PFXAfterBin,

   /// After the diffuse rendering pass.
   PFXAfterDiffuse,

   /// When the end of the frame is reached.
   PFXEndOfFrame,

   /// This PostEffect is not processed by the manager.
   /// It will generate its texture when it is requested.
   PFXTexGenOnDemand
};

DefineEnumType( PFXRenderTime );


/// PFXTargetClear specifies whether and how
/// often a given PostEffect's target will be cleared.
enum PFXTargetClear
{
   /// Never clear the PostEffect target.
   PFXTargetClear_None,

   /// Clear once on create.
   PFXTargetClear_OnCreate,

   /// Clear before every draw.
   PFXTargetClear_OnDraw,
};

DefineEnumType( PFXTargetClear );


/// PFXTargetViewport specifies how the viewport should be
/// set up for a PostEffect's target.
enum PFXTargetViewport
{
   /// The default viewport set up to match the target size
   PFXTargetViewport_TargetSize,

   /// Use the current GFX viewport
   PFXTargetViewport_GFXViewport,

   /// Use the input texture 0 if it is named, otherwise
   /// revert to PFXTargetViewport_TargetSize if there is none
   PFXTargetViewport_NamedInTexture0,
};

DefineEnumType( PFXTargetViewport );

///
struct PFXFrameState
{
   MatrixF worldToCamera;
   MatrixF cameraToScreen;

   PFXFrameState() 
      :  worldToCamera( true ),
         cameraToScreen( true )
   {
   }
};

///
GFX_DeclareTextureProfile( PostFxTextureProfile );

///
GFXDeclareVertexFormat( PFXVertex )
{
   /// xyz position.
   Point3F point;

   /// The screen space texture coord.
   Point2F texCoord;

   /// 
   Point3F wsEyeRay;
};

#endif // _POSTEFFECTCOMMON_H_