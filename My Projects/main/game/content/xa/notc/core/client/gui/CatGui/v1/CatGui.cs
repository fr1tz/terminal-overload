// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function CatGui::onWake(%this)
{
   // Turn off any shell sounds...
   // sfxStop( ... );
   
   %this.zZoomNoiseOffset = 0;

   $enableDirectInput = "1";
   activateDirectInput();
   
   Canvas.pushDialog(MiscHud);
   Canvas.pushDialog(XaNotcMinimapHud);
   Canvas.pushDialog(notcCatHud);
   Canvas.pushDialog(XaNotcMinimapHudEffectsLayer);
   
   // Message hud dialog
   if ( isObject( MainChatHud ) )
   {
      Canvas.pushDialog( MainChatHud );
      chatHud.attach(HudMessageVector);
   }      
   
   // just update the action map here
   XaNotc1MiscMoveMap_activate();
   XaNotc1CatMoveMap_activate();
   
   // Start tick thread.
   %this.tickThread();

   // hack city - these controls are floating around and need to be clamped
   if ( isFunction( "refreshCenterTextCtrl" ) )
      schedule(0, 0, "refreshCenterTextCtrl");
   if ( isFunction( "refreshBottomTextCtrl" ) )
      schedule(0, 0, "refreshBottomTextCtrl");
}

function CatGui::onSleep(%this)
{
   if(NotcBlurPostFx.isEnabled())
      NotcBlurPostFx.disable();

   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
      
   cancel(%this.zTickThread);
   
   // pop the keymaps
   //XaNotc1CatMoveMap.pop();
}

function CatGui::clearHud( %this )
{
   Canvas.popDialog( MainChatHud );

   while ( %this.getCount() > 0 )
      %this.getObject( 0 ).delete();
}

function CatGui::tickThread(%this)
{
   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(64, "tickThread");

   if(!isObject(ServerConnection))
      return;
      
   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;
      
   %data = %control.getDataBlock();

   %fov = ServerConnection.getControlCameraFov();
   %zoomRange = $Pref::NOTC1::DefaultFov-%data.cameraMinFov;
   %zoomAmount = 1 - (%fov-%data.cameraMinFov)/%zoomRange;
   
   %scale = 1.0;
   if(ServerConnection.isFirstPerson() && %zoomAmount > 0)
   {
      %blurryNess = 0.9;
      %minScale = 0.05;
      %zoomAmountScaled = (1-%minScale) * %zoomAmount * %blurryNess;
      %scale = (1-%zoomAmountScaled)*(1-%zoomAmountScaled);
      %scale += %minScale;
      %scale = mClamp(%scale, %minScale, 1);
   }
   //echo(%scale);
   if(%scale < 1)
   {
      NotcBlurPostFx.targetScale = %scale SPC %scale;
      if(!NotcBlurPostFx.isEnabled())
         NotcBlurPostFx.enable();
   }
   else
   {
      if(NotcBlurPostFx.isEnabled())
         NotcBlurPostFx.disable();
   }

   %scanlinesAlpha = mClamp(50 + 205*%zoomAmount, 50, 255);
   %scanlinesAlpha = 25;
   notcCatGuiFeedOverlayProfile.fillColor = "255 255 255" SPC %scanlinesAlpha;
   
   //echo(NotcCatGuiScanlinesProfile.fillColor);
   
   %this.zZoomNoiseOffset -= 1;
   //%this-->ZoomNoise.setValue(%this.zZoomNoiseOffset, %this.zZoomNoiseOffset);
   //echo(%this.zZoomNoiseOffset);
}

//-----------------------------------------------------------------------------
