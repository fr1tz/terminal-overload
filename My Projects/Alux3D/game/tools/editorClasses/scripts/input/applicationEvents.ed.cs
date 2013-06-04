// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

///
/// Public Application Events
///
Input::GetEventManager().registerEvent( "ClosePressed" );
Input::GetEventManager().registerEvent( "BeginShutdown" );
Input::GetEventManager().registerEvent( "FocusChanged" );

function onClosePressed()
{
   //error("% Application Close - User Pressed the X button on their window");
   Input::GetEventManager().postEvent( "ClosePressed" );
}

function onPreExit()
{
   //error("% Application Close - quit called or quit message received"");
   Input::GetEventManager().postEvent( "BeginShutdown" );   
}

function onWindowFocusChange( %focused )
{
   //error("% Application Close - quit called or quit message received"");
   Input::GetEventManager().postEvent( "FocusChanged", %focused );
}