// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeFrontlineServerScripts()
{
   exec("alux3d/server/base/exec.cs");

   exec("alux3d/server/forms/light/exec.cs");
   
   exec("alux3d/server/weapons/badger/v1/exec.cs");
   exec("alux3d/server/weapons/raptor/v1/exec.cs");
   exec("alux3d/server/weapons/bulldog/v1/exec.cs");
   exec("alux3d/server/weapons/siberion/v1/exec.cs");
   exec("alux3d/server/weapons/pineapple/v1/exec.cs");

   exec("./frontlineGame.cs");
   exec("./teams.cs");
   exec("./etherform.cs");
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

