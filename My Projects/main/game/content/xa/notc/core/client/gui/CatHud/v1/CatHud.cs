// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function notcCatHud::onWake(%this)
{
   %this.tickThread();
}

function notcCatHud::onSleep(%this)
{
   cancel(%this.zTickThread);
}

function notcCatHud::setMeter(%this, %meterCtrl, %percent)
{
   %count = %meterCtrl.getCount();
   %visible = mFloor(%count * %percent);
   for(%i = 0; %i < %count; %i++)
   {
      %blip = %meterCtrl.getObject(%i);
      %blip.setVisible(%i < %visible);
   }
   %meterCtrl.zNumVisible = %visible;
}

function notcCatHud::tickThread(%this)
{
   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(64, "tickThread");

   if(!isObject(ServerConnection))
      return;

   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;
      
   %data = %control.getDataBlock();
   %damageDamper = %control.getEnergyLevel(0) / %data.maxEnergy[0];
   %impulseDamper = %control.getEnergyLevel(1) / %data.maxEnergy[1];
   %xJump = %control.getEnergyLevel(2) / %data.maxEnergy[2];
   %xJumpCharge = %control.getXJumpCharge() / %data.maxEnergy[2];
   %damageBuffer = %control.getDamageBufferLevel() / %data.damageBuffer;
   %health = 1 - %control.getDamageLevel() / %data.maxDamage;

   notcCatHud-->xJump.setValue(%xJump);
   notcCatHud-->xJumpCharge.setValue(%xJumpCharge);

   %this.setMeter(notcCatHud-->dpblips, %damageDamper);
   %this.setMeter(notcCatHud-->kpblips, %impulseDamper);
   %this.setMeter(notcCatHud-->shieldblips, %damageBuffer);
   %this.setMeter(notcCatHud-->healthblips, %health);

   %dpMax = 50;
   if(%this.zMaxDamageProtection !$= "")
      %dpMax = %this.zMaxDamageProtection;
   %dp = mFloatLength(%damageDamper*%dpMax, 0);

   %kpMax = 75;
   if(%this.zMaxKnockbackProtection !$= "")
      %kpMax = %this.zMaxKnockbackProtection;
   %kp = mFloatLength(%impulseDamper*%kpMax, 0);

   notcCatHud-->dpnumber.setNumber(%dp);
   notcCatHud-->kpnumber.setNumber(%kp);
   
   if(notcCatHud-->dpblips.zNumVisible <= 6)
      notcCatHudDamageProtectionProfile.fillColor = "255 25 25 200";
   else if(notcCatHud-->dpblips.zNumVisible <= 9)
      notcCatHudDamageProtectionProfile.fillColor = "255 100 0 175";
   else
      notcCatHudDamageProtectionProfile.fillColor = "50 255 50 150";

   if(isObject(MiscHud))
   {
      %impulseDamperPercent = mFloatLength(%impulseDamper*75, 0) @ "%";
      MiscHud-->ImpulseDamperText.setText(%impulseDamperPercent);
      MiscHud-->ImpulseDamperGraph.addDatum(0, %impulseDamper);
      %damageDamperPercent = mFloatLength(%damageDamper*50, 0) @ "%";
      MiscHud-->DamageDamperText.setText(%damageDamperPercent);
      MiscHud-->DamageDamperGraph.addDatum(0, %damageDamper);
      %damageBufferText = mFloatLength(%control.getDamageBufferLevel(), 0);
      MiscHud-->DamageBufferText.setText(%damageBufferText);
      MiscHud-->DamageBufferGraph.addDatum(0, %damageBuffer);
      %healthText = mFloatLength(%data.maxDamage-%control.getDamageLevel(), 0);
      MiscHud-->HealthText.setText(%healthText);
      MiscHud-->HealthGraph.addDatum(0, %health);
   }

   if(isObject(XaNotcVitalsHud))
   {
      XaNotcVitalsHud-->ImpulseDamperGraph.addDatum(0, %impulseDamper);
      XaNotcVitalsHud-->DamageDamperGraph.addDatum(0, %damageDamper);
      XaNotcVitalsHud-->DamageBufferGraph.addDatum(0, %damageBuffer);
      XaNotcVitalsHud-->HealthGraph.addDatum(0, %health);
   }
}

//-----------------------------------------------------------------------------
