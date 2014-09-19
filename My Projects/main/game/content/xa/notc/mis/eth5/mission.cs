// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Note: The server executes this file.

datablock TacticalZoneData(XaNotcMisEth5TerritoryZone)
{
   className = "TerritoryZone"; // don't mess with this
   category = "Tactical Zones"; // for the mission editor
   tickPeriodMS = 200; // don't mess with this
   colorChangeTimeMS = 400;
   terrainMaterial = "xa_notc_mis_eth5_territoryzone_terrainmat";
   borderMaterial = "xa_notc_mis_eth5_territoryzone_bordermat";
   otherMaterial = "xa_notc_mis_eth5_territoryzone_othermat";
   isTerritoryZone = true;
};
