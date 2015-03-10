// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function XaNotc1CatMoveMap_switchFeed(%val)
{
   if(!%val)
      return;
      
   if(!ServerConnection.isFirstPerson())
      return;
      
   if(Canvas.getContent() == CatGui.getId())
      $PlayGui = notcCatSniperGui;
   else
      $PlayGui = CatGui;
      
   Canvas.setContent($PlayGui);
}

function XaNotc1CatMoveMap_mouseZoom(%val)
{
	if(Canvas.isCursorOn())
		return;

   if(!ServerConnection.isFirstPerson())
      return;
  
   if($MouseZoomSteps $= "")
      $MouseZoomSteps = $Pref::NOTC1::MouseZoomSteps;
      
	%minFov = ServerConnection.getControlObject().getDataBlock().cameraMinFov;
   %maxFov = $Pref::NOTC1::DefaultFov;

   %mouseZoomStepStor = $MouseZoomStep;
	if(%val > 0)
      $MouseZoomStep++;
	else
		$MouseZoomStep--;
   $MouseZoomStep = mClamp($MouseZoomStep, 0, $MouseZoomSteps);
   if($MouseZoomStep == %mouseZoomStepStor)
      return;
   
   %pos = (1/($MouseZoomSteps)) * $MouseZoomStep;
   //echo(%pos);
   %f = mPow(1-%pos, 2);
   $MouseZoomValue = %minFov + (%maxFov-%minFov)*%f;
   setFov($MouseZoomValue);
   sfxPlayOnce(AudioGui, "content/o/rotc/p.5.4/sounds/rotc/weaponSwitch.wav");
}

function XaNotc1CatMoveMap_toggleFirstPerson(%val)
{
   if(!%val)
      return;

   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;

   %datablock = %control.getDataBlock();
   if(%datablock.firstPersonOnly || %datablock.thirdPersonOnly)
      return;
      
   %fp = !ServerConnection.isFirstPerson();

   ServerConnection.setFirstPerson(%fp);

   if(%fp)
      $PlayGui = notcUserGui.zPlayGui;
   else
   {
      notcUserGui.zPlayGui = $PlayGui;
      $PlayGui = notcUserGui;
   }
      
   Canvas.setContent($PlayGui);
}

