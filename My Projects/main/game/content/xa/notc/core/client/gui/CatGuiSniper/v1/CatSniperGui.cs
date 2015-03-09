// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function notcCatSniperGui::onAdd(%this)
{
   %this-->ts.cameraXRot = 0;
   %this-->ts.cameraZRot = 0;
   %this.zElevation = 0.5;
}

function notcCatSniperGui::onWake(%this)
{
   //$HDRPostFX::colorCorrectionRamp = "content/xa/notc/core/client/gui/CatGuiSniper/graphics/color_ramp.png";

   if(!notcCatSniperGuiPostFX.isEnabled())
      notcCatSniperGuiPostFX.enable();

   // Turn off any shell sounds...
   // sfxStop( ... );
   
   %this-->ts.cameraXRot = 0;
   %this-->ts.cameraZRot = 0;
   //%this.setElevation(%this.zElevation);
   %this.setElevation(0);

   //setFov($cameraFov*0.5);
   
   %this.zZoomNoiseOffset = 0;

   $enableDirectInput = "1";
   activateDirectInput();
   
   Canvas.pushDialog(MiscHud);
   //Canvas.pushDialog(XaNotcMinimapHud);
   //Canvas.pushDialog(notcCatHud);
   //Canvas.pushDialog(XaNotcMinimapHudEffectsLayer);

   // Message hud dialog
   if ( isObject( MainChatHud ) )
   {
      Canvas.pushDialog( MainChatHud );
      chatHud.attach(HudMessageVector);
   }      
   
   // just update the action map here
   XaNotc1MiscMoveMap_activate();
   XaNotc1CatSniperMoveMap_activate();
   
   // Start tick thread.
   %this.tickThread();
   
   %colorI = ServerConnection.getControlObject().paletteColors[0];
   notcCatSniperGuiDefaultProfile.fontColor = %colorI;
   notcCatSniperGuiDefaultProfile.fillColor = %colorI;

   // hack city - these controls are floating around and need to be clamped
   if ( isFunction( "refreshCenterTextCtrl" ) )
      schedule(0, 0, "refreshCenterTextCtrl");
   if ( isFunction( "refreshBottomTextCtrl" ) )
      schedule(0, 0, "refreshBottomTextCtrl");
}

function notcCatSniperGui::onSleep(%this)
{
   $HDRPostFX::colorCorrectionRamp = "core/scripts/client/postFx/null_color_ramp.png";

   if(notcCatSniperGuiPostFX.isEnabled())
      notcCatSniperGuiPostFX.disable();
      
   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
      
   //setFov(mClamp($cameraFov*2,1,$Pref::NOTC1::DefaultFov));
      
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

function notcCatSniperGui::setElevation(%this, %elevation)
{
   //echo("notcCatSniperGui::setElevation():" SPC %elevation);
   
   if(!isObject(ServerConnection))
      return;

   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;
   
   %newElevation = mClamp(%elevation, -1, 1);
   
   %fov = $cameraFov;
   %maxElevDeg = %fov/2;
   %elevDeg = %maxElevDeg * %elevation;
   %elevDegDt = %elevDeg - %this-->ts.cameraXRot;

   %pitchAdd = 0;
   if(%elevDegDt != 0)
      %pitchAdd = -%elevDegDt*(mPi()/180);
   MoveManager_addPitch(%pitchAdd);
   
   %this-->ts.cameraXRot = %elevDeg;

   %this.zElevation = %newElevation;
   //echo(%this.zElevation);

   // Update GUI
   %width = getWord(%this-->ts.getExtent(), 0);
   %height = getWord(%this-->ts.getExtent(), 1);
   %crosshairX = 0.5 * %width;
   %crosshairY = 0.5 * %height - %height*%this.zElevation*0.5;
   //echo(%crosshairX SPC %crosshairY);
   
   %this-->zeroElev.setPosition(0, 0.5*%height);
   %this-->zeroElev.setExtent(%width SPC "1");
   
   %this-->crosshair.setPosition(%crosshairX-60, %crosshairY-60);

   %this-->targetX.setVisible(false);
   %this-->targetY.setVisible(false);
}
