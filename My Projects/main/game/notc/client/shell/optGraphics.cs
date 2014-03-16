// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function OptGraphicsGui::onWake(%this)
{
   //echo("OptGraphicsGui::onWake()");
   
   if($InGuiEditor)
      return;

   if ( isFunction("getWebDeployment") && getWebDeployment() )
   {
      // Cannot enable full screen under web deployment
      %this-->OptGraphicsFullscreenToggle.setStateOn( false );
      %this-->OptGraphicsFullscreenToggle.setVisible( false );
   }
   else
   {
      %this-->OptGraphicsFullscreenToggle.setStateOn( Canvas.isFullScreen() );
   }
   %this-->OptGraphicsVSyncToggle.setStateOn( !$pref::Video::disableVerticalSync );

   OptGraphicsGui.initResMenu();
   %resSelId = OptionsDlg-->OptGraphicsResolutionMenu.findText( _makePrettyResString( $pref::Video::mode ) );
   if( %resSelId != -1 )
      OptionsDlg-->OptGraphicsResolutionMenu.setSelected( %resSelId );

   OptGraphicsDriverMenu.clear();
   
   %buffer = getDisplayDeviceList();
   %count = getFieldCount( %buffer );
   for(%i = 0; %i < %count; %i++)
      OptGraphicsDriverMenu.add(getField(%buffer, %i), %i);

   %selId = OptGraphicsDriverMenu.findText( getDisplayDeviceInformation() );
	if ( %selId == -1 )
		OptGraphicsDriverMenu.setFirstSelected();
   else
	   OptGraphicsDriverMenu.setSelected( %selId );
    
   // Setup the graphics quality dropdown menus.
   %this-->OptMeshQualityPopup.init( MeshQualityGroup );
   %this-->OptTextureQualityPopup.init( TextureQualityGroup );
   %this-->OptLightingQualityPopup.init( LightingQualityGroup );
   %this-->OptShaderQualityPopup.init( ShaderQualityGroup );

   // Setup the anisotropic filtering menu.
   %ansioCtrl = %this-->OptAnisotropicPopup;
   %ansioCtrl.clear();
   %ansioCtrl.add( "Off", 0 );
   %ansioCtrl.add( "4X", 4 );
   %ansioCtrl.add( "8X", 8 );
   %ansioCtrl.add( "16X", 16 );
   %ansioCtrl.setSelected( $pref::Video::defaultAnisotropy, false );

   // set up the Refresh Rate menu.
   %refreshMenu = %this-->OptRefreshSelectMenu;
   %refreshMenu.clear();
   // %refreshMenu.add("Auto", 60);
   %refreshMenu.add("60", 60);
   %refreshMenu.add("75", 75);
   %refreshMenu.setSelected( getWord( $pref::Video::mode, $WORD::REFRESH ) );
   
   // Populate the Anti-aliasing popup.
   %aaMenu = %this-->OptAAQualityPopup;
   %aaMenu.clear();
   %aaMenu.Add( "Off", 0 );
   %aaMenu.Add( "1x", 1 );
   %aaMenu.Add( "2x", 2 );
   %aaMenu.Add( "4x", 4 );
   %aaMenu.setSelected( getWord( $pref::Video::mode, $WORD::AA ) );
}

function OptGraphicsGui::initResMenu(%this)
{
   // Clear out previous values
   %resMenu = %this-->OptGraphicsResolutionMenu;
   %resMenu.clear();

   // If we are in a browser then we can't change our resolution through
   // the options dialog
   if (getWebDeployment())
   {
      %count = 0;
      %currRes = getWords(Canvas.getVideoMode(), $WORD::RES_X, $WORD::RES_Y);
      %resMenu.add(%currRes, %count);
      %count++;

      return;
   }

   // Loop through all and add all valid resolutions
   %count = 0;
   %resCount = Canvas.getModeCount();
   for (%i = 0; %i < %resCount; %i++)
   {
      %testResString = Canvas.getMode( %i );
      %testRes = _makePrettyResString( %testResString );

      // Only add to list if it isn't there already.
      if (%resMenu.findText(%testRes) == -1)
      {
         %resMenu.add(%testRes, %i);
         %count++;
      }
   }

   %resMenu.sort();
}

