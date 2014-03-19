// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function XaNotcSettings1_MiscGui::onWake(%this)
{
   //echo("XaNotcSettings1_MiscGui::onWake");
   
   if($InGuiEditor)
      return;

}

function XaNotcSettings1_MiscGui::onSleep(%this)
{
   //echo("XaNotcSettings1_MiscGui::onSleep");

}

function XaNotcSettings1_Misc_PlayerColor0::onAction(%this)
{
   %colori = "";
   for(%i = 0; %i < 3; %i++)
      %colori = %colori @ getWord(%this.pickColor, %i)*255 @ " ";
   %this.ToolTip = "Color:" SPC %colori;
   $Pref::NOTC1::PlayerColor0 = %colori;
   gameSettingsChanged("XaNotcSettings1");
}

function XaNotcSettings1_Misc_PlayerColor1::onAction(%this)
{
   %colori = "";
   for(%i = 0; %i < 3; %i++)
      %colori = %colori @ getWord(%this.pickColor, %i)*255 @ " ";
   %this.ToolTip = "Color:" SPC %colori;
   $Pref::NOTC1::PlayerColor1 = %colori;
   gameSettingsChanged("XaNotcSettings1");
}

function XaNotcSettings1_Misc_Update(%element)
{
   //echo(%element);
   if(%element $= "DefaultFov")
      setDefaultFov($Pref::NOTC1::DefaultFov);
}



