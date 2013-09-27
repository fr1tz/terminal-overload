// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeFrontlineServerScripts()
{
   exec("alux3d/server/weapons/pineapple/v1/exec.cs");

   exec("./frontlineGame.cs");
   exec("./grid.cs");
   exec("./metaSoilEdit.cs");
   exec("./metaSoilEditAux.cs");
   exec("./metaSoilEditSetup.cs");
   exec("./metaSoilEditTweak.cs");
   exec("./metaSoilEditWorker.cs");
   //exec("./unfinishedSoilTile.cs");
   exec("./soil.sfx.cs");
   exec("./soil.gfx.cs");
   exec("./soil.cs");
}

executeFrontlineServerScripts();

