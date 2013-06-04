// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


// Used to name the saved files.
$PostFXManager::fileExtension = ".postfxpreset.cs";

// The filter string for file open/save dialogs.
$PostFXManager::fileFilter = "Post Effect Presets|*.postfxpreset.cs";

// Enable / disable PostFX when loading presets or just apply the settings?
$PostFXManager::forceEnableFromPresets = true;

//Load a preset file from the disk, and apply the settings to the
//controls. If bApplySettings is true - the actual values in the engine
//will be changed to reflect the settings from the file.
function PostFXManager::loadPresetFile()
{
   //Show the dialog and set the flag
   getLoadFilename($PostFXManager::fileFilter, "PostFXManager::loadPresetHandler");
}

function PostFXManager::loadPresetHandler( %filename )
{
   //Check the validity of the file
   if ( isScriptFile( %filename ) )
   {
      %filename = expandFilename(%filename);
      postVerbose("% - PostFX Manager - Executing " @ %filename);
      exec(%filename);

      PostFXManager.settingsApplyFromPreset();      
   }
}

//Save a preset file to the specified file. The extension used
//is specified by $PostFXManager::fileExtension for on the fly
//name changes to the extension used. 

function PostFXManager::savePresetFile(%this)
{
   %defaultFile = filePath($Client::MissionFile) @ "/" @ fileBase($Client::MissionFile);
   getSaveFilename($PostFXManager::fileFilter, "PostFXManager::savePresetHandler", %defaultFile);
}

//Called from the PostFXManager::savePresetFile() function
function PostFXManager::savePresetHandler( %filename )
{
   %filename = makeRelativePath( %filename, getMainDotCsDir() );
   if(strStr(%filename, ".") == -1)
      %filename = %filename @ $PostFXManager::fileExtension;
               
   //Apply the current settings to the preset
   PostFXManager.settingsApplyAll();
   
   export("$PostFXManager::Settings::*", %filename, false);

   postVerbose("% - PostFX Manager - Save complete. Preset saved at : " @ %filename);
}

