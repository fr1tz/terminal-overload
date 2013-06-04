// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// RSS Feed integration structures
// I apologize in advance if this RSS reader is too restrictive with regard
// to tags/enclosures. I may revisit it at some point to add support

//------------------------------------------------------------------------------
// RSS Headline Item
//------------------------------------------------------------------------------
function constructRSSHeadline( %headline, %link )
{
   %ret = new ScriptObject()
   {
      class = "RSSHeadline";
      _headline = %headline;
      _link = %link;
   };
   
   return %ret;
}

function RSSHeadline::getHeadline( %this )
{
   return %this._headline;
}

function RSSHeadline::getLink( %this )
{
   return %this._link;
}

function RSSHeadline::sameAs( %this, %headline )
{
   return ( strcmp( %this.toString(), %headline.toString() ) == 0 );
}

function RSSHeadline::toString( %this )
{
   return %this.getHeadline() @ " ( " @ %this.getLink() @ " ) ";
}

//------------------------------------------------------------------------------

function constructRSSHeadlineCollection()
{
   %ret = new ScriptObject()
   {
      class = "RSSHeadlineCollection";
   };
   
   // Create sim group for it
   %ret._simGroup = new SimGroup();
   
   return %ret;
}

function RSSHeadlineCollection::getObject( %this, %index )
{
   %ret = %this._simGroup.getObject( %index );
   
   if( !isObject( %ret ) )
   {
      warn( "No such index in headline collection." );
      return -1;
   }
   
   return %ret;
}

function RSSHeadlineCollection::getCount( %this )
{
   return %this._simGroup.getCount();
}

function RSSHeadlineCollection::addHeadline( %this, %headline, %skipReorder )
{
   for( %i = 0; %i < %this.getCount(); %i++ )
   {
      %obj = %this.getObject( %i );
         
      if( %obj.sameAs( %headline ) )
      {
         //echo( "cache hit headline: " @ %headline.toString() );
         return false;
      }
   }
   
   %this._simGroup.add( %headline );
   
   if( !%skipReorder )
      %this._simGroup.bringToFront( %headline );
      
   //echo( "adding headline: " @ %headline.toString() );

   return true;
}

function RSSHeadlineCollection::writeToFile( %this, %file )
{
   $rssHeadlineCollection::count = %this.getCount();
   
   for( %i = 0; %i < %this.getCount(); %i++ )
   {
      %hdl = %this.getObject( %i );
      $rssHeadlineCollection::headline[%i] = %hdl.getHeadline();
      $rssHeadlineCollection::link[%i] = %hdl.getLink();
   }
   
   export( "$rssHeadlineCollection::*", %file, false );
}

function RSSHeadlineCollection::loadFromFile( %this, %file )
{
   %this._simGroup.clear();
   
   $rssHeadlineCollection::count = 0;
   
   %file = getPrefsPath(%file);
   if (isFile(%file) || isFile(%file @ ".dso"))
      exec( %file );

   for( %i = 0; %i < $rssHeadlineCollection::count; %i++ )
   {
      //echo( "[LD: " @ %i @ "] Headline: " @ $rssHeadlineCollection::headline[%i] );
      //echo( "[LD: " @ %i @ "] Link: " @ $rssHeadlineCollection::link[%i] );
      
      %hdl = constructRSSHeadline( $rssHeadlineCollection::headline[%i],
                                   $rssHeadlineCollection::link[%i] );
                                   
      // This does negate the cache check, but that is ok -pw                             
      %this.addHeadline( %hdl, true );
   }
}
