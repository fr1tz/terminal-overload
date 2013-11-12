// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeFrontlineServerScripts()
{
   exec("alux3d/server/base/exec.cs");

   exec("alux3d/server/forms/light/exec.cs");
   exec("alux3d/server/forms/brick/exec.cs");
   exec("alux3d/server/forms/soldierpod/exec.cs");
   exec("alux3d/server/forms/soldier/exec.cs");
   
   exec("alux3d/server/weapons/badger/v1/exec.cs");
   exec("alux3d/server/weapons/raptor/v1/exec.cs");
   exec("alux3d/server/weapons/bulldog/v1/exec.cs");
   exec("alux3d/server/weapons/siberion/v1/exec.cs");
   exec("alux3d/server/weapons/pineapple/v1/exec.cs");
   exec("alux3d/server/weapons/crackpack/v1/exec.cs");

   exec("./etherform.cs");
   exec("./frontlineActions.cs");
   exec("./frontlineBasics.cs");
   exec("./frontlineEtherforms.cs");
   exec("./frontlinePrepare.cs");
   exec("./frontlineRounds.cs");
   exec("./frontlineTeams.cs");
   exec("./gameBase.cs");
   exec("./grid.cs");
   exec("./loadout.cs");
   exec("./metaSoilEdit.cs");
   exec("./metaSoilEditAux.cs");
   exec("./metaSoilEditSetup.cs");
   exec("./metaSoilEditTweak.cs");
   exec("./metaSoilEditWorker.cs");
   exec("./shapeBase.cs");
   exec("./soil.cs");
   exec("./soil.gfx.cs");
   exec("./soil.sfx.cs");
   //exec("./unfinishedSoilTile.cs");
}

executeFrontlineServerScripts();

