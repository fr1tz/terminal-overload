// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmdXaNotcLoadoutHudUpdateSlot(%slot, %vis, %icon,
   %progress, %progressDt, %selection)
{
   XaNotcLoadoutHud.updateSlot(%slot, %vis, %icon, %progress, %progressDt);
}

function clientCmdXaNotcLoadoutHudSelectSlot(%slot)
{
   XaNotcLoadoutHud.selectSlot(%slot);
}

function XaNotcLoadoutHud::onAdd(%this)
{
   // Start tick thread.
   %this.tickThread();
}

function XaNotcLoadoutHud::selectSlot(%this, %slot)
{
   for(%i = 0; %i < 6; %i++)
   {
      %ctl = XaNotcLoadoutHudSlot @ %i;
      %ctl-->selected.setVisible(false);
   }
   %ctl = XaNotcLoadoutHudSlot @ %slot;
   %ctl-->selected.setVisible(true);
}

function XaNotcLoadoutHud::updateSlot(%this, %slot, %vis, %icon,
   %progress, %progressDt, %selection)
{
   %slotCtrl = XaNotcLoadoutHudSlot @ %slot;

   if(%vis !$= "")
   {
      %slotCtrl.setVisible(%vis);
   }

   if(%icon !$= "")
   {
      %slotCtrl-->icon.setBitmap(%icon);
   }

   if(%progress !$= "")
   {
      %slotCtrl-->progress.setValue(%progress);
   }

   if(%progressDt !$= "")
   {
      %slotCtrl.zProgressDt = %progressDt;
   }
}

function XaNotcLoadoutHud::tickThread(%this)
{
   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(32, "tickThread");
   
   for(%i = 0; %i < 6; %i++)
   {
      %slotCtrl = XaNotcLoadoutHudSlot @ %i;
      if(%slotCtrl.zProgressDt != 0)
      {
         %progress = %slotCtrl-->progress.getValue();
         echo(%progress);
         %progress += %slotCtrl.zProgressDt;
         %slotCtrl-->progress.setValue(%progress);
      }
   }
}

