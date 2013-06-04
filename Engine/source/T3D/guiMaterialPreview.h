// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Original header:
// GuiMaterialPreview Control for Material Editor Written by Travis Vroman of Gaslight Studios
// Updated 2-14-09
// Portions based off Constructor viewport code.

#ifndef _GUIMATERIALPREVIEW_H_
#define _GUIMATERIALPREVIEW_H_

#include "gui/3d/guiTSControl.h"
#include "ts/tsShapeInstance.h"

class LightInfo;

class GuiMaterialPreview : public GuiTSCtrl
{
private:
   typedef GuiTSCtrl Parent;

protected:
   enum MouseState
   {
      None,
      Rotating,
      Zooming,
	  Panning,
	  MovingLight
   };

   MouseState  mMouseState;

   TSShapeInstance*  mModel;
   TSShapeInstance*  mMountedModel;
   U32   mSkinTag;

   // For Camera Panning.
   F32 mTransStep;	//*** Amount of translation with each mouse move
   F32 mTranMult;	//*** With a modifier, how much faster to translate 

   // For light translation.
   F32 mLightTransStep;
   F32 mLightTranMult;

   Point3F     mCameraPos;
   MatrixF     mCameraMatrix;
   EulerF      mCameraRot;
   Point3F     mOrbitPos;
   Point3F	   mOrbitRelPos;
   Point3F     mCameraTransform;

   TSThread *  runThread;
   S32         lastRenderTime;

   Point2I     mLastMousePoint;

   LightInfo*  mFakeSun;

public:
   bool onWake();

   void onMouseEnter(const GuiEvent &event);
   void onMouseLeave(const GuiEvent &event);
   void onMouseDown(const GuiEvent &event);
   void onMouseUp(const GuiEvent &event);
   void onMouseDragged(const GuiEvent &event);
   void onRightMouseDown(const GuiEvent &event);
   void onRightMouseUp(const GuiEvent &event);
   void onRightMouseDragged(const GuiEvent &event);
   bool onMouseWheelUp(const GuiEvent &event);
   bool onMouseWheelDown(const GuiEvent &event);
   void onMiddleMouseUp(const GuiEvent &event);
   void onMiddleMouseDown(const GuiEvent &event);
   void onMiddleMouseDragged(const GuiEvent &event);
   
   // For Camera Panning.
   void setTranslate(S32 modifier, F32 xstep, F32 ystep);
   
   // For Light Translation.
   void setLightTranslate(S32 modifier, F32 xstep, F32 ystep);
   
   // For changing the light color.
   void setLightColor( F32 r, F32 g, F32 b );
   
   // For changing the ambient light color.
   void setAmbientLightColor( F32 r, F32 g, F32 b );

   void setObjectModel(const char * modelName);
   void deleteModel();
   void resetViewport();
   void setOrbitDistance(F32 distance);

   bool processCameraQuery(CameraQuery *query);
   void renderWorld(const RectI &updateRect);

   DECLARE_CONOBJECT(GuiMaterialPreview);
   DECLARE_CATEGORY( "Gui Editor" );

   GuiMaterialPreview();
   ~GuiMaterialPreview();

private:
   F32         mMaxOrbitDist;
   F32         mMinOrbitDist;
   F32         mOrbitDist;

};

#endif
