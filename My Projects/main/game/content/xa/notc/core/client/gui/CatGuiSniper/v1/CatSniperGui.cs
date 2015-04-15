// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function notcCatSniperGui::onAdd(%this)
{
   %this-->ts.cameraXRot = 0;
   %this-->ts.cameraZRot = 0;
   %this.zElevation = 0;
   
   %this.zScanForTargets = false;
   
   %this.sounds[0] = sfxCreateSource(
      AudioGui,
      "content/xa/notc/core/sounds/test1.wav"
   );
}

function notcCatSniperGui::onWake(%this)
{
   //$HDRPostFX::colorCorrectionRamp = "content/xa/notc/core/client/gui/CatGuiSniper/graphics/color_ramp.png";

   if(!notcCatSniperGuiPostFX.isEnabled())
      notcCatSniperGuiPostFX.enable();

   // Turn off any shell sounds...
   // sfxStop( ... );

   //%this.setElevation(%this.zElevation);
   //%this.updateView();
   if($cameraFov > 45)
      $cameraFov = 45;
   setFov($cameraFov);
   %this.schedule(0, "updateView");

   %this.zZoomNoiseOffset = 0;

   $enableDirectInput = "1";
   activateDirectInput();

   Canvas.pushDialog(notcCatHud);
   Canvas.pushDialog(notcCatSniperGuiOverlay);
   Canvas.pushDialog(MiscHud);
   Canvas.pushDialog(XaNotcMinimapHud);
   Canvas.pushDialog(XaNotcMinimapHudEffectsLayer);

   sfxPlayOnce(AudioGui, "content/xa/notc/core/sounds/charge1.wav");

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
   
   %colorI = ServerConnection.getControlObject().paletteColors[0];
   //notcCatSniperGuiDefaultProfile.fontColor = %colorI;
   //notcCatSniperGuiDefaultProfile.fillColor = %colorI;

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
      
   sfxPlayOnce(AudioGui, "content/xa/notc/core/sounds/charge1rev.wav");
      
   //MoveManager_addPitch(%this-->ts.cameraXRot*(mPi()/180));
   //setFov(mClamp($cameraFov*2,1,$Pref::NOTC1::DefaultFov));
   setFov($Pref::NOTC1::DefaultFov);
   $MouseZoomStep = 0;
      
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
   %this.zTickThread = %this.schedule(32, "tickThread");

   if(!isObject(ServerConnection))
      return;
      
   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;
      
   %data = %control.getDataBlock();
   
   if(%this.zScanForTargets)
      %this.scanForTarget();
   
   %this.renderTargeting();

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

function notcCatSniperGui::updateView(%this)
{
   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;

   %fov = $cameraFov;
   %maxElevDeg = %fov/2;
   %elevDeg = %maxElevDeg * %this.zElevation;
   %this-->ts.cameraXRot = %elevDeg;
   
   %this.updateCrosshair();
}

function notcCatSniperGui::setElevation(%this, %elevation)
{
   //echo("notcCatSniperGui::setElevation():" SPC %elevation);

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
   %this.updateCrosshair();
}

function notcCatSniperGui::updateCrosshair(%this)
{
   %width = getWord(%this-->ts.getExtent(), 0);
   %height = getWord(%this-->ts.getExtent(), 1);
   %crosshairX = 0.5 * %width;
   %crosshairY = 0.5 * %height - %height*%this.zElevation*0.5;
   //echo(%crosshairX SPC %crosshairY);
   
   %size = %this-->ts.getWorldToScreenScale();

   %w = mFloatLength(%size,0);
   %h = mFloatLength(%size,0);
   %this-->crosshairScaled.setExtent(%w SPC %h);
   %this-->crosshairScaled.setPosition(%crosshairX-%w/2, %crosshairY-%h/2);

   %w = 100;
   %h = 100;
   %this-->crosshairStatic.setExtent(%w SPC %h);
   %this-->crosshairStatic.setPosition(%crosshairX-%w/2, %crosshairY-%h/2);
   
   %this-->crosshair-->vline1.setPosition(%crosshairX, 0);
   %this-->crosshair-->vline1.setExtent("1" SPC %crosshairY-5);
   %this-->crosshair-->vline2.setPosition(%crosshairX, %crosshairY+5);
   %this-->crosshair-->vline2.setExtent("1" SPC %height);
   %this-->crosshair-->hline1.setPosition(0, %crosshairY);
   %this-->crosshair-->hline1.setExtent(%crosshairX-5 SPC "1");
   %this-->crosshair-->hline2.setPosition(%crosshairX+5, %crosshairY);
   %this-->crosshair-->hline2.setExtent(%width SPC "1");
}

function notcCatSniperGui::scanForTarget(%this)
{
   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;

   %mask = $TypeMasks::ShapeBaseObjectType;
   %fvec = %control.getEyeVector();
   %start = %control.getEyePoint();
   %end = VectorAdd(%start, VectorScale(%fvec, 99999));
   %result = containerRayCast( %start, %end, %mask, %control, true );

   %target = getWord(%result, 0);
   if(!isObject(%target))
   {
      %this.zTarget = "";
      return;
   }
      
   %this.zTarget = %target;
   %this.zScanForTargets = false;

   //echo(%this.zTarget);
   %this.sounds[0].play();
}

function notcCatSniperGui::renderTargeting(%this)
{
   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;
      
   %this-->target.setVisible(false);
   %this-->crosshairScaled.setVisible(false);

   if(isObject(%this.zTarget) && %this.zTarget.getDamageState() $= "Enabled")
   {
      %pos3D = %this.zTarget.getWorldBoxCenter();
      %pos = %this-->ts.project(%pos3D);
      //echo(%pos3D SPC "->" SPC %pos);
      
      %targetX = getWord(%pos, 0);
      %targetY = getWord(%pos, 1);
      %depth   = getWord(%pos, 2);
      
      %targetDist = VectorLen(VectorSub(%pos3D, %control.getEyePoint()));
      %this-->projectilesHud.targetPos = %pos3D;
      
      %width = getWord(%this-->ts.getExtent(), 0);
      %height = getWord(%this-->ts.getExtent(), 1);
      
      %this-->target-->VLine.setPosition(%targetX, 0);
      %this-->target-->VLine.setExtent("1" SPC %height);
      %this-->target-->HLine.setPosition(0, %targetY);
      %this-->target-->HLine.setExtent(%width SPC "1");
      
      //%wb = %this.zTarget.getWorldBox();
      //%p1 = %this-->ts.project(getWords(%wb, 0, 2));
      //%p2 = %this-->ts.project(getWords(%wb, 3, 5));
      //%size = VectorLen(VectorSub(%p2,%p1));
      %size = %targetDist; 
      %size = %size * %this-->ts.getWorldToScreenScale() / 1000;
      %size = mFloatLength(%size/5, 0);
      
      %this-->target-->VBlock.setPosition(%targetX-%size/2, 0);
      %this-->target-->VBlock.setExtent(%size SPC %height);
      %this-->target-->HBlock.setPosition(0, %targetY-%size/2);
      %this-->target-->HBlock.setExtent(%width SPC %size);
      
      %w = %targetDist * getWord(%this-->ts.getWorldToScreenScale(), 0) / 1000;
      %h = %targetDist * getWord(%this-->ts.getWorldToScreenScale(), 1) / 1000;
      %this-->target-->distOverlay.setExtent(mFloatLength(%w,0) SPC mFloatLength(%h,0));
      %this-->target-->distOverlay.setPosition(%targetX-%w/2, %targetY-%h/2);
      
      %this-->target.setVisible(true);
      %this-->target-->HBlock.setVisible(false);
      %this-->target-->VBlock.setVisible(false);
      %this-->target-->VLine.setVisible(%depth < 1);
      %this-->target-->distOverlay.setVisible(%depth < 1);
      //%this-->crosshairScaled.setVisible(true);
   }
   else
   {
      %this.zTarget = "";
      %this-->projectilesHud.targetPos = "0 0 0";
   }
}
