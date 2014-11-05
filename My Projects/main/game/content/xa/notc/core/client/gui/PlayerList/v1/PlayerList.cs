// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function showPlayerList(%val)
{
   if(%val)
   {
      Canvas.pushDialog(XaNotcPlayerList);
   }
   else
   {
      Canvas.popDialog(XaNotcPlayerList);
   }

   commandToServer('ShowingPlayerList', %val);
}

function clientCmd_XaNotcPlayerList_start(%update)
{
   //echo("clientCmd_XaNotcPlayerList_start()" SPC %update);
	XaNotcPlayerListLayer1.zText = "";
	XaNotcPlayerListLayer2.zText = "";
	XaNotcPlayerListLayer4.zText = "";
	XaNotcPlayerListLayer8.zText = "";
	if(%update)
	{
		XaNotcPlayerListScroll.zPrevPosX = XaNotcPlayerListScroll.getScrollPositionX();
		XaNotcPlayerListScroll.zPrevPosY = XaNotcPlayerListScroll.getScrollPositionY();
	}
	else
	{
		XaNotcPlayerListScroll.zPrevPosX = 0;
		XaNotcPlayerListScroll.zPrevPosY = 0;
	}
}

function clientCmd_XaNotcPlayerList_add(%text, %layerMask)
{
   //echo("clientCmd_XaNotcPlayerList_add()");
   if(%layerMask $= "")
   {
   	XaNotcPlayerListLayer1.zText = XaNotcPlayerListLayer1.zText @ %text;
      return;
   }
   if(%layerMask & 1)
   	XaNotcPlayerListLayer1.zText = XaNotcPlayerListLayer1.zText @ %text;
   if(%layerMask & 2)
   	XaNotcPlayerListLayer2.zText = XaNotcPlayerListLayer2.zText @ %text;
   if(%layerMask & 4)
   	XaNotcPlayerListLayer4.zText = XaNotcPlayerListLayer4.zText @ %text;
   if(%layerMask & 8)
   	XaNotcPlayerListLayer8.zText = XaNotcPlayerListLayer8.zText @ %text;
}

function clientCmd_XaNotcPlayerList_finish()
{
   //echo("clientCmd_XaNotcPlayerList_finish()");
	XaNotcPlayerListLayer1.setText(XaNotcPlayerListLayer1.zText);
	XaNotcPlayerListLayer2.setText(XaNotcPlayerListLayer2.zText);
	XaNotcPlayerListLayer4.setText(XaNotcPlayerListLayer4.zText);
	XaNotcPlayerListLayer8.setText(XaNotcPlayerListLayer8.zText);
	XaNotcPlayerListLayer1.forceReflow();
	XaNotcPlayerListLayer2.forceReflow();
	XaNotcPlayerListLayer4.forceReflow();
	XaNotcPlayerListLayer8.forceReflow();
	XaNotcPlayerListScroll.setScrollPosition(
		XaNotcPlayerListScroll.zPrevPosX,
		XaNotcPlayerListScroll.zPrevPosY
	);
}

