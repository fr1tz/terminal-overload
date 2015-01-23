// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Note: The server executes this file.

datablock TacticalZoneData(XaNotcEth3TerritoryZone)
{
   className = "TerritoryZone"; // don't mess with this
   category = "Tactical Zones"; // for the mission editor
   tickPeriodMS = 200; // don't mess with this
   colorChangeTimeMS = 400;
   terrainMaterial = "xa_notc_mis_eth3_territoryzone_terrainmat";
   borderMaterial = "xa_notc_mis_eth3_territoryzone_bordermat";
   otherMaterial = "xa_notc_mis_eth3_territoryzone_othermat";
   isTerritoryZone = true;
};

datablock LightFlareData( MissionLightFlare1 )
{
   overallScale = 2.0;
   flareEnabled = true;
   renderReflectPass = true;
   flareTexture = "content/o/torque3d/3.0/lights/lensFlareSheet1";

   elementRect[0] = "0 512 512 512";
   elementDist[0] = 0.0;
   elementScale[0] = 0.5;
   elementTint[0] = "1.0 1.0 1.0";
   elementRotate[0] = false;
   elementUseLightColor[0] = false;

   elementRect[1] = "0 0 512 512";
   elementDist[1] = 0.0;
   elementScale[1] = "0.2";
   elementTint[1] = "0.992157 0.992157 0.992157 1";
   elementRotate[1] = false;
   elementUseLightColor[1] = false;
   occlusionRadius = "0.25";
};


