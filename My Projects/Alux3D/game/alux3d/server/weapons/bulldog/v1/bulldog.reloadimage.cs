// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnBulldogReloadImage)
{
   // Basic Item properties
   shapeFile = "library/shape/alux3d/bulldog/image/p1/TP_Bulldog.DAE";
   shapeFileFP = "library/shape/alux3d/bulldog/image/p1/FP_Bulldog.DAE";
   emap = true;

   imageAnimPrefix = "Rifle";
   imageAnimPrefixFP = "Rifle";

   // Specify mount point & offset for 3rd person, and eye offset
   // for first person rendering.
   mountPoint = 0;
   firstPerson = true;
   useEyeNode = true;
   animateOnServer = true;

   // When firing from a point offset from the eye, muzzle correction
   // will adjust the muzzle vector to point to the eye LOS point.
   correctMuzzleVector = true;

   // Add the WeaponImage namespace as a parent, WeaponImage namespace
   // provides some hooks into the inventory system.
   class = "WeaponImage";
   className = "WeaponImage";

   useRemainderDT = false;

   // Script fields
   fireImage = WpnBulldogImage;

   // Initial start up state
   stateName[0]                     = "ReloadStart";
   stateTransitionOnTimeout[0]      = "ReloadDone";
   stateWaitForTimeout[0]           = true;
   stateTimeoutValue[0]             = 3.0;
   stateReload[0]                   = true;
   stateSequence[0]                 = "reload";
   stateShapeSequence[0]            = "Reload";
   stateScaleShapeSequence[0]       = true;
   stateSound[0]                    = WpnBulldogReloadSound;
   
   // Reload done
   stateName[1]                     = "ReloadDone";
   stateScript[1]                   = "onReloadDone";
};


