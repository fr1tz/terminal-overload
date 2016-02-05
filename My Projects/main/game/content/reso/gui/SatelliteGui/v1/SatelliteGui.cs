// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function ResoSatelliteGui::onAdd(%this)
{
   %this.setDisplayType($EditTsCtrl::DisplayTypeTop);	
}

function ResoSatelliteGui::onWake(%this)
{
   // Turn off any shell sounds...
   // sfxStop( ... );

   $enableDirectInput = "1";
   activateDirectInput();
     
   // Message hud dialog
   if ( isObject( MainChatHud ) )
   {
      Canvas.pushDialog( MainChatHud );
      chatHud.attach(HudMessageVector);
   }      
   
   // just update the action map here
   XaNotc1MiscMoveMap_activate();
   XaNotc1CatMoveMap_activate();
   
   // Start tick thread.
   %this.tickThread();

   // hack city - these controls are floating around and need to be clamped
   if ( isFunction( "refreshCenterTextCtrl" ) )
      schedule(0, 0, "refreshCenterTextCtrl");
   if ( isFunction( "refreshBottomTextCtrl" ) )
      schedule(0, 0, "refreshBottomTextCtrl");
}

function ResoSatelliteGui::onSleep(%this)
{
   if(NotcBlurPostFx.isEnabled())
      NotcBlurPostFx.disable();

   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
      
   cancel(%this.zTickThread);
   
   // pop the keymaps
   //XaNotc1CatMoveMap.pop();
}

function ResoSatelliteGui::clearHud( %this )
{
   Canvas.popDialog( MainChatHud );

   while ( %this.getCount() > 0 )
      %this.getObject( 0 ).delete();
}

function ResoSatelliteGui::tickThread(%this)
{
   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(64, "tickThread");

   if(!isObject(ServerConnection))
      return;
      
   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;

}