function OptGraphicsGui::_autoDetectQuality( %this )
{
   %msg = GraphicsQualityAutodetect();
   %this.onWake();

   if ( %msg !$= "" )
   {
      MessageBoxOK( "Notice", %msg );
   }
}

function OptGraphicsGui::_updateApplyState(%this)
{
   %applyCtrl = %this-->Apply;
   assert( isObject( %applyCtrl ) );
   %applyCtrl.active = %this.applyGraphics( true );
}

function OptGraphicsGui::applyGraphics( %this, %testNeedApply )
{
	%newAdapter    = OptGraphicsDriverMenu.getText();
	%numAdapters   = GFXInit::getAdapterCount();
	%newDevice     = $pref::Video::displayDevice;

	for( %i = 0; %i < %numAdapters; %i ++ )
	   if( GFXInit::getAdapterName( %i ) $= %newAdapter )
	   {
	      %newDevice = GFXInit::getAdapterType( %i );
	      break;
	   }

   // Change the device.
   if ( %newDevice !$= $pref::Video::displayDevice )
   {
      if ( %testNeedApply )
         return true;

      $pref::Video::displayDevice = %newDevice;
      if( %newAdapter !$= getDisplayDeviceInformation() )
         MessageBoxOK( "Change requires restart", "Please restart the game for a display device change to take effect." );
   }

   // Gather the new video mode.
   if ( isFunction("getWebDeployment") && getWebDeployment() )
   {
      // Under web deployment, we use the custom resolution rather than a Canvas
      // defined one.
      %newRes = %this-->OptGraphicsResolutionMenu.getText();
   }
   else
   {
	   %newRes = getWords( Canvas.getMode( %this-->OptGraphicsResolutionMenu.getSelected() ), $WORD::RES_X, $WORD::RES_Y );
   }
	%newBpp        = 32; // ... its not 1997 anymore.
	%newFullScreen = %this-->OptGraphicsFullscreenToggle.getValue() ? "true" : "false";
	%newRefresh    = %this-->OptRefreshSelectMenu.getSelected();
	%newVsync = !%this-->OptGraphicsVSyncToggle.getValue();
	%newFSAA = %this-->OptAAQualityPopup.getSelected();

   // Under web deployment we can't be full screen.
   if ( isFunction("getWebDeployment") && getWebDeployment() )
   {
      %newFullScreen = false;
   }
   else if ( %newFullScreen $= "false" )
	{
      // If we're in windowed mode switch the fullscreen check
      // if the resolution is bigger than the desktop.
      %deskRes    = getDesktopResolution();
      %deskResX   = getWord(%deskRes, $WORD::RES_X);
      %deskResY   = getWord(%deskRes, $WORD::RES_Y);
	   if (  getWord( %newRes, $WORD::RES_X ) > %deskResX ||
	         getWord( %newRes, $WORD::RES_Y ) > %deskResY )
      {
         %newFullScreen = "true";
         %this-->OptGraphicsFullscreenToggle.setStateOn( true );
      }
	}

   // Build the final mode string.
	%newMode = %newRes SPC %newFullScreen SPC %newBpp SPC %newRefresh SPC %newFSAA;

   // Change the video mode.
   if (  %newMode !$= $pref::Video::mode ||
         %newVsync != $pref::Video::disableVerticalSync )
   {
      if ( %testNeedApply )
         return true;

      $pref::Video::mode = %newMode;
      $pref::Video::disableVerticalSync = %newVsync;
      configureCanvas();
   }

   // Test and apply the graphics settings.
   if ( %this-->OptMeshQualityPopup.apply( MeshQualityGroup, %testNeedApply ) ) return true;
   if ( %this-->OptTextureQualityPopup.apply( TextureQualityGroup, %testNeedApply ) ) return true;
   if ( %this-->OptLightingQualityPopup.apply( LightingQualityGroup, %testNeedApply ) ) return true;
   if ( %this-->OptShaderQualityPopup.apply( ShaderQualityGroup, %testNeedApply ) ) return true;

   // Check the anisotropic filtering.
   %level = %this-->OptAnisotropicPopup.getSelected();
   if ( %level != $pref::Video::defaultAnisotropy )
   {
      if ( %testNeedApply )
         return true;

      $pref::Video::defaultAnisotropy = %level;
   }

   // If we're applying the state then recheck the
   // state to update the apply button.
   if ( !%testNeedApply )
      %this._updateApplyState();

   return false;
}

