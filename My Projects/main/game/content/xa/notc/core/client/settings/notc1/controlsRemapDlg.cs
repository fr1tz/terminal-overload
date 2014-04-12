// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function XaNotcSettings1_Controls_RemapInputCtrl::onInputEvent( %this, %device, %action )
{
   call(%this.inputEventCallback, %device, %action);
}

