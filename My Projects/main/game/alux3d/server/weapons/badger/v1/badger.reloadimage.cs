// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ShapeBaseImageData(WpnBadgerReloadImage)
{
   // Basic Item properties
   shapeFile = "content/fr1tz/oldshapes/badger/image/p1/TP_Badger.DAE";
   shapeFileFP = "content/fr1tz/oldshapes/badger/image/p1/FP_Badger.DAE";
   emap = true;

   imageAnimPrefix = "Pistol";
   imageAnimPrefixFP = "Pistol";

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
   fireImage = WpnBadgerImage;

   // Initial start up state
   stateName[0]                     = "ReloadStart";
   stateTransitionOnTimeout[0]      = "ReloadDone";
   stateWaitForTimeout[0]           = true;
   stateTimeoutValue[0]             = 2.0;
   stateReload[0]                   = true;
   stateSequence[0]                 = "reload";
   stateShapeSequence[0]            = "Reload";
   stateScaleShapeSequence[0]       = true;
   stateSound[0]                    = WpnBadgerReloadSound;
   
   // Reload done
   stateName[1]                     = "ReloadDone";
   stateScript[1]                   = "onReloadDone";
};


