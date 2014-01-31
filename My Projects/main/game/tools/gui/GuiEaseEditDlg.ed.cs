// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.



//---------------------------------------------------------------------------------------------

function GetEaseF( %currentEase, %callback, %root )
{
   GuiEaseEditDlg.init( %currentEase, %callback );
   
   if( !isObject( %root ) )
      %root = Canvas;
   
   %root.pushDialog( GuiEaseEditDlg );
}

//=============================================================================================
//    GuiEaseEditDlg
//=============================================================================================

//---------------------------------------------------------------------------------------------

function GuiEaseEditDlg::init( %this, %ease, %callback )
{
   // Initialize direction popup.
   
   %directionList = %this-->directionList;
   if( !%directionList.size() )
   {
      %directionList.add( "InOut", $Ease::InOut );
      %directionList.add( "In", $Ease::In );
      %directionList.add( "Out", $Ease::Out );
   }
   
   // Initialize type popup.
   
   %typeList = %this-->typeList;
   if( !%typeList.size() )
   {
      %typeList.add( "Linear", $Ease::Linear );
      %typeList.add( "Quadratic", $Ease::Quadratic );
      %typeList.add( "Cubic", $Ease::Cubic );
      %typeList.add( "Quartic", $Ease::Quartic );
      %typeList.add( "Quintic", $Ease::Quintic );
      %typeList.add( "Sinusoidal", $Ease::Sinusoidal );
      %typeList.add( "Exponential", $Ease::Exponential );
      %typeList.add( "Circular", $Ease::Circular );
      %typeList.add( "Elastic", $Ease::Elastic );
      %typeList.add( "Back", $Ease::Back );
      %typeList.add( "Bounce", $Ease::Bounce );
   }
   
   // Set the initial easing curve.
   
   %this.oldEase = %ease;
   %this.setEase( %ease );
   
   // Remember callback.
   
   %this.callback = %callback;
}

//---------------------------------------------------------------------------------------------

function GuiEaseEditDlg::setEase( %this, %ease )
{
   %this-->easeView.ease = %ease;
   %this-->directionList.setSelected( getWord( %ease, 0 ), false );
   %this-->typeList.setSelected( getWord( %ease, 1 ), false );
   %this-->param1Value.setValue( getWord( %ease, 2 ) );
   %this-->param2Value.setValue( getWord( %ease, 3 ) );
   
   %this.onEaseTypeSet();
}

//---------------------------------------------------------------------------------------------

function GuiEaseEditDlg::onEaseTypeSet( %this )
{
   switch( %this-->typeList.getSelected() )
   {
      case $Ease::Elastic:
         %this-->param1Value.setActive( true );
         %this-->param2Value.setActive( true );
         
      case $Ease::Back:
         %this-->param1Value.setActive( true );
         %this-->param2Value.setActive( false );
         
      default:
         %this-->param1Value.setActive( false );
         %this-->param2Value.setActive( false );
   }
}

//---------------------------------------------------------------------------------------------

function GuiEaseEditDlg::onOK( %this )
{
   eval( %this.callback @ "( \"" @ %this-->easeView.ease @ "\" );" );
   %this.getRoot().popDialog( %this );
}

//---------------------------------------------------------------------------------------------

function GuiEaseEditDlg::onCancel( %this )
{
   %this.getRoot().popDialog( %this );
}

//---------------------------------------------------------------------------------------------

function GuiEaseEditDlg::onSetParam1( %this, %value )
{
   %easeView = %this-->easeView;
   
   %ease = %easeView.ease;
   %ease = setWord( %ease, 2, %value );
   %easeView.ease = %ease;
}

//---------------------------------------------------------------------------------------------

function GuiEaseEditDlg::onSetParam2( %this, %value )
{
   %easeView = %this-->easeView;
   
   %ease = %easeView.ease;
   %ease = setWord( %ease, 3, %value );
   %easeView.ease = %ease;
}

//=============================================================================================
//    GuiEaseEditDirectionList
//=============================================================================================

//---------------------------------------------------------------------------------------------

function GuiEaseEditDirectionList::onSelect( %this, %id, %text )
{
   %easeView = GuiEaseEditDlg-->easeView;
   
   %ease = %easeView.ease;
   %ease = setWord( %ease, 0, %id );
   %easeview.ease = %ease;
}

//=============================================================================================
//    GuiEaseEditTypeList
//=============================================================================================

//---------------------------------------------------------------------------------------------

function GuiEaseEditTypeList::onSelect( %this, %id, %text )
{
   %easeView = GuiEaseEditDlg-->easeView;
   
   %ease = %easeView.ease;
   %ease = setWord( %ease, 1, %id );
   %easeview.ease = %ease;
   
   GuiEaseEditDlg.onEaseTypeSet();
}
