// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
function XaNotcLoadingGui::onAdd(%this)
{
   %this.qLineCount = 0;
}

//------------------------------------------------------------------------------
function XaNotcLoadingGui::onWake(%this)
{
   // Play sound...
   //CloseMessagePopup();
}

//------------------------------------------------------------------------------
function XaNotcLoadingGui::onSleep(%this)
{
   // Clear the load info:
   if ( %this.qLineCount !$= "" )
   {
      for ( %line = 0; %line < %this.qLineCount; %line++ )
         %this.qLine[%line] = "";
   }      
   %this.qLineCount = 0;

   XaNotcLoadingGui-->LoadingProgress.setValue( 0 );
   XaNotcLoadingGui-->LoadingText.setValue( "WAITING FOR SERVER" );

   // Stop sound...
}
