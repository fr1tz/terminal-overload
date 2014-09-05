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
         IngameMenuDlg-->ExitButton.setText("Exit From Mission");
      else
         IngameMenuDlg-->ExitButton.setText("Disconnect From Server");
      Canvas.pushDialog(IngameMenuDlg);
   }
}

