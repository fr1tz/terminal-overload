// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


//---------------------------------------------------------------------------------------------

function initLightingSystems()
{
   echo( "\n--------- Initializing Lighting Systems ---------" );

   // First exec the scripts for the different light managers
   // in the lighting folder.
   
   %pattern = "./lighting/*/init.cs";   
   %file = findFirstFile( %pattern );
   if ( %file $= "" )
   {
      // Try for DSOs next.
      %pattern = "./lighting/*/init.cs.dso";
      %file = findFirstFile( %pattern );
   }
   
   while( %file !$= "" )
   {      
      exec( %file );
      %file = findNextFile( %pattern );
   }
   
   // Try the perfered one first.
   %success = setLightManager( $pref::lightManager );
   if ( !%success )
   {
      // The perfered one fell thru... so go thru the default
      // light managers until we find one that works.
      %lmCount = getFieldCount( $lightManager::defaults );
      for ( %i = 0; %i < %lmCount; %i++ )
      {         
         %lmName = getField( $lightManager::defaults, %i );
         %success = setLightManager( %lmName );
         if ( %success )
            break;
      }
   }
   
   // Did we completely fail to initialize a light manager?   
   if ( !%success )
   {
      // If we completely failed to initialize a light 
      // manager then the 3d scene cannot be rendered.
      quitWithErrorMessage( "Failed to set a light manager!" );
   }
      
   echo( "\n" );
}

//---------------------------------------------------------------------------------------------

function onLightManagerActivate( %lmName )
{
   $pref::lightManager = %lmName;
   echo( "Using " @ $pref::lightManager );
   
   // Call activation callbacks.
   
   %activateNewFn = "onActivate" @ getWord( %lmName, 0 ) @ "LM";   
   if( isFunction( %activateNewFn ) )
      eval( %activateNewFn @ "();" );
}

//---------------------------------------------------------------------------------------------

function onLightManagerDeactivate( %lmName )
{
   // Call deactivation callback.
   
   %deactivateOldFn = "onDeactivate" @ getWord( %lmName, 0 ) @ "LM";
   if( isFunction( %deactivateOldFn ) )
      eval( %deactivateOldFn @ "();" );
}
