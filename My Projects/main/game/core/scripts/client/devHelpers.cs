// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// Shortcut for typing dbgSetParameters with the default values torsion uses.
function dbgTorsion()
{
   dbgSetParameters( 6060, "password", false );
}

/// Reset the input state to a default of all-keys-up.
/// A helpful remedy for when Torque misses a button up event do to your breakpoints
/// and can't stop shooting / jumping / strafing.
function mvReset()
{
   for ( %i = 0; %i < 6; %i++ )
      setVariable( "mvTriggerCount" @ %i, 0 );
      
   $mvUpAction = 0;
   $mvDownAction = 0;
   $mvLeftAction = 0;
   $mvRightAction = 0;
   
   // There are others.
}