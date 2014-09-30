// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function CatGui::onWake(%this)
{
   // Turn off any shell sounds...
   // sfxStop( ... );
   
   setFov($Pref::NOTC1::DefaultFov);

   $enableDirectInput = "1";
   activateDirectInput();
   
   Canvas.pushDialog(MiscHud);
   Canvas.pushDialog(XaNotcMinimapHud);
   Canvas.pushDialog(XaNotcCatHud);

   // Message hud dialog
   if ( isObject( MainChatHud ) )
   {
      Canvas.pushDialog( MainChatHud );
      chatHud.attach(HudMessageVector);
   }      
   
   // just update the action map here
   XaNotc1MiscMoveMap_activate();
   XaNotc1CatMoveMap_activate();
   
   // Start tick thread.
   %this.tickThread();

   // hack city - these controls are floating around and need to be clamped
   if ( isFunction( "refreshCenterTextCtrl" ) )
      schedule(0, 0, "refreshCenterTextCtrl");
   if ( isFunction( "refreshBottomTextCtrl" ) )
      schedule(0, 0, "refreshBottomTextCtrl");
}

function CatGui::onSleep(%this)
{
   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
      
   cancel(%this.zTickThread);
   
   // pop the keymaps
   //XaNotc1CatMoveMap.pop();
}

function CatGui::clearHud( %this )
{
   Canvas.popDialog( MainChatHud );

   while ( %this.getCount() > 0 )
      %this.getObject( 0 ).delete();
}

function CatGui::tickThread(%this)
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
      
   //CatGuiDamageBufferText.setText(%control.getDamageBufferLevel());
   //CatGuiMassText.setText(%control.getMass());
   //%image = %control.getMountedImage(0);
   //if(isObject(%image))
   //{
   //   if(%image.ammoSource $= "Energy")
   //      CatGuiAmmoText.setText("-");
   //   else
   //      CatGuiAmmoText.setText(%control.getImageMagazineRounds(0));
   //}
   //else
   //   CatGuiAmmoText.setText("");
      
   %impshield = -1;
   %n = 0;
   if(%control.isMethod("getMountedObjectCount"))
      %n = %control.getMountedObjectCount();

   for(%i = 0; %i < %n; %i++)
   {
      %obj = %control.getMountedObject(%i);
      if(isObject(%obj) && %obj.getClassName() $= "BallastShape")
         %impshield = %obj;
   }

   if(isObject(%impshield))
      CatGuiImpShield.setValue(%impshield.getLevel());
   else
      CatGuiImpShield.setValue(0);
      
   %data = %control.getDataBlock();
   %damageDamper = %control.getEnergyLevel(0) / %data.maxEnergy[0];
   %impulseDamper = %control.getEnergyLevel(1) / %data.maxEnergy[1];
   %damageBuffer = %control.getDamageBufferLevel() / %data.damageBuffer;
   %health = 1 - %control.getDamageLevel() / %data.maxDamage;
   
   XaNotcCatHud-->impulseDamper.setValue(%impulseDamper);
   XaNotcCatHud-->damageDamper.setValue(%damageDamper);
      
   if(isObject(MiscHud))
   {
      MiscHud-->ImpulseDamperGraph.addDatum(0, %impulseDamper);
      MiscHud-->DamageDamperGraph.addDatum(0, %damageDamper);
      MiscHud-->DamageBufferGraph.addDatum(0, %damageBuffer);
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
