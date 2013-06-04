<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

class SafariWebPlugin
{
   var $FOLDER = "";
   var $GAMEFOLDER = "";
   var $PLUGINNAME = "";
   var $MIMETYPE = "";
   var $DESCRIPTION = "";
   var $IDENTIFIER = "";
   var $BUNDLE = "";
   var $VERSION = "";
   
   function SafariWebPlugin()
   {
      $rootPhpBuildDir = getcwd();

      $this->FOLDER = $rootPhpBuildDir."/web/source/npplugin/mac/";
      $this->GAMEFOLDER = $rootPhpBuildDir."/game/";
      
      $this->PLUGINNAME = WebDeploymentOSX::$safariPluginName;
      $this->MIMETYPE = WebDeploymentOSX::$mimeType;
      
      $this->VERSION = WebDeploymentOSX::$version;

      $this->DESCRIPTION = WebDeploymentOSX::$description." ".$this->VERSION ;      

      $this->BUNDLE = WebDeploymentOSX::$safariPluginName;
      $this->IDENTIFIER = WebDeploymentOSX::$identifier;
   }
   
   function process($project)
   {
      
      $this->processTemplates();
      

   }
   
   function readTemplate($filename)
   {
      $filename = realpath( dirname( $_SERVER[ 'PHP_SELF' ] ) ). "/templates/web/".$filename;
      $fh = fopen($filename, 'r');
      $data = fread($fh, filesize($filename));
      fclose($fh);
      return $data;
   }
   
   function writeFile($filename, $data)
   {
      $filename = $this->FOLDER . $filename;

      echo($filename);
      
      $fh = fopen($filename, 'w');
      fwrite($fh, $data);
      fclose($fh);
   }

   function writeGameFile($filename, $data)
   {
      $filename = $this->GAMEFOLDER . $filename;
      $fh = fopen($filename, 'w');
      fwrite($fh, $data);
      fclose($fh);
   }

   function processTemplates()
   {

      $data =  $this->readTemplate("safari_Info_plist.tpl");
      $data = str_replace("__CFBundleExecutable__", $this->BUNDLE, $data);
      $data = str_replace("__CFBundleIdentifier__", $this->IDENTIFIER, $data);
      $data = str_replace("__WebPluginDescription__", $this->DESCRIPTION, $data);
      $data = str_replace("__WebPluginMIMEType__", "application/".$this->MIMETYPE, $data);
      $data = str_replace("__WebPluginName__", $this->PLUGINNAME, $data);      

      $data = str_replace("__GameName__", getGameProjectName(), $data);

      //TODO: handled by Toolbox
      $data = str_replace("__GameInstallPath__", $this->GAMEFOLDER, $data);

      $this->writeFile('Info.plist', $data);
      
      WebPlugin::processNPPlugin($this);
   }
   
}

?>
