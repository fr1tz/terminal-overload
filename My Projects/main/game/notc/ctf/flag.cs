// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ItemData(ctfFlag)
{
   // Basic Item properties
   shapeFile = "content/xa/notc/core/shapes/flag/p1/shape.dae";
   mass = 1;
   elasticity = 0.2;
   friction = 0.6;
   emap = true;

   // Dynamic properties defined by the scripts
   pickUpName = "Flag";
   description = "Flag";
};

function ctfFlag::onAdd(%this, %obj)
{
   //echo("ctfFlag::onAdd()");
   Parent::onAdd(%this, %obj);
   
   %obj.zShapeBaseHudInfo.setDatasetType(0, $HudInfoDatasetType::TeamID);
   %obj.zShapeBaseHudInfo.setDatasetIntField(0, %obj.getTeamId());
   %obj.zShapeBaseHudInfo.setDatasetType(2, $HudInfoDatasetType::IconID);
   %obj.zShapeBaseHudInfo.setDatasetIntField(2, 130);
}

function ctfFlag::onRemove(%this, %obj)
{
   //echo("ctfFlag::onRemove()");
   Parent::onAdd(%this, %obj);
}

function ctfFlag::onCollision(%this, %obj, %col, %vec, %vecLen)
{
   //echo("ctfFlag::onCollision()");
   
   if(!%col.isCAT)
      return;
   
   %flag = %obj;
   %cat = %col;

   %mount = %flag.getObjectMount();
   if(%flag.getTeamId() == %cat.getTeamId())
   {
      if(%mount)
      {
         // See if CAT is carrying enemy flag.
         %enemyFlag = "";
         %n = %cat.getMountedObjectCount();
         for(%i = 0; %i < %n; %i++)
         {
            %m = %cat.getMountedObject(%i);
            if(%m.getDataBlock() == %this)
            {
               %enemyFlag = %m;
               break;
            }
         }
         if(!isObject(%enemyFlag))
            return;
         if(!isObject(%enemyFlag.zFlagstand))
            return;
         Game.noFlagCallbacks = true;
         %enemyFlag.getDataBlock().returnToFlagstand(%enemyFlag);
         Game.noFlagCallbacks = false;
         CTF::onFlagCaptured(%flag.getTeamId());
      }
      else
         %flag.getDataBlock().returnToFlagstand(%flag);
   }
   else
   {
      if(!%mount || %mount == %flag.zFlagstand)
      {
         %mat = MatrixCreate("0 0.2 -1.5", "0 0 1 0");
         %cat.mountObject(%flag, 2, %mat);
      }
   }
}

function ctfFlag::returnToFlagstand(%this, %obj)
{
   //echo("ctfFlag::returnToFlagstand()");
   %flagstand = %obj.zFlagstand;
   if(isObject(%flagstand))
   {
      %flagstand.getDataBlock().returnFlag(%flagstand);
      if(Game.noFlagCallbacks == false)
         CTF::onFlagReturned(%obj.getTeamId());
   }
}

function ctfFlag::onMount(%this, %obj, %mount, %node)
{
   //echo("ctfFlag::onMount()");
   
   if(%mount != %obj.zFlagstand && Game.noFlagCallbacks == false)
      CTF::onFlagTaken(%obj.getTeamId());
   
   if(%obj.zReturnThread !$= "")
      cancel(%obj.zReturnThread);
}

function ctfFlag::onUnmount(%this, %obj, %mount)
{
   //echo("ctfFlag::onUnmount()");
   
   if(%mount != %obj.zFlagstand && Game.noFlagCallbacks == false)
      CTF::onFlagDropped(%obj.getTeamId());
      
   if(%obj.zReturnThread !$= "")
      cancel(%obj.zReturnThread);
   %obj.zReturnThread = %this.schedule(30000, "returnToFlagstand", %obj);
}

