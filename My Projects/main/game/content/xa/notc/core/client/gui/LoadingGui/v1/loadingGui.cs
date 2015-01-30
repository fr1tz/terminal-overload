// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
function XaNotcLoadingGui::onAdd(%this)
{

}

//------------------------------------------------------------------------------
function XaNotcLoadingGui::onWake(%this)
{

}

//------------------------------------------------------------------------------
function XaNotcLoadingGui::onSleep(%this)
{
   XaNotcLoadingGui-->LoadingProgress.setValue( 0 );
   XaNotcLoadingGui-->LoadingText.setValue( "WAITING FOR SERVER" );
}
