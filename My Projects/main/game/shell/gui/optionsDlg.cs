// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function OptionsDlg::setContent(%this, %ctrl)
{
   //echo("OptionsDlg::setContent():" SPC %ctrl);

   if(%this.zContent $= %ctrl)
      return;
   
   // Clean content container.
   if(isObject(%this.zContent) && isObject(%this.zContentOriginalParent))
      %this.zContentOriginalParent.add(%this.zContent);
   %this-->ContentContainer.clear();
   
   %content = %ctrl;
   %contentOriginalParent = %ctrl.getParent();
   
   if(isObject(%content))
   {
      %this-->ContentContainer.add(%content);
      %content.setPosition(0, 0);
      %content.setExtent(%this-->ContentContainer.getExtent());
      %this.zContent = %content;
      %this.zContentOriginalParent = %contentOriginalParent;
   }
}

function OptionsDlg::onWake(%this)
{
   //echo("OptionsDlg::onWake()");

   if(%this-->ContentContainer.getCount() == 0)
      %this-->PlayerButton.performClick();
}

function OptionsDlg::onSleep(%this)
{
   //echo("OptionsDlg::onSleep()");

   savePrefs();
}

