// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _POSTEFFECTVIS_H_
#define _POSTEFFECTVIS_H_

#ifndef _TSINGLETON_H_
#include "core/util/tSingleton.h"
#endif

#ifndef _POST_EFFECT_H_
#include "postFx/postEffect.h"
#endif

class GuiWindowCtrl;
class GuiBitmapCtrl;
class GuiControl;

class PostEffectVis
{
   // Protected constructor.
   // Use PFXVIS define to access singleton.
   PostEffectVis();
   friend class ManagedSingleton<PostEffectVis>;   

public:

   ~PostEffectVis();

   /// Open visualization windows for all input and target textures.
   void open( PostEffect *pfx );

   /// Close all visualization windows.
   void clear();

   /// Hide or show all visualization windows.
   void setVisible( bool visible );

   /// Callback from PostEffectManager at the start of a frame.
   void onStartOfFrame();
   
   /// Callback from PostEffect to update visualization.
   void onPFXProcessed( PostEffect *pfx );
      
   /// Callback when a visualization window is closed.
   void onWindowClosed( GuiWindowCtrl *ctrl );      

protected:

   /// Get or create the content control, the parent of all visualization windows.
   GuiControl* _getContentControl();

protected:

   enum TexIndex
   {
      Target = 0,
      Input1, 
      Input2, 
      Input3, 
      Input4,       
      TexCount
   };

   /// Structure representing a single 'opened' PostEffect
   /// including GuiControls for displaying any input/target textures.
   struct VisWindow
   {
      PostEffect *pfx;
      GuiWindowCtrl *window[TexCount];
      GuiBitmapCtrl *bmp[TexCount];
   };

   void _setDefaultCaption( VisWindow &vis, U32 texIndex );

   typedef Vector< VisWindow > VisVector;
   
   VisVector mWindows;

   GuiControl *mContent;
   
public:

   // For ManagedSingleton.
   static const char* getSingletonName() { return "PostEffectVis"; }
};

/// Returns the PostEffectVis singleton.
#define PFXVIS ManagedSingleton<PostEffectVis>::instance()

#endif // _POSTEFFECTVIS_H_