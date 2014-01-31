// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
function LoadingGui::onAdd(%this)
{
   %this.qLineCount = 0;
}

//------------------------------------------------------------------------------
function LoadingGui::onWake(%this)
{
   // Play sound...
   //CloseMessagePopup();
}

//------------------------------------------------------------------------------
function LoadingGui::onSleep(%this)
{
   // Clear the load info:
   if ( %this.qLineCount !$= "" )
   {
      for ( %line = 0; %line < %this.qLineCount; %line++ )
         %this.qLine[%line] = "";
   }      
   %this.qLineCount = 0;

   LoadingProgress.setValue( 0 );
   LoadingProgressTxt.setValue( "WAITING FOR SERVER" );

   // Stop sound...
}
