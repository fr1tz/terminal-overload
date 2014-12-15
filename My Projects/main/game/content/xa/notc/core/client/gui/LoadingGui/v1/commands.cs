// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmd_XaNotcLoadingGui_SetLeftPanel(%text, %append)
{
   //echo("clientCmd_XaNotcLoadingGui_SetLeftPanel()");
   if(%append)
      XaNotcLoadingGui-->LeftPanel.addText(%text);
   else
      XaNotcLoadingGui-->LeftPanel.setText(%text);
}

function clientCmd_XaNotcLoadingGui_SetRightPanel(%text, %append)
{
   //echo("clientCmd_XaNotcLoadingGui_SetRightPanel()");
   if(%append)
      XaNotcLoadingGui-->RightPanel.addText(%text);
   else
      XaNotcLoadingGui-->RightPanel.setText(%text);
}

