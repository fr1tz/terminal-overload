// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

package GuiChanger
{
   function clientCmdCanvasSetContent(%ctrl)
   {
      Parent::clientCmdCanvasSetContent();
      Canvas.setContent(%ctrl);
   }
   
   function clientCmdCanvasPushDialog(%ctrl)
   {
      Parent::clientCmdCanvasPushDialog();
      Canvas.pushDialog(%ctrl);
   }
   
   function clientCmdCanvasPopDialog(%ctrl)
   {
      Parent::clientCmdCanvasPopDialog();
      Canvas.popDialog(%ctrl);
   }
};

activatePackage(GuiChanger);

