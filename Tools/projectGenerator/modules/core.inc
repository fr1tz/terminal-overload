<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

addEngineSrcDir('sfx/media');
addEngineSrcDir('sfx/null');
addEngineSrcDir('sfx');


// Components
addEngineSrcDir('component');
addEngineSrcDir('component/interfaces');

// Core
if (TorqueGenerator::isApp())
	addSrcDir( '../source' );
    
addEngineSrcDir('console');
addEngineSrcDir('core');
addEngineSrcDir('core/stream');
addEngineSrcDir('core/strings');
addEngineSrcDir('core/util');
addEngineSrcDir('core/util/test');
addEngineSrcDir('core/util/journal');
addEngineSrcDir('core/util/journal/test');
addEngineSrcDir('core/util/zip');
addEngineSrcDir('core/util/zip/unitTests');
addEngineSrcDir('core/util/zip/compressors');
addEngineSrcDir('i18n');
addEngineSrcDir('sim');
addEngineSrcDir('unit/tests');
addEngineSrcDir('unit');
addEngineSrcDir('util');
addEngineSrcDir('windowManager');
addEngineSrcDir('windowManager/torque');
addEngineSrcDir('windowManager/test');
addEngineSrcDir('math');
addEngineSrcDir('math/util');
addEngineSrcDir('math/test');
addEngineSrcDir('platform');
addEngineSrcDir('cinterface');

switch( TorqueGenerator::$platform )
{
   case "win32":
   case "mac":
   case "linux":
     addEngineSrcDir('platform/nativeDialogs');
     addEngineSrcDir('platform/menus');
     addEngineSrcDir('platform/test');
     break;
}

addEngineSrcDir('platform/threads');
addEngineSrcDir('platform/async');
addEngineSrcDir('platform/input');
addEngineSrcDir('platform/output');
addEngineSrcDir('app');
addEngineSrcDir('app/net');

// Moved this here temporarily because PopupMenu uses on it and is currently in core
addEngineSrcDir('util/messaging');

switch( TorqueGenerator::$platform )
{
   case "win32":
     addEngineSrcDir('platformWin32');
     addEngineSrcDir('platformWin32/nativeDialogs');
     addEngineSrcDir('platformWin32/menus');
     addEngineSrcDir('platformWin32/threads');
     addEngineSrcDir('platformWin32/videoInfo');
     addEngineSrcDir('platformWin32/minidump');
     addEngineSrcDir('windowManager/win32');
     
     break;

   case "mac":
     addEngineSrcDir('platformMac');
     addEngineSrcDir('platformMac/menus');
     addEngineSrcDir('platformPOSIX');
     addEngineSrcDir('windowManager/mac');
     break;

   case "360":
     addEngineSrcDir('platformXbox');
     addEngineSrcDir('platformXbox/threads');
     addEngineSrcDir('windowManager/360');
     break;
     
   case "ps3":
     addEngineSrcDir('platformPS3');
     addEngineSrcDir('platformPS3/threads');
     addEngineSrcDir('windowManager/ps3');
     break;

   case "linux_dedicated":
     addEngineSrcDir('windowManager/dedicated');
     addEngineSrcDir('platformX86UNIX');
     addEngineSrcDir('platformX86UNIX/threads');
     addEngineSrcDir('platformPOSIX');
     break;

   case "linux":
     addEngineSrcDir('platformX86UNIX');
     addEngineSrcDir('platformX86UNIX/threads');
     //addEngineSrcDir('platformX86UNIX/nativeDialogs');
     //addEngineSrcDir('platformX86UNIX/menus');
     addEngineSrcFile('platformX86UNIX/nativeDialogs/x11MsgBox.cpp');
     addEngineSrcDir('platformPortable/menus');
     addEngineSrcFile('platformPortable/nativeDialogs/portableFileDialog.cpp');
     addEngineSrcDir('platformPOSIX');
     addEngineSrcDir('windowManager/x11');
     break;
}

// GFX
addEngineSrcDir( 'gfx/Null' );
addEngineSrcDir( 'gfx/test' );
addEngineSrcDir( 'gfx/bitmap' );
addEngineSrcDir( 'gfx/bitmap/loaders' );
addEngineSrcDir( 'gfx/util' );
addEngineSrcDir( 'gfx/video' );
addEngineSrcDir( 'gfx' );
addEngineSrcDir( 'shaderGen' );

