// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function BitmapInteger::setNumber(%this, %number)
{
   //echo("BitmapInteger::setNumber():" SPC %this SPC %number);
   %len = strlen(%number);
   %count = %this.getCount();
   for(%idx = 0; %idx < %count; %idx++)
   {
      %pos = %len - %idx - 1;
      if(%pos < 0)
         break;
      %digit = getSubStr(%number, %pos, 1);
      %this.getObject(%idx).setDigit(%digit);
   }

}

function BitmapDigit10::setDigit(%this, %digit)
{
   //echo("BitmapDigit10::setDigit():" SPC %this SPC %digit);
   %w = getWord(%this.getExtent(), 0);
   %h = getWord(%this.getExtent(), 1);
   %offsetX = (%digit-5) * %w;
   %offsetY = mCeil(%h/2);
   %this.setValue(%offsetX, %offsetY);
}
