// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//---------------------------------------------------------------------------------------------
// TCP Debugger
// To use the debugger, first call "dbgSetParameters(port, password);" from one instance of
// your game. Then, in another instance (either on the same system, or a different one) call
// "startDebugger();". Then use the gui to connect to the first instance with the port and
// password you first passed to dbgSetParameters.
//---------------------------------------------------------------------------------------------

function initializeDebugger()
{
   echo(" % - Initializing Debugger");
   
   // Load the scripts.
   exec("./Scripts/debugger.ed.cs");
   
   // And the guis.
   exec("./Gui/breakConditionDlg.ed.gui");
   exec("./Gui/connectDlg.ed.gui");
   exec("./Gui/editWatchDlg.ed.gui");
   exec("./Gui/findDlg.ed.gui");
   exec("./Gui/debugger.ed.gui");
   exec("./Gui/watchDlg.ed.gui");
}

function destroyDebugger()
{
   if (isObject(TCPDebugger))
      TCPDebugger.delete();
}

function startDebugger()
{
   // Clean up first.
   destroyDebugger();
   
   // Create a TCP object named TCPDebugger.
   new TCPObject(TCPDebugger);
   
   // Used to get unique IDs for breakpoints and watch expressions.
   $DbgBreakId = 0;
   $DbgWatchSeq = 1;
   
   // Set up the GUI.
   DebuggerConsoleView.setActive(false);
   Canvas.pushDialog(DebuggerGui);
}
