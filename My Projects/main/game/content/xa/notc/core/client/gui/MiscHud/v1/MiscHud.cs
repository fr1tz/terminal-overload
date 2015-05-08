// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

package MiscHud
{
   function clientCmdGameStart(%seq)
   {
      Parent::clientCmdGameStart(%seq);
      HudGameTimer.visible = false;
   }
   
   function clientCmdGameTimer(%timeLeft)
   {
      HudGameTimer.setTimeLeft(%timeLeft);
   }
   
   function clientCmdSetFovDelta(%dt)
   {
      setFovDelta(%dt);
   }

   function clientCmdViewSetHud(%hud, %teamId)
   {
      %valid = false;
      if(%hud $= "LightHud")
         %valid = true;
      if(%hud $= "SoldierHud")
         %valid = true;

      if(!%valid)
         return;

      %hud.zTeamId = %teamId;
      $PlayGui = %hud;
      Canvas.setContent($PlayGui);
   }

   function clientCmdViewSetIris(%sizeX, %dtX, %sizeY, %dtY)
   {
      if(%sizeX !$= "")
         Iris.sizeX = %sizeX;
      if(%dtX !$= "")
         Iris.setDeltaX(%dtX);
      if(%sizeY !$= "")
         Iris.sizeY = %sizeY;
      if(%dtY !$= "")
         Iris.setDeltaY(%dtY);
   }
   
   function clientCmdLeftPrint(%text)
   {
      if(%text $= "")
         leftPrintText.setText("");
      else
         leftPrintText.setText(leftPrintText.getText() @ %text);
   }

   //---------------------------------------------------------------------------

   function refreshBottomTextCtrl()
   {
      BottomPrintText.position = "0 0";
   }

   function refreshCenterTextCtrl()
   {
      CenterPrintText.position = "0 0";
   }

   //---------------------------------------------------------------------------

   function HudGameTimer::setTimeLeft(%this, %timeLeft)
   {
      %this.zTimeLeft = %timeLeft;
      %this.updateThread();
      %this.visible = true;
   }

   function HudGameTimer::updateThread(%this)
   {
      if(%this.zUpdateThread !$= "")
      {
         cancel(%this.zUpdateThread);
         %this.zUpdateThread = "";
      }

      %this.text = mFloatLength(%this.zTimeLeft, 1);
      %this.zTimeLeft -= 0.1;

      if(%this.zTimeLeft < 0)
         %this.zTimeLeft = 0;
      else
         %this.zUpdateThread = %this.schedule(100, "updateThread");
   }

   //---------------------------------------------------------------------------

   function Iris::setDeltaX(%this, %dt)
   {
      %this.zSizeDeltaX = %dt;
      %this.animationThread();
   }

   function Iris::setDeltaY(%this, %dt)
   {
      %this.zSizeDeltaY = %dt;
      %this.animationThread();
   }

   function Iris::animationThread(%this)
   {
      if(%this.zAnimationThread !$= "")
      {
         cancel(%this.zAnimationThread);
         %this.zAnimationThread = "";
      }

      %this.sizeX += %this.zSizeDeltaX;
      %this.sizeY += %this.zSizeDeltaY;

      //$CAPostFx::cubeDistortionFactor = %this.size/10;
      %r = getWord($CAPostFx::colorDistortionFactor, 0);
      %g = getWord($CAPostFx::colorDistortionFactor, 1);
      %b = getWord($CAPostFx::colorDistortionFactor, 2);
      %r += %this.zSizeDelta/50;
      %g -= %this.zSizeDelta/50;
      %b += %this.zSizeDelta/100;
      //$CAPostFx::colorDistortionFactor = %r SPC %g SPC %b;

      if(%this.size <= 0)
         %this.size = 0;
      //else if(%this.size >= 1)
      //   %this.size = 1;
      else
         %this.zAnimationThread = %this.schedule(32, "animationThread");
   }

   //---------------------------------------------------------------------------

   function setFovDelta(%dt)
   {
      $fovDelta = %dt;
      fovDeltaThread();
   }

   function fovDeltaThread(%this)
   {
      if($fovDeltaThread !$= "")
      {
         cancel($fovDeltaThread);
         $fovDeltaThread = "";
      }

      if($fovDelta == 0)
         return;

      %newFov = ServerConnection.getControlCameraFov() + $fovDelta;
      setFov(%newFov);

      if(%newFov < 1 || %newFov > 179)
         return;

      $fovDeltaThread = schedule(32, ServerConnection, "fovDeltaThread");
   }
   
   //---------------------------------------------------------------------------
};

activatePackage(MiscHud);

function MiscHud::onAdd(%this)
{
   LagOverlay.zCurrentNoise = 0;
}

function MiscHud::onWake(%this)
{
   // Start tick thread.
   %this.tickThread();
   %this.animThread();
}

function MiscHud::onSleep(%this)
{
   cancel(%this.zTickThread);
   cancel(%this.zAnimThread);
}

