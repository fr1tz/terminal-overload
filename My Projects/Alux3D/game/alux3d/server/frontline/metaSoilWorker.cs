// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metaSoil.txt for documentation

function MetaSoil::initWorkerSet(%func)
{
   if(!isObject(Game.metaSoilWorkerSet))
   {
      Game.metaSoilWorkerSet = new SimSet();
      MissionCleanup.add(Game.metaSoilWorkerSet);
      return true;
   }
   else if(Game.metaSoilWorkerSet.getCount() > 0)
   {
      error("MetaSoil working set not empty!");
      return false;
   }
   Game.metaSoilWorkerFunc = %func;
   return true;
}

function MetaSoil::workerSet()
{
   return Game.metaSoilWorkerSet;
}

function MetaSoil::workerFunc()
{
   return Game.metaSoilWorkerFunc;
}

function MetaSoil::workerThread()
{
   if(Game.metaSoilWorkerThread !$= "")
   {
      cancel(Game.metaSoilWorkerThread);
      Game.metaSoilWorkerThread = "";
   }
   Game.metaSoilWorkerThread = schedule(8, Game, "MetaSoil::workerThread");
   
   if(MetaSoil::workerSet().getCount() > 0)
   {
		%tile = MetaSoil::workerSet().getObject(0);
      %done = %tile.getDataBlock().call(MetaSoil::workerFunc(), %tile);
      if(%done)
         MetaSoil::workerSet().remove(%tile);
   }
}

