// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// *** callback function: called by engine
function GameBaseData::onRemove(%this, %obj)
{
   %obj.beingRemoved = true;
   %obj.removePiecesFromPlay();
}

// Called by script code
function GameBase::removePiecesFromPlay(%this)
{
   if(%this.zPiecesRemovedFromPlay)
      return;

   if(%this.loadoutcode && %this.client)
   {
      %pieces = sLoadoutcode2Pieces(%this.loadoutcode);
      for(%f = 0; %f < getFieldCount(%pieces); %f++)
      {
         %field = getField(%pieces, %f);
         %piece = getWord(%field, 0);
         %count = getWord(%field, 1);
         %this.client.inventory.pieceUsed[%piece] -= %count;
         if(%this.zFormDestroyed)
            %this.client.inventory.pieceCount[%piece] -= %count;
            
         if(%piece == 0)
         {
            if(%this.client.player.getClassName() $= "Etherform")
               %this.client.player.updateVisuals();
         }
      }
   }

   %this.client.displayInventory();

   %this.zPiecesRemovedFromPlay = true;
}

// Called by script code
function GameBase::setLoadoutCode(%this, %loadoutcode)
{
   %client = %this.client;
   %this.loadoutcode = %loadoutcode;
   %pieces = sLoadoutcode2Pieces(%this.loadoutcode);
   for(%f = 0; %f < getFieldCount(%pieces); %f++)
   {
      %field = getField(%pieces, %f);
      %piece = getWord(%field, 0);
      %count = getWord(%field, 1);
      %client.inventory.pieceUsed[%piece] += %count;
   }
   %client.displayInventory();
}

// Called by script code
function GameBase::dematerialize(%this)
{
   %this.getDataBlock().dematerialize(%this);
}

// Called by script code
function GameBase::dematerializeFinish(%this)
{
   %this.getDataBlock().dematerializeFinish(%this);
}
