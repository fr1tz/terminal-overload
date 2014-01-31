// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// See metaSoil.txt for documentation

function MetaSoil::setRenderEnabled(%render)
{
	for(%idx =MissionMetaSoilTiles.getCount()-1; %idx >= 0; %idx-- )
	{
		%tile = MissionMetaSoilTiles.getObject(%idx);
      %tile.isRenderEnabled = %render;
   }
}

