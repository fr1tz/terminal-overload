// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function toggleIngameMenu()
{
   if(IngameMenuDlg.isAwake())
   {
      Canvas.popDialog(IngameMenuDlg);
   }
   else
   {
      if($Server::ServerType $= "SinglePlayer")
         IngameMenuDlg-->ExitButton.setText("EXIT");
      else
         IngameMenuDlg-->ExitButton.setText("DISCONNECT");
      Canvas.pushDialog(IngameMenuDlg);
   }
}

