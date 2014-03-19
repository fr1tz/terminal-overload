// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmdXaNotcSettings1_Query(%setting)
{
   echo("clientCmdXaNotcSettings1_Query():" SPC %setting);

   %value = "";
   if(%setting $= "PlayerColor0")
      %value = $Pref::NOTC1::PlayerColor0;
   else if(%setting $= "PlayerColor1")
      %value = $Pref::NOTC1::PlayerColor1;

   commandToServer('XaNotcSettings1_Reply', %setting, %value);
}

function clientCmdXaNotcSettings1_Confirmation(%setting, %status)
{
   echo("clientCmdXaNotcSettings1_Confirmation():" SPC %setting SPC %status);
}

