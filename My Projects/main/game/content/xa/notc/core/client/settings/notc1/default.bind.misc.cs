// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if ( isObject( XaNotc1MiscMoveMap ) )
   XaNotc1MiscMoveMap.delete();
new ActionMap(XaNotc1MiscMoveMap);

function XaNotc1MiscMoveMap_activate()
{
   XaNotc1MiscMoveMap.push();
}

//------------------------------------------------------------------------------

function XaNotc1MiscMoveMap_showPlayerList(%val)
{
   if (%val)
      PlayerListGui.toggle();
}

XaNotc1MiscMoveMap.bind( keyboard, Tab, XaNotc1MiscMoveMap_showPlayerList );

function XaNotc1MiscMoveMap_hideHUDs(%val)
{
   if (%val)
      HudlessPlayGui.toggle();
}

XaNotc1MiscMoveMap.bind(keyboard, "ctrl h", XaNotc1MiscMoveMap_hideHUDs);

function XaNotc1MiscMoveMap_doScreenShotHudless(%val)
{
   if(%val)
   {
      canvas.setContent(HudlessPlayGui);
      //doScreenshot(%val);
      schedule(10, 0, "doScreenShot", %val);
   }
   else
      canvas.setContent($PlayGui);
}

XaNotc1MiscMoveMap.bind(keyboard, "alt p", XaNotc1MiscMoveMap_doScreenShotHudless);

function XaNotc1MiscMoveMap_toggleCamera(%val)
{
   if (%val)
      commandToServer('ToggleCamera');
}

XaNotc1MiscMoveMap.bind(keyboard, "alt c", XaNotc1MiscMoveMap_toggleCamera);

//------------------------------------------------------------------------------
// Message HUD functions
//------------------------------------------------------------------------------

function XaNotc1MiscMoveMap_toggleMessageHud( %val )
{
   if ( %val )
      toggleMessageHud(1);
}

function XaNotc1MiscMoveMap_pageMessageHudUp( %val )
{
   if ( %val )
      pageUpMessageHud();
}

function XaNotc1MiscMoveMap_pageMessageHudDown( %val )
{
   if ( %val )
      pageDownMessageHud();
}

function XaNotc1MiscMoveMap_resizeMessageHud( %val )
{
   if ( %val )
      cycleMessageHudSize();
}

XaNotc1MiscMoveMap.bind(keyboard, t, XaNotc1MiscMoveMap_toggleMessageHud );
//XaNotc1MiscMoveMap.bind(keyboard, y, XaNotc1MiscMoveMap_teamMessageHud );
XaNotc1MiscMoveMap.bind(keyboard, "pageUp", XaNotc1MiscMoveMap_pageMessageHudUp );
XaNotc1MiscMoveMap.bind(keyboard, "pageDown", XaNotc1MiscMoveMap_pageMessageHudDown );
//XaNotc1MiscMoveMap.bind(keyboard, "p", XaNotc1MiscMoveMap_resizeMessageHud );

//------------------------------------------------------------------------------
// Demo recording functions
//------------------------------------------------------------------------------

function XaNotc1MiscMoveMap_startRecordingDemo( %val )
{
   if ( %val )
      startDemoRecord();
}

function XaNotc1MiscMoveMap_stopRecordingDemo( %val )
{
   if ( %val )
      stopDemoRecord();
}

//XaNotc1MiscMoveMap.bind( keyboard, F3, XaNotc1MiscMoveMap_startRecordingDemo );
//XaNotc1MiscMoveMap.bind( keyboard, F4, XaNotc1MiscMoveMap_stopRecordingDemo );


//------------------------------------------------------------------------------
// Helper Functions
//------------------------------------------------------------------------------

function XaNotc1MiscMoveMap_bringUpOptions(%val)
{
   if (%val)
      Canvas.pushDialog(OptionsDlg);
}

XaNotc1MiscMoveMap.bind(keyboard, "ctrl o", XaNotc1MiscMoveMap_bringUpOptions);


//------------------------------------------------------------------------------
// Debugging Functions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
// Start profiler by pressing ctrl f3
// ctrl f3 - starts profile that will dump to console and file
//
function XaNotc1MiscMoveMap_doProfile(%val)
{
   if (%val)
   {
      // key down -- start profile
      echo("Starting profile session...");
      profilerReset();
      profilerEnable(true);
   }
   else
   {
      // key up -- finish off profile
      echo("Ending profile session...");

      profilerDumpToFile("profilerDumpToFile" @ getSimTime() @ ".txt");
      profilerEnable(false);
   }
}

GlobalActionMap.bind(keyboard, "ctrl F3", XaNotc1MiscMoveMap_doProfile);

//------------------------------------------------------------------------------
// Misc.
//------------------------------------------------------------------------------

XaNotc1MiscMoveMap.bindCmd(keyboard, "n", "toggleNetGraph();", "");

