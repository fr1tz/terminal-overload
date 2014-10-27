// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// First we execute the core default preferences.
exec( "core/scripts/client/defaults.cs" );


// Now add your own game specific client preferences as
// well as any overloaded core defaults here.
$PhysXLogWarnings = false;



// Finally load the preferences saved from the last
// game execution if they exist.
if ( $platform !$= "xenon" )
{
   if (isFile($SettingsDir@"/prefs.cs"))
      exec($SettingsDir@"/prefs.cs");
}
else
{
   echo( "Not loading client prefs.cs on Xbox360" );
}
