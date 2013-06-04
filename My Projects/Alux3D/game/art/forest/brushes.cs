// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// This is the default save location for any ForestBrush(s) created in 
// the Forest Editor.
// This script is executed from ForestEditorPlugin::onWorldEditorStartup().

//--- OBJECT WRITE BEGIN ---
new SimGroup(ForestBrushGroup) {
   canSaveDynamicFields = "1";

   new ForestBrush() {
      internalName = "ExampleForestBrush";
      canSaveDynamicFields = "1";

      new ForestBrushElement() {
         internalName = "ExampleElement";
         canSaveDynamicFields = "1";
         ForestItemData = "ExampleForestMesh";
         probability = "1";
         rotationRange = "360";
         scaleMin = "1";
         scaleMax = "2";
         scaleExponent = "0.2";
         sinkMin = "0";
         sinkMax = "0.1";
         sinkRadius = "0.25";
         slopeMin = "0";
         slopeMax = "30";
         elevationMin = "-10000";
         elevationMax = "10000";
         clumpCountMin = "1";
         clumpCountMax = "1";
         clumpCountExponent = "1";
         clumpRadius = "10";
      };
   };
};
//--- OBJECT WRITE END ---
