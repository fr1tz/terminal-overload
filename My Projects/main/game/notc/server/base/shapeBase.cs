// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// This file contains ShapeBase methods used by all the derived classes

//-----------------------------------------------------------------------------
// ShapeBase object
//-----------------------------------------------------------------------------

// A raycast helper function to keep from having to duplicate code everytime
// that a raycast is needed.
//  %this = the object doing the cast, usually a player
//  %range = range to search
//  %mask = what to look for

function ShapeBase::doRaycast(%this, %range, %mask)
{
   // get the eye vector and eye transform of the player
   %eyeVec = %this.getEyeVector();
   %eyeTrans = %this.getEyeTransform();

   // extract the position of the player's camera from the eye transform (first 3 words)
   %eyePos = getWord(%eyeTrans, 0) SPC getWord(%eyeTrans, 1) SPC getWord(%eyeTrans, 2);

   // normalize the eye vector
   %nEyeVec = VectorNormalize(%eyeVec);

   // scale (lengthen) the normalized eye vector according to the search range
   %scEyeVec = VectorScale(%nEyeVec, %range);

   // add the scaled & normalized eye vector to the position of the camera
   %eyeEnd = VectorAdd(%eyePos, %scEyeVec);

   // see if anything gets hit
   %searchResult = containerRayCast(%eyePos, %eyeEnd, %mask, %this);

   return %searchResult;
}

//-----------------------------------------------------------------------------

function ShapeBase::damage(%this, %sourceObject, %position, %damage, %damageType)
{
   // All damage applied by one object to another should go through this method.
   // This function is provided to allow objects some chance of overriding or
   // processing damage values and types.  As opposed to having weapons call
   // ShapeBase::applyDamage directly. Damage is redirected to the datablock,
   // this is standard procedure for many built in callbacks.

   if (isObject(%this))
      %this.getDataBlock().damage(%this, %sourceObject, %position, %damage, %damageType);
}

function ShapeBase::impulse(%this, %position, %impulseVec, %src)
{
   // All impulses applied by one object to another should go through this method.
   return %this.getDataBlock().impulse(%this, %position, %impulseVec, %src);
}

//-----------------------------------------------------------------------------

function ShapeBase::setDamageDt(%this, %damageAmount, %damageType)
{
   // This function is used to apply damage over time.  The damage is applied
   // at a fixed rate (50 ms).  Damage could be applied over time using the
   // built in ShapBase C++ repair functions (using a neg. repair), but this
   // has the advantage of going through the normal script channels.

   if (%this.getState() !$= "Dead")
   {
      %this.damage(0, "0 0 0", %damageAmount, %damageType);
      %this.damageSchedule = %this.schedule(50, "setDamageDt", %damageAmount, %damageType);
   }
   else
      %this.damageSchedule = "";
}

function ShapeBase::clearDamageDt(%this)
{
   if (%this.damageSchedule !$= "")
   {
      cancel(%this.damageSchedule);
      %this.damageSchedule = "";
   }
}

//-----------------------------------------------------------------------------

function ShapeBase::reloadWeapon(%this)
{
   %player = %this;
   %image = %player.getMountedImage($WeaponSlot);

   if(%image == 0)
      return;

   // Bail out if we're already reloading.
   if(%image.fireImage !$= "")
      return;

   if(%image.isField("ammo"))
   {
      if(%this.getInventory(%image.ammo) > 0)
         %this.mountImage(%image.reloadImage, $WeaponSlot);
   }
   else if(%image.isField("clip"))
   {
      if(%this.getInventory(%image.clip) > 0)
         %this.mountImage(%image.reloadImage, $WeaponSlot);
   }
}

//------------------------------------------------------------------------------

function ShapeBase::setHitSoundPitch(%this, %pitch)
{
   if(%pitch > %this.inflictedDamageSoundPitch)
      %this.inflictedDamageSoundPitch = %pitch;

   cancel(%this.inflictedDamageThread);
   %this.inflictedDamageThread = %this.schedule(0, "playHitSound");
}

function ShapeBase::playHitSound(%this)
{
   if(%this.client)
   {
      %pitch = 0.9 + %this.inflictedDamageSoundPitch / 2;
      commandToClient(%this.client, 'PlayHitSound', %pitch);
   }

   %this.inflictedDamageSoundPitch = 0;
   %this.inflictedDamageSoundLocked = false;
}

//-----------------------------------------------------------------------------
// ShapeBase datablock
//-----------------------------------------------------------------------------

function ShapeBaseData::onAdd(%this, %obj)
{
   Parent::onAdd(%this, %obj);

   // Default dynamic armor stats
   %obj.setDamageBufferRechargeRate(%this.damageBufferRechargeRate);
   %obj.setDamageBufferDischargeRate(%this.damageBufferDischargeRate);
   %obj.setRechargeRate(%this.rechargeRate);
   %obj.setRepairRate(0);
}

function ShapeBaseData::damage(%this, %obj, %source, %position, %amount, %damageType)
{
   if(%this.ignoreDamage)
      return;

	// Find original source object.
   %originalSource = 0;
   if(isObject(%source))
   {
      if(%source.getType() & $TypeMasks::ProjectileObjectType)
         %originalSource = %source.sourceObject;
      else if(%source.getType() & $TypeMasks::ShapeBaseObjectType)
         %originalSource = %source.client.player;
   }
   
   %damageBufStore = %obj.getDamageBufferLevel();
   %healthDamageDealt = %obj.applyDamage(%amount);
   %bufDamageDealt = %damageBufStore - %obj.getDamageBufferLevel();
   
   //error("ShapeBaseData::damage()");
   //echo("source:" SPC %source);
   //echo("amount:" SPC %amount);
   //echo("damageType:" SPC %damageType);
   //echo("originalSource:" SPC %originalSource);
   //echo("healthDamageDealt:" SPC %healthDamageDealt);
   //echo("bufDamageDealt:" SPC %bufDamageDealt);

   if(%originalSource != 0
   && %originalSource.teamId != %obj.teamId
   && %originalSource.getDamageState() $= "Enabled")
	{
		%stor = %originalSource.getDamageLevel();

      %this.onHitEnemy(
         %originalSource,
         %obj,
         %healthDamageDealt,
         %bufDamageDealt
      );
   }

   %bleed = %this.getBleed(%obj, %healthDamageDealt);
   if(isObject(%bleed))
   {
      %dpos = %position;
      %spos = %source.getPosition();
      %norm = VectorNormalize(VectorSub(%dpos, %obj.getWorldBoxCenter()));
      if(getWord(%norm, 2) < 0)
         %norm = VectorNormalize(VectorSub(%spos, %dpos));
      %colorI = %obj.paletteColors[0];
      if(%healthDamageDealt == 0)
         %colorI = "";
      createExplosion(%bleed, %dpos, %norm, %colorI);
   }
}

// Called by ShapeBase::impulse()
function ShapeBaseData::impulse(%this, %obj, %position, %impulseVec, %src)
{
   if(%obj != %src && %obj.zImpShield !$= "")
      %impulseVec = VectorScale(%impulseVec, 1-%obj.zImpShield);
   %obj.applyImpulse(%position, %impulseVec);
}

// Called by engine whenever the object's damage level changes.
function ShapeBaseData::onDamage(%this, %obj, %delta)
{
   // Avoid console error spam.
}

// Called by script
function ShapeBaseData::onHitEnemy(%this, %obj, %enemy, %healthDmg, %bufDmg)
{
   %client = %obj.client;
   if(!isObject(%client))
      return;
  
   %obj.setHitSoundPitch(%enemy.getDamagePercent());
}

