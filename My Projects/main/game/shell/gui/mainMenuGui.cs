// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function MainMenuGui::onAdd(%this)
{
   //echo("MainMenuGui::onAdd()");

   %this.zBitmapOffset = 0;
}

function MainMenuGui::onWake(%this)
{
   //echo("MainMenuGui::onWake()");
   
   MainMenuVersionString.setText($GameVersionString);

   if (isFunction("getWebDeployment") &&
       getWebDeployment() &&
       isObject(%this-->ExitButton))
      %this-->ExitButton.setVisible(false);
      
   if($GameVersionType !$= "public" && $GameVersionFeedbackURL !$= "")
   {
      if(WelcomeDlg.zUnderstood == false)
         Canvas.pushDialog(WelcomeDlg);
   }

   // Start tick thread.
   %this.tickThread();
}

function MainMenuGui::onSleep(%this)
{
   //echo("MainMenuGui::onSleep()");

   // Stop tick thread.
   cancel(%this.zTickThread);
}

function MainMenuGui::tickThread(%this)
{
   //echo("MainMenuGui::tickThread()");

   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(32, "tickThread");

   %this.zBitmapOffset--;
   %this-->Scanlines.setValue(%this.zBitmapOffset, %this.zBitmapOffset);
   %this-->Noise.setValue(getRandom(0, 100), getRandom(0, 100));
}

