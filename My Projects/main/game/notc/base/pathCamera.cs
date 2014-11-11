// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function PathCamera::onNode(%obj, %node)
{
   //echo("PathCamera::onNode()");
   //echo("node:" SPC %node);
   %obj.getDataBlock().onNode(%obj, %node);
}