/// Returns true if the current quality settings equal
/// this graphics quality level.
function GraphicsQualityLevel::isCurrent( %this )
{
   // Test each pref to see if the current value
   // equals our stored value.

   for ( %i=0; %i < %this.count(); %i++ )
   {
      %pref = %this.getKey( %i );
      %value = %this.getValue( %i );

      if ( getVariable( %pref ) !$= %value )
         return false;
   }

   return true;
}

/// Applies the graphics quality settings and calls
/// 'onApply' on itself or its parent group if its
/// been overloaded.
function GraphicsQualityLevel::apply( %this )
{
   for ( %i=0; %i < %this.count(); %i++ )
   {
      %pref = %this.getKey( %i );
      %value = %this.getValue( %i );
      setVariable( %pref, %value );
   }

   // If we have an overloaded onApply method then
   // call it now to finalize the changes.
   if ( %this.isMethod( "onApply" ) )
      %this.onApply();
   else
   {
      %group = %this.getGroup();
      if ( isObject( %group ) && %group.isMethod( "onApply" ) )
         %group.onApply( %this );
   }
}

function GraphicsQualityPopup::init( %this, %qualityGroup )
{
   assert( isObject( %this ) );
   assert( isObject( %qualityGroup ) );

   // Clear the existing content first.
   %this.clear();

   // Fill it.
   %select = -1;
   for ( %i=0; %i < %qualityGroup.getCount(); %i++ )
   {
      %level = %qualityGroup.getObject( %i );
      if ( %level.isCurrent() )
         %select = %i;

      %this.add( %level.getInternalName(), %i );
   }

   // Setup a default selection.
   if ( %select == -1 )
      %this.setText( "Custom" );
   else
      %this.setSelected( %select );
}

function GraphicsQualityPopup::apply( %this, %qualityGroup, %testNeedApply )
{
   assert( isObject( %this ) );
   assert( isObject( %qualityGroup ) );

   %quality = %this.getText();

   %index = %this.findText( %quality );
   if ( %index == -1 )
      return false;

   %level = %qualityGroup.getObject( %index );
   if ( isObject( %level ) && !%level.isCurrent() )
   {
      if ( %testNeedApply )
         return true;

      %level.apply();
   }

   return false;
}

function OptGraphicsDriverMenu::onSelect( %this, %id, %text )
{
	// Attempt to keep the same resolution settings:
	%resMenu = OptGraphicsGui-->OptGraphicsResolutionMenu;
   %currRes = %resMenu.getText();

   // If its empty the use the current.
   if ( %currRes $= "" )
      %currRes = _makePrettyResString( Canvas.getVideoMode() );

	// Fill the resolution list.
	OptGraphicsGui.initResMenu();

	// Try to select the previous settings:
	%selId = %resMenu.findText( %currRes );
	if ( %selId == -1 )
	   %selId = 0;
   %resMenu.setSelected( %selId );

	OptGraphicsGui._updateApplyState();
}

function _makePrettyResString( %resString )
{
   %width = getWord( %resString, $WORD::RES_X );
   %height = getWord( %resString, $WORD::RES_Y );

   %aspect = %width / %height;
   %aspect = mRound( %aspect * 100 ) * 0.01;

   switch$( %aspect )
   {
      case "1.33":
         %aspect = "4:3";
      case "1.78":
         %aspect = "16:9";
      default:
         %aspect = "";
   }

   %outRes = %width @ " x " @ %height;
   if ( %aspect !$= "" )
      %outRes = %outRes @ "  (" @ %aspect @ ")";

   return %outRes;
}

