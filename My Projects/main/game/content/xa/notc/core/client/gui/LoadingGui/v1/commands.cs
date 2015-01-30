// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmd_XaNotcLoadingGui_SetBackground(%bitmap)
{
   //echo("clientCmd_XaNotcLoadingGui_SetBackground()");
   if(isFile(%bitmap))
   {
      XaNotcLoadingGui-->bg.setBitmap(%bitmap);
      XaNotcLoadingGui-->bg.setVisible(true);
   }
   else
      XaNotcLoadingGui-->bg.setVisible(false);
}


function clientCmd_XaNotcLoadingGui_SetLayer(%layer, %text, %append)
{
   //echo("clientCmd_XaNotcLoadingGui_SetLayer()");
   switch(%layer)
   {
      case 1: %ctrl = XaNotcLoadingGui-->layer1;
      case 2: %ctrl = XaNotcLoadingGui-->layer2;
      case 3: %ctrl = XaNotcLoadingGui-->layer3;
      default: return;
   }
   
   if(%append)
      %ctrl.addText(%text);
   else
      %ctrl.setText(%text);
}


