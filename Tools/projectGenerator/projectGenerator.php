<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


//
// Hello, hello...
//
echo( "Welcome to projectGenerator 0.9\n" );
echo( "Copyright (c) 2012 GarageGames, LLC\n" );
echo( "Released under a MIT license.\n" );
echo( "\n" );

//
//	Configure error logging
//
error_reporting( E_ALL & ~E_NOTICE );

//
// Requires
//
require_once( "classes/BuildTarget.php" );
require_once( "btargets/targets.inc" );
require_once( "classes/Generator.php" );
require_once( "projectGenUtils.inc" );
require_once( "smarty/Smarty.class.php" );

//
// Initialization
//
$g_cwd = realpath( dirname( $_SERVER[ 'PHP_SELF' ] ) );

echo( "   CWD = " . $g_cwd . "\n" );

//
// Load, instantiate, and configure the smarty template engine.
//
echo( "   - Loading Smarty...\n" );

$tpl 				= new Smarty();
$tpl->template_dir	= $g_cwd . "/templates";
$tpl->compile_dir	= $g_cwd . "/templates_c";

$tpl->clear_all_cache();

// By default we assume that the root of the Torque SDK
// is located two folders up from the CWD.  That is unless
// another path is passed in the command line.
$torqueRoot = "../..";
if ( $argc >= 3 )
    $torqueRoot = str_replace( "\\", "/", $argv[2] );

// Kick off the generator
Generator::init( $torqueRoot );

// Ready to read our config file.
echo( "   - Loading config file " . realpath($argv[1])."\n" );

require( $argv[ 1 ] );

// Generate all projects
Generator::generateProjects( $tpl );

// Now the solutions (if any)
$tpl->clear_all_cache();

Generator::generateSolutions( $tpl );

// finally write out the sample.html for web deployment (if any)
WebPlugin::writeSampleHtml();

exit;
?>
