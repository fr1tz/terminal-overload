// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmd_XaNotcHudIcons_SetHudInfoDatasetType_Color(%type)
{
   echo("clientCmd_XaNotcHudIcons_SetHudInfoDatasetType_Color()" SPC %type);
   CatGui-->hudIcons.hudInfoDatasetType_Color = %type;
   EtherformGui-->hudIcons.hudInfoDatasetType_Color = %type;
}

function clientCmd_XaNotcHudIcons_SetHudInfoDatasetType_Icon(%type)
{
   echo("clientCmd_XaNotcHudIcons_SetHudInfoDatasetType_Icon()" SPC %type);
   CatGui-->hudIcons.hudInfoDatasetType_Icon = %type;
   EtherformGui-->hudIcons.hudInfoDatasetType_Icon = %type;
}

function clientCmd_XaNotcHudIcons_ClearColors()
{
   echo("clientCmd_XaNotcHudIcons_ClearColors()");
   CatGui-->hudIcons.clearColors();
   EtherformGui-->hudIcons.clearColors();
}

function clientCmd_XaNotcHudIcons_ClearIcons()
{
   echo("clientCmd_XaNotcHudIcons_ClearIcons()");
   CatGui-->hudIcons.clearIcons();
   EtherformGui-->hudIcons.clearIcons();
}

function clientCmd_XaNotcHudIcons_AddColor(%id, %colorI)
{
   echo("clientCmd_XaNotcHudIcons_AddColor()" SPC %id SPC %colorI);
   CatGui-->hudIcons.addColor(%id, %colorI);
   EtherformGui-->hudIcons.addColor(%id, %colorI);
}

function clientCmd_XaNotcHudIcons_AddIcon(%id, %bitmap, %size)
{
   echo("clientCmd_XaNotcHudIcons_AddIcon()" SPC %id SPC %bitmap SPC %size);
   CatGui-->hudIcons.addIcon(%id, %bitmap, %size);
   EtherformGui-->hudIcons.addIcon(%id, %bitmap, %size);
}

