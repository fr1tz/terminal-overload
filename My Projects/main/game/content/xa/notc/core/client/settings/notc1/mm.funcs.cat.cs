// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function XaNotc1CatMoveMap_switchFeed(%val)
{
   if(!%val)
      return;
      
   if(Canvas.getContent() == CatGui.getId())
      Canvas.setContent(notcCatSniperGui);
   else
      Canvas.setContent(CatGui);
}

function XaNotc1CatMoveMap_mouseZoom(%val)
{
	if(Canvas.isCursorOn())
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
   %f = (1-%pos)*(1-%pos);
   $MouseZoomValue = %minFov + (%maxFov-%minFov)*%f;
   setFov($MouseZoomValue);
}