switch( TorqueGenerator::$platform )
{
   case "win32":
      //addEngineSrcDir( 'gfx/D3D8' );
      addEngineSrcDir( 'gfx/D3D' );
      addEngineSrcDir( 'gfx/D3D9' );
      addEngineSrcDir( 'gfx/D3D9/pc' );
      addEngineSrcDir( 'shaderGen/HLSL' );
	  
	  // GFX - GGL
	  addProjectDefines( 'TORQUE_OPENGL' );
     addProjectDefines( 'GLEW_STATIC' );
     addLibSrcFile( 'glew/src/glew.c' );
     addIncludePath( getAppLibSrcDir() . 'glew/include' );
     addEngineSrcDir( 'gfx/gl' );
     addEngineSrcDir( 'gfx/gl/win32' );
     addEngineSrcDir( 'gfx/gl/tGL' );
     addEngineSrcDir( 'shaderGen/GLSL' );
      break;
   case "360":
      addEngineSrcDir( 'gfx/D3D9' );
      addEngineSrcDir( 'gfx/D3D9/360' );
      addEngineSrcDir( 'shaderGen/HLSL' );
      addEngineSrcDir( 'shaderGen/360' );
      break;
   case "mac":
      // GFX - GGL
      addProjectDefines( 'TORQUE_OPENGL' );
      addLibSrcFile( 'glew/src/glew.c' );
      addIncludePath( getAppLibSrcDir() . 'glew/include' );
      addEngineSrcDir( 'gfx/gl' );
      addEngineSrcDir( 'gfx/gl/tGL' );
      addEngineSrcDir( 'shaderGen/GLSL' );
      break;
   case "linux":
   case "linux_dedicated":
      // GFX - GGL
	   addProjectDefines( 'TORQUE_OPENGL' );
      addLibSrcFile( 'glew/src/glew.c' );
      addIncludePath( getAppLibSrcDir() . 'glew/include' );
      addEngineSrcDir( 'gfx/gl' );
      addEngineSrcDir( 'gfx/gl/x11' );
      addEngineSrcDir( 'gfx/gl/tGL' );
      addEngineSrcDir( 'shaderGen/GLSL' );
      break;
   case "ps3":
      // GFX - GGL
      addProjectDefines( 'TORQUE_OPENGL' );
      addEngineSrcDir( 'gfx/gl' );
      addEngineSrcDir( 'gfx/gl/tGL' );
      addEngineSrcDir( 'shaderGen/GLSL' );
      break;
}

// GFX - Sim dependent 
addEngineSrcDir( 'gfx/sim');

// GUI
addEngineSrcDir('gui/buttons');
addEngineSrcDir('gui/containers');
addEngineSrcDir('gui/controls');

addEngineSrcDir('gui/core');
addEngineSrcDir('gui/game');
addEngineSrcDir('gui/shiny');
addEngineSrcDir('gui/utility');
addEngineSrcDir('gui');

// Include tools for non-tool builds (or define player if a tool build)
includeModule( 'tools' );

/////////////////////
// Additional includes
addIncludePath( '../../source' );		   // product source (relative to solution output directories)
addIncludePath( getAppEngineSrcDir() );	// main engine source dir relative to app project file 
addIncludePath( getAppLibSrcDir() ); 	   // main lib source dir relative to app project file

if ( TorqueGenerator::$platform == "win32" )
{
}

switch( TorqueGenerator::$platform )
{
   case "win32":
   addIncludePath( getAppLibSrcDir() . 'directx8' );
   addIncludePath( getAppLibSrcDir() . 'openal/win32' );
   
   addProjectLibDir( getAppLibSrcDir() . 'SDL/win32' );
   addProjectLibDir( getAppLibSrcDir() . 'unicode' );
   addProjectLibDir( getAppLibSrcDir() . 'directx8' );
      
      addProjectLibInput("Opengl32.lib");
      break;
   case "linux":
      addIncludePath( '/usr/include/freetype2' );
      break;
}

?>
