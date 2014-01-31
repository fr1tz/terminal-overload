// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function SoldierHud::onWake(%this)
{
   // Turn off any shell sounds...
   // sfxStop( ... );

   $enableDirectInput = "1";
   activateDirectInput();

   // Message hud dialog
   if ( isObject( MainChatHud ) )
   {
      Canvas.pushDialog( OverlayHud );
      Canvas.pushDialog( MainChatHud );
      chatHud.attach(HudMessageVector);
   }      
   
   // just update the action map here
   moveMap.push();
   
   // Start tick thread.
   %this.tickThread();

   // hack city - these controls are floating around and need to be clamped
   if ( isFunction( "refreshCenterTextCtrl" ) )
      schedule(0, 0, "refreshCenterTextCtrl");
   if ( isFunction( "refreshBottomTextCtrl" ) )
      schedule(0, 0, "refreshBottomTextCtrl");
}

function SoldierHud::onSleep(%this)
{
   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
   
   // pop the keymaps
   moveMap.pop();
}

function SoldierHud::clearHud( %this )
{
   Canvas.popDialog( MainChatHud );

   while ( %this.getCount() > 0 )
      %this.getObject( 0 ).delete();
}

function SoldierHud::tickThread(%this)
{
   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(32, "tickThread");
   
   %magazine = SoldierHudAmmoAmount.zMagazine;
   if(%magazine $= "")
      %magazine = ServerConnection.getControlObject().getImageMagazineRounds(0);
      
   %spare = SoldierHudAmmoAmount.zSpare;
   
   SoldierHudAmmoAmount.setText("Ammo: " @ %magazine @ "/" @ %spare);
}

//-----------------------------------------------------------------------------
