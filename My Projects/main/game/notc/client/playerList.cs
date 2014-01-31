// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Hook into the client update messages to maintain our player list and scores.
//-----------------------------------------------------------------------------

addMessageCallback('MsgClientJoin', handleClientJoin);
addMessageCallback('MsgClientDrop', handleClientDrop);
addMessageCallback('MsgClientScoreChanged', handleClientScoreChanged);

function handleClientJoin(%msgType, %msgString, %clientName, %clientId, %guid,
      %score, %kills, %deaths, %isAI, %isAdmin, %isSuperAdmin)
{
   PlayerListGui.update(%clientId, detag(%clientName), %isSuperAdmin, %isAdmin,
   %isAI, %score, %kills, %deaths);
}

function handleClientDrop(%msgType, %msgString, %clientName, %clientId)
{
   PlayerListGui.remove(%clientId);
}

function handleClientScoreChanged(%msgType, %msgString, %score, %kills, %deaths, %clientId)
{
   PlayerListGui.updateScore(%clientId, %score, %kills, %deaths);
   echo(" score:"@%score@" kills:"@%kills@" deaths:"@%deaths);
}

// ----------------------------------------------------------------------------
// GUI methods
// ----------------------------------------------------------------------------

function PlayerListGui::update(%this, %clientId, %name, %isSuperAdmin, %isAdmin, %isAI, %score, %kills, %deaths)
{
   // Build the row to display.  The name can have ML control tags, including
   // color and font.  Since we're not using an ML control here, we need to
   // strip them off.
   %tag = %isSuperAdmin ? "[Super]" :
      (%isAdmin ? "[Admin]" :
      (%isAI ? "[Bot]" :
      ""));
   %text = StripMLControlChars(%name) SPC %tag TAB %score TAB %kills TAB %deaths;

   // Update or add the player to the control
   if (PlayerListGuiList.getRowNumById(%clientId) == -1)
      PlayerListGuiList.addRow(%clientId, %text);
   else
      PlayerListGuiList.setRowById(%clientId, %text);

   // Sorts by score
   PlayerListGuiList.sortNumerical(1, false);
   PlayerListGuiList.clearSelection();
}

function PlayerListGui::updateScore(%this, %clientId, %score, %kills, %deaths)
{
   %text = PlayerListGuiList.getRowTextById(%clientId);
   %text = setField(%text, 1, %score);
   %text = setField(%text, 2, %kills);
   %text = setField(%text, 3, %deaths);
   PlayerListGuiList.setRowById(%clientId, %text);
   PlayerListGuiList.sortNumerical(1, false);
   PlayerListGuiList.clearSelection();
}

function PlayerListGui::remove(%this, %clientId)
{
   PlayerListGuiList.removeRowById(%clientId);
}

function PlayerListGui::toggle(%this)
{
   if (%this.isAwake())
      Canvas.popDialog(%this);
   else
      Canvas.pushDialog(%this);
}

function PlayerListGui::clear(%this)
{
   // Override to clear the list.
   PlayerListGuiList.clear();
}

function PlayerListGui::zeroScores(%this)
{
   for (%i = 0; %i < PlayerListGuiList.rowCount(); %i++)
   {
      %text = PlayerListGuiList.getRowText(%i);
      %text = setField(%text, 1, "0");
      %text = setField(%text, 2, "0");
      %text = setField(%text, 3, "0");
      PlayerListGuiList.setRowById(PlayerListGuiList.getRowId(%i), %text);
   }
   PlayerListGuiList.clearSelection();
}
