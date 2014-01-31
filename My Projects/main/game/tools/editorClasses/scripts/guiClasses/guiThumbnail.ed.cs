// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// This file merely contains the base functionality for creating your own
// 'subclassed' script namkespaces that define the visual appearance of 
// a thumbnail for a guiThumnailPopup list.
//
// All border creation and callback click functionality is also defined in
// this file and may be overriden in your namespaces provided that you 
// properly invoke the Parent::onMethodName( %parameterList ) to all this
// base namespace to do it's dependent processing.

//function GuiDefaultThumbnail::onAdd( %this )
//{
   //// Nothing Here.
//}
//
//function GuiDefaultThumbnail::onRemove( %this )
//{
   //// Nothing Here.
//}

//-----------------------------------------------------------------------------
// Object Browser Item Default Behaviors
//-----------------------------------------------------------------------------
function GuiDefaultThumbnail::onClick( %this )
{
   // Store data and hide the dialog.
   if( isObject( %this.base ) )
   {
      %this.base.item = %this;
      %this.base.Hide();
   }
}

function GuiDefaultThumbnail::onRightClick( %this )
{
   // Nothing Here.   
}

function GuiDefaultThumbnail::onMouseLeave( %this )
{
   // Nothing Here.
}

function ObjectBrowserItem::onMouseEnter( %this )
{
   // Nothing Here.
}

function GuiDefaultThumbnail::onDoubleClick( %this )
{
   // By Default if the base funcitonality is called
   // in onClick, we will never get here.  However, if
   // you want to override this functionality, simply 
   // override onClick and don't call the parent.
}
