// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

package xa_notc_deathmatch_client_gui_endgamegui
{
   function clientCmdGameEnd()
   {
      Parent::clientCmdGameEnd();
   
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
};

activatePackage(xa_notc_deathmatch_client_gui_endgamegui);

