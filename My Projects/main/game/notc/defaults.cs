// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// First we execute the core default preferences.
exec( "core/scripts/server/defaults.cs" );

// Now add your own game specific server preferences as
// well as any overloaded core defaults here.


// Finally load the preferences saved from the last
// game execution if they exist.
if ( $platform !$= "xenon" )
{
   if ( isFile( $SettingsDir@"/tol.srv.prefs.cs" ) )
      exec( $SettingsDir@"/tol.srv.prefs.cs" );
}
else
{
   echo( "Not loading server prefs.cs on Xbox360" );
}
