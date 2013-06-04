// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function ForestBrushTool::onActivated( %this )
{
   ForestEditToolbar.setVisible( true );
   %this.syncBrushToolbar();
}

function ForestBrushTool::onDeactivated( %this )
{
   ForestEditToolbar.setVisible( false );
}

function ForestBrushTool::syncBrushToolbar( %this )
{
   %size = %this.size;
   ForestBrushSizeSliderCtrlContainer->slider.setValue( %size );
   ForestBrushSizeTextEditContainer-->textEdit.setValue( %size );
      
   %pres = %this.pressure;   
   ForestBrushPressureSliderCtrlContainer->slider.setValue( %pres );
   ForestBrushPressureTextEditContainer-->textEdit.setValue( mCeil(100 * %pres) @ "%" );
   
   %hard = %this.hardness;
   ForestBrushHardnessSliderCtrlContainer->slider.setValue( %hard );
   ForestBrushHardnessTextEditContainer-->textEdit.setValue( mCeil(100 * %hard) @ "%"); 
}

function ForestBrushTool::onMouseDown( %this )
{
   ForestEditTabBook.selectPage( 0 );
}

function ForestSelectionTool::onActivated( %this )
{
}

function ForestSelectionTool::onDeactivated( %this )
{
   %this.clearSelection();
}