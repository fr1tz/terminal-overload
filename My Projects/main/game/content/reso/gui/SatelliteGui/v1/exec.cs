// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if(isFunction("unloadContentModule_ResoSatelliteGui"))
   unloadContentModule_ResoSatelliteGui();

function loadContentModule_ResoSatelliteGui()
{
   exec("./SatelliteGui.cs");
   exec("./SatelliteGui.gui");
}

function unloadContentModule_ResoSatelliteGui()
{

}

loadContentModule_ResoSatelliteGui();

