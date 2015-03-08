// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function notcCatSniperGui::onWake(%this)
{
   if(!notcCatSniperGuiPostFX.isEnabled())
      notcCatSniperGuiPostFX.enable();

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

function notcCatSniperGui::onSleep(%this)
{
   if(notcCatSniperGuiPostFX.isEnabled())
      notcCatSniperGuiPostFX.disable();
      
   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
      
   cancel(%this.zTickThread);
   
   // pop the keymaps
   //XaNotc1CatMoveMap.pop();
}

function notcCatSniperGui::clearHud( %this )
{
   Canvas.popDialog( MainChatHud );

   while ( %this.getCount() > 0 )
      %this.getObject( 0 ).delete();
}

function notcCatSniperGui::tickThread(%this)
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

   //echo($MouseZoomValue);
   
   %zoomRange = $Pref::NOTC1::DefaultFov-%data.cameraMinFov;
   %zoomAmount = 1 - ($MouseZoomValue-%data.cameraMinFov)/%zoomRange;
   
   //notcCatSniperGuiZoom.setVisible($MouseZoomValue != $Pref::NOTC1::DefaultFov);
   %irisSize = (1-%zoomAmount) * 20;
   //notcCatSniperGui-->iris.sizeX = %irisSize;
   //notcCatSniperGui-->iris.sizeY = %irisSize;
   //notcCatSniperGui-->iris.setVisible(false);
   
   %scanlinesAlpha = mClamp(50 + 205*%zoomAmount, 50, 255);
   %scanlinesAlpha = 100;
   notcCatSniperGuiFeedOverlayProfile.fillColor = "255 255 255" SPC %scanlinesAlpha;
   
   //echo(NotcnotcCatSniperGuiScanlinesProfile.fillColor);
   
   %this.zZoomNoiseOffset -= 1;
   //%this-->ZoomNoise.setValue(%this.zZoomNoiseOffset, %this.zZoomNoiseOffset);
   //echo(%this.zZoomNoiseOffset);
}

//-----------------------------------------------------------------------------
