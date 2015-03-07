// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmd_XaNotcMinimapHud_SetHudInfoDatasetType_Color(%type)
{
   echo("clientCmd_XaNotcMinimapHud_SetHudInfoDatasetType_Color()" SPC %type);
   XaNotcMinimapHud-->map.hudInfoDatasetType_Color = %type;
}

function clientCmd_XaNotcMinimapHud_SetHudInfoDatasetType_Icon(%type)
{
   echo("clientCmd_XaNotcMinimapHud_SetHudInfoDatasetType_Icon()" SPC %type);
   XaNotcMinimapHud-->map.hudInfoDatasetType_Icon = %type;
}

function clientCmd_XaNotcMinimapHud_ClearColors()
{
   echo("clientCmd_XaNotcMinimapHud_ClearColors()");
   XaNotcMinimapHud-->map.clearColors();
}

function clientCmd_XaNotcMinimapHud_ClearIcons()
{
   echo("clientCmd_XaNotcMinimapHud_ClearIcons()");
   XaNotcMinimapHud-->map.clearIcons();
}

function clientCmd_XaNotcMinimapHud_AddColor(%id, %colorI)
{
   echo("clientCmd_XaNotcMinimapHud_AddColor()" SPC %id SPC %colorI);
   XaNotcMinimapHud-->map.addColor(%id, %colorI);
}

function clientCmd_XaNotcMinimapHud_AddIcon(%id, %bitmap, %size)
{
   echo("clientCmd_XaNotcMinimapHud_AddIcon()" SPC %id SPC %bitmap SPC %size);
   XaNotcMinimapHud-->map.addIcon(%id, %bitmap, %size);
}

//------------------------------------------------------------------------------

function XaNotcMinimapHudEffectsLayer::onWake(%this)
{
   %this.tickThread();
}

function XaNotcMinimapHudEffectsLayer::onSleep(%this)
{
   cancel(%this.zTickThread);
}

function XaNotcMinimapHudEffectsLayer::tickThread(%this)
{
   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(64, "tickThread");

   %this-->monitorNoise.setValue(getRandom(0, 256), getRandom(0, 256));
}
