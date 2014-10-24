// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GameConnection::LoadoutHud_SelectSlot(%client, %slot)
{
   commandToClient(%client, 'XaNotcLoadoutHudSelectSlot', %slot);
}

function GameConnection::LoadoutHud_UpdateSlot(%client, %slot, %vis, %icon,
   %progress, %progressDt)
{
   %setup = %client.zDemoRecordingSetupInProgress;

   if(%vis !$= "")
   {
      if(!%setup && %client.zLoadoutHudVis[%slot] $= %vis)
         %vis = "";
      else
         %client.zLoadoutHudVis[%slot] = %vis;
   }
   
   if(%icon !$= "")
   {
      if(!%setup && %client.zLoadoutHudIcon[%slot] $= %icon)
         %icon = "";
      else
         %client.zLoadoutHudIcon[%slot] = %icon;
   }
   
   if(%progress !$= "")
   {
      if(!%setup && %client.zLoadoutHudProgress[%slot] $= %progress)
         %progress = "";
      else
         %client.zLoadoutHudProgress[%slot] = %progress;
   }
   
   if(%progressDt !$= "")
   {
      if(!%setup && %client.zLoadoutHudProgressDt[%slot] $= %progressDt)
         %progressDt = "";
      else
         %client.zLoadoutHudProgressDt[%slot] = %progressDt;
   }
   
   commandToClient(%client, 'XaNotcLoadoutHudUpdateSlot', %slot, %vis, %icon,
      %progress, %progressDt);
}

