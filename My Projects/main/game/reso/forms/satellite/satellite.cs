// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock CameraData(FrmSatellite)
{
   mode = "Observer";
};

//-----------------------------------------------------------------------------

// callback function: called by engine
function FrmSatellite::onAdd(%this, %obj)
{
   Parent::onAdd(%this,%obj);
   
   %obj.scopeToClient(%obj.client);
 
   // Setup view & hearing
   %obj.fovDelta = 0;
   %obj.viewHud = "ResoSatelliteGui";
   %obj.viewIrisSizeX = 8;
   %obj.viewIrisSizeY = 8;
   %obj.viewIrisDtX = 0;
   %obj.viewIrisDtY = 0;
   %obj.viewMotionBlurActive = false;
   %obj.hearingDeafness = 0.0;
   %obj.hearingDeafnessDt = 0;
   %obj.hearingTinnitusEnabled = false;
}

// callback function: called by engine
function FrmSatellite::onRemove(%this, %obj)
{
   Parent::onRemove(%this, %obj);
}

