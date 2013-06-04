// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

$GuiEditor::defaultGridSize = 8;
$GuiEditor::minGridSize = 3;

//-----------------------------------------------------------------------------------------
// Buttons
//-----------------------------------------------------------------------------------------

function GuiEditorPrefsDlgOkBtn::onAction(%this)
{
   GuiEditor.snap2gridsize = GuiEditorPrefsDlgGridEdit.getValue();
   if( GuiEditor.snap2grid )
      GuiEditor.setSnapToGrid( GuiEditor.snap2gridsize );
      
   Canvas.popDialog( GuiEditorPrefsDlg );
}

function GuiEditorPrefsDlgCancelBtn::onAction(%this)
{
   Canvas.popDialog( GuiEditorPrefsDlg );
}

function GuiEditorPrefsDlgDefaultsBtn::onAction(%this)
{
   GuiEditorPrefsDlgGridSlider.setValue( $GuiEditor::defaultGridSize );
}

//-----------------------------------------------------------------------------------------
// Grid
//-----------------------------------------------------------------------------------------

function GuiEditorPrefsDlgGridEdit::onWake(%this)
{
   %this.setValue( GuiEditor.snap2gridsize );
}

function GuiEditorPrefsDlgGridEdit::onAction( %this )
{
   %value = %this.getValue();
   if( %value < $GuiEditor::minGridSize )
   {
         %value = $GuiEditor::minGridSize;
         %this.setValue( %value );
   }
   
   GuiEditorPrefsDlgGridSlider.setValue( %value );
}

function GuiEditorPrefsDlgGridSlider::onWake(%this)
{
   %this.setValue( GuiEditor.snap2gridsize );
}

function GuiEditorPrefsDlgGridSlider::onAction(%this)
{
   %value = %this.value;
   if( %value < $GuiEditor::minGridSize )
   {
      %value = $GuiEditor::minGridSize;
      %this.setValue( %value );
   }
      
   GuiEditorPrefsDlgGridEdit.setvalue( mCeil( %value ) );
}
