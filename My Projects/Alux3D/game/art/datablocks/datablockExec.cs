// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Load up all datablocks.  This function is called when
// a server is constructed.

// Do the sounds first -- later scripts/datablocks may need them
exec("./audioProfiles.cs");

// LightFlareData and LightAnimData(s)
exec("./lights.cs");

// Do the various effects next -- later scripts/datablocks may need them
exec("./particles.cs");
exec("./environment.cs");

exec("./triggers.cs");

// Add a rigid example
exec("./rigidShape.cs");

exec("./health.cs");

// Load our supporting weapon datablocks, effects and such.  They must be
// loaded before any weapon that uses them.
exec("./weapon.cs");
exec("./weapons/grenadefx.cs");
exec("./weapons/rocketfx.cs");

// Load the weapon datablocks
exec("./weapons/Lurker.cs");
exec("./weapons/Ryder.cs");
exec("./weapons/ProxMine.cs");
exec("./weapons/Turret.cs");

exec("./teleporter.cs");

// Load the default player datablocks
exec("./player.cs");

// Load our other player datablocks
exec("./aiPlayer.cs");

// Load the vehicle datablocks
exec("./vehicles/cheetahCar.cs");