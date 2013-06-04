<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// settings/logic shared by plugins

class WebPlugin
{
   static $SAMPLE_HTML = "";
   static $GAME_FOLDER = "";
   
   static function readTemplate()
   {
      $filename = realpath( dirname( $_SERVER[ 'PHP_SELF' ] ) ). "/templates/web/sample_html.tpl";
      $fh = fopen($filename, 'r');
      $data = fread($fh, filesize($filename));
      fclose($fh);
      
      if (!$data)
        trigger_error( "WebPlugin::readTemplate() - cannot read HTML template!", E_USER_ERROR );
      
      self::$SAMPLE_HTML = $data;
   }
   
   static function processNPPlugin($np)
   {
   
      if (!self::$SAMPLE_HTML)
         self::readTemplate();
         
      $rootPhpBuildDir = getcwd();      
      self::$GAME_FOLDER = $rootPhpBuildDir."/game/";

      self::$SAMPLE_HTML = str_replace("__MIMETYPE__", $np->MIMETYPE, self::$SAMPLE_HTML);
      
   }

   static function processActiveXPlugin($ax)
   {
      if (!self::$SAMPLE_HTML)
        self::readTemplate();   

      $rootPhpBuildDir = getcwd();      
      self::$GAME_FOLDER = $rootPhpBuildDir."/game/";
      
      $projID = $ax->WEBGAME_PLUGINNAME.'.'.$ax->WEBGAME_CTRLNAME.'.'.'1';
      
      self::$SAMPLE_HTML = str_replace("__PROJID__", $projID, self::$SAMPLE_HTML);
      self::$SAMPLE_HTML = str_replace("__CLSID__", $ax->WEBGAMELIB_UUID, self::$SAMPLE_HTML);
      
    }
   
   static function writeSampleHtml()
   {
      // no plugins defined
      if (!self::$SAMPLE_HTML)
         return;
         
      $filename = self::$GAME_FOLDER . "web/sample.html";
      $fh = fopen($filename, 'w');
      fwrite($fh, self::$SAMPLE_HTML);
      fclose($fh);
   }
}
   
?>
