// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(TP_BadgerDae)
{
   baseShape = "./TP_Badger.DAE";
   forceUpdateMaterials = "0";
   loadLights = "0";
   lodType = "TrailingNumber";
};

function TP_BadgerDae::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "root", "0", "0", "1", "0");
   %this.addSequence("timeline", "fire", "0", "0", "1", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.addSequence("timeline", "fire_vis", "9", "19", "1", "0");
   %this.setSequenceCyclic("fire_vis", "0");
}
