// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// PlayGui is the main TSControl through which the game is viewed.
// The PlayGui also contains the hud controls.
//-----------------------------------------------------------------------------

function PlayGui::onWake(%this)
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
   moveMap.push();

   // hack city - these controls are floating around and need to be clamped
   if ( isFunction( "refreshCenterTextCtrl" ) )
      schedule(0, 0, "refreshCenterTextCtrl");
   if ( isFunction( "refreshBottomTextCtrl" ) )
      schedule(0, 0, "refreshBottomTextCtrl");
}

function PlayGui::onSleep(%this)
{
   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
   
   // pop the keymaps
   moveMap.pop();
}

function PlayGui::clearHud( %this )
{
   Canvas.popDialog( MainChatHud );

   while ( %this.getCount() > 0 )
      %this.getObject( 0 ).delete();
}

//-----------------------------------------------------------------------------

function refreshBottomTextCtrl()
{
   BottomPrintText.position = "0 0";
}

function refreshCenterTextCtrl()
{
   CenterPrintText.position = "0 0";
}

//-----------------------------------------------------------------------------

function Iris::setDelta(%this, %dt)
{
   %this.zSizeDelta = %dt;
   %this.animationThread();
}

function Iris::animationThread(%this)
{
   if(%this.zAnimationThread !$= "")
   {
      cancel(%this.zAnimationThread);
      %this.zAnimationThread = "";
   }
      
   %this.size += %this.zSizeDelta;
   
   if(%this.size <= 0)
      %this.size = 0;
   //else if(%this.size >= 1)
   //   %this.size = 1;
   else
      %this.zAnimationThread = %this.schedule(32, "animationThread");
}

//-----------------------------------------------------------------------------

function setFovDelta(%dt)
{
   $fovDelta = %dt;
   fovDeltaThread();
}

function fovDeltaThread(%this)
{
   if($fovDeltaThread !$= "")
   {
      cancel($fovDeltaThread);
      $fovDeltaThread = "";
   }
   
   if($fovDelta == 0)
      return;

   %newFov = ServerConnection.getControlCameraFov() + $fovDelta;
   setFov(%newFov);

   if(%newFov < 1 || %newFov > 179)
      return;
      
   $fovDeltaThread = schedule(32, ServerConnection, "fovDeltaThread");
}


//-----------------------------------------------------------------------------
