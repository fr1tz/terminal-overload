// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function EditorLightingMenu::onAdd( %this )
{
   Parent::onAdd( %this );
   
   // Get the light manager names.
   %lightManagers = getLightManagerNames();

   // Where we gonna insert them?
   %this.lmFirstIndex = %this.getItemCount();
   
   // Add the light mangers to the lighting menu.
   %count = getFieldCount( %lightManagers );
   for ( %i = 0; %i < %count; %i++ )
   {      
      %lm = getField( %lightManagers, %i );

      // Store a reverse lookup of the light manager
      // name to the menu index... used in onMenuSelect.
      %index = %this.lmFirstIndex + %i;
      %this.lmToIndex[ %lm ] = %index;      
            
      // The command just sets the light manager.
      %cmd = "setLightManager(\"" @ %lm @ "\"); $pref::lightManager = \"" @ %lm @ "\";";
      
      // Add it.
      %this.addItem( %index, %lm TAB "" TAB %cmd );
   }
   
   // Store for later in EditorLightingMenu.
   %this.lmLastIndex = %index;
}

function EditorLightingMenu::onMenuSelect( %this )
{
   %lm = getActiveLightManager();
   %index = %this.lmToIndex[ %lm ];
   %this.checkRadioItem( %this.lmFirstIndex, %this.lmLastIndex, %index );
   
   //%selSize = EWorldEditor.getSelectionSize();
   %this.enableItem( 1, true /*%selSize == 1*/ );   
}
