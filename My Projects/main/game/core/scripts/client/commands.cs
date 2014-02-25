// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Sync the Camera and the EditorGui
function clientCmdSyncEditorGui()
{
   if (isObject(EditorGui))
      EditorGui.syncCameraGui();
}

function clientCmdExecContentScript(%path)
{
   if(strstr(%path, ".." ) != -1)
   {
      echo("clientCmdExecContentScript(): skipping" SPC %path);
      return;
   }
   %stor = $instantGroup;
   $instantGroup = ClientMissionCleanup;
   exec("content/" @ %path);
   $instantGroup = %stor;
}