function MiscHud::animThread(%this)
{
   if(%this.zAnimThread !$= "")
   {
      cancel(%this.zAnimThread);
      %this.zAnimThread = "";
   }
   %this.zAnimThread = %this.schedule(16, "animThread");
   
   LagOverlay-->noise.setValue(getRandom(0, 1024), getRandom(0, 1024));

   if(LagIcon.isVisible())
   {
      LagIcon.zBlinkDelay--;
      if(LagIcon.zBlinkDelay <= 0)
      {
         LagIcon-->flash.setVisible(!LagIcon-->flash.isVisible());
         LagIcon.zBlinkDelay = 30;
      }
   }
   else
   {
      LagIcon-->flash.setVisible(true);
      LagIcon.zBlinkDelay = 30;
   }

   if(!isObject(ServerConnection))
      return;
      
   %lastMoveAck = ServerConnection.getMoveListLastMoveAck();
   %lastClientMove = ServerConnection.getMoveListLastClientMove();
   %firstMoveIndex = ServerConnection.getMoveListFirstMoveIndex();
   %moveVecSize = ServerConnection.getMoveListMoveVecSize();

   //echo(%lastMoveAck SPC %lastClientMove SPC %firstMoveIndex SPC %moveVecSize);
      
   %x = %lastClientMove-%lastMoveAck;
   //echo(%x);
   if(%x >= 30)
   {
      LagOverlay-->frozen.setVisible(true);
      %targetNoise = 1;
   }
   else
   {
      LagOverlay-->frozen.setVisible(false);
      %targetNoise = mClamp(%x-10, 0, 20)/50;
      %targetNoise += ServerConnection.getPacketLoss()/2;
   }

   if(%targetNoise > LagOverlay.zCurrentNoise)
   {
      LagOverlay.zCurrentNoise += 0.01;
      if(LagOverlay.zCurrentNoise > %targetNoise)
         LagOverlay.zCurrentNoise = %targetNoise;
   }
   else
   {
      LagOverlay.zCurrentNoise -= 0.01;
      if(LagOverlay.zCurrentNoise < %targetNoise)
         LagOverlay.zCurrentNoise = %targetNoise;
   }

   //echo(LagOverlay.zCurrentNoise SPC "->" SPC %targetNoise);

   notcMiscHudLatencyNoiseProfile.fillColor = "255 255 255" SPC 255*LagOverlay.zCurrentNoise;


   
   if(LagOverlay-->frozen.isVisible())
   {
      LagOverlay-->frozen-->flash.zBlinkDelay--;
      if(LagOverlay-->frozen-->flash.zBlinkDelay <= 0)
      {
         LagOverlay-->frozen-->flash.setVisible(!LagOverlay-->frozen-->flash.isVisible());
         LagOverlay-->frozen-->flash.zBlinkDelay = 30;
      }
   }
   else
   {
      LagOverlay-->frozen-->flash.setVisible(true);
      LagOverlay-->frozen-->flash.zBlinkDelay = 30;
   }
}

function MiscHud::tickThread(%this)
{
   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(64, "tickThread");
   
   %this-->ImpulseDamperText.setText(" ---");
   %this-->DamageDamperText.setText(" ---");
   %this-->DamageBufferText.setText(" ---");
   %this-->HealthText.setText(" ---");
   
   if(!isObject(ServerConnection))
      return;

   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;
      
   if(%control.getClassName() $= "Etherform")
      return;

   %data = %control.getDataBlock();
   %damageDamper = %control.getEnergyLevel(0) / %data.maxEnergy[0];
   %impulseDamper = %control.getEnergyLevel(1) / %data.maxEnergy[1];
   %xJump = %control.getEnergyLevel(2) / %data.maxEnergy[2];
   %xJumpCharge = %control.getXJumpCharge() / %data.maxEnergy[2];
   %damageBuffer = %control.getDamageBufferLevel() / %data.damageBuffer;
   %health = 1 - %control.getDamageLevel() / %data.maxDamage;

   %impulseDamperPercent = mFloatLength(%impulseDamper*75, 0) @ "%";
   %this-->ImpulseDamperText.setText(%impulseDamperPercent);
   %this-->ImpulseDamperGraph.addDatum(0, %impulseDamper);
   %damageDamperPercent = mFloatLength(%damageDamper*50, 0) @ "%";
   %this-->DamageDamperText.setText(%damageDamperPercent);
   %this-->DamageDamperGraph.addDatum(0, %damageDamper);
   %damageBufferText = mFloatLength(%control.getDamageBufferLevel(), 0);
   %this-->DamageBufferText.setText(%damageBufferText);
   %this-->DamageBufferGraph.addDatum(0, %damageBuffer);
   %healthText = mFloatLength(%data.maxDamage-%control.getDamageLevel(), 0);
   %this-->HealthText.setText(%healthText);
   %this-->HealthGraph.addDatum(0, %health);
}


