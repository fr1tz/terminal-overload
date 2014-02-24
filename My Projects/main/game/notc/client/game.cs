// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//----------------------------------------------------------------------------
// Game start / end events sent from the server
//----------------------------------------------------------------------------

function clientCmdGameStart(%seq)
{
   PlayerListGui.zeroScores();
   HudGameTimer.visible = false;
}

function clientCmdGameEnd(%seq)
{
   // Stop local activity... the game will be destroyed on the server
   sfxStopAll();
   
   if ((!EditorIsActive() && !GuiEditorIsActive()))
   {
      // Copy the current scores from the player list into the
      // end game gui (bit of a hack for now).
      EndGameGuiList.clear();
      for (%i = 0; %i < PlayerListGuiList.rowCount(); %i++)
      {
         %text = PlayerListGuiList.getRowText(%i);
         %id = PlayerListGuiList.getRowId(%i);
         EndGameGuiList.addRow(%id, %text);
      }
      EndGameGuiList.sortNumerical(1, false);

      // Display the end-game screen
      Canvas.setContent(EndGameGui);
   }
}
