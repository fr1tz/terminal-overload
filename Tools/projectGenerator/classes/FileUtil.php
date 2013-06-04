<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

class FileUtil
{
	// Turn foo/../bar/../baz/ into baz/
	static function collapsePath( $p )
	{
	    $p = explode( '/', $p );
	    $o = array();
	    
	    for( $i = 0; $i < sizeof( $p ); $i++ )
	    {
	        // Skip meaningless . or empty terms.
	        if( $p[ $i ] == '' || $p[ $i ] == '.' )
	           continue;
	
	        // Consider if we can pop something off the list.
	        if( $p[ $i ] == '..' && $i > 0 && $o[ sizeof( $o ) - 1 ] != '..' )
	        {
	            array_pop( $o );
	            
	            continue;
	        }
	        
	        array_push( $o, $p[ $i ] );
	    }
	    
	    return implode( '/', $o );
	}
	
	// We apply some cleanup to the file list, specifically to remove
	// any groupings with no siblings.
	static function trimFileList( &$list )
	{
	   // Consider each child...
	   foreach( $list as $k => $v )
	   {
	      // Only consider folders...
	      if( !is_array( $v ) )
	         continue;
	
	      // If child has only one child, then collapse it
	      reset( $v );
	      
	      if( count( $v ) == 1 && is_array( current( $v ) ) ) 
	      {
	         //echo("Trying to collapse $k\n");
	         
	         $list[ $k ] = current( $v );
	
	         // Reset our walk through the list...
	         reset( $list );
	      }
	   }
	
	   // Now recurse on all children.
	   foreach( $list as $k => $v )
	   {
	      // Only consider folders...
	      if( !is_array( $v ) )
	         continue;
	
	      FileUtil::trimFileList( $list[ $k ] );
	   }
	}
	
	static function prepareOutputDir( $outdir )
	{
		if( !file_exists( $outdir ) ) 
		{
			echo( " Directory " . $outdir . " doesn't exist, attempting to create it.\n" );
	
			if( !mkdir_r( $outdir, 0777 ) ) 
			{
				echo( " Couldn't create directory.\n" );
	
				return false;
			}
		}
	
		if( !chdir( $outdir ) ) 
		{
			echo( "Couldn't change directory\n" );
	
			return false;;
		}
		
		return true;
	}

   static function normalizeSlashes( $path )
   {
      return str_replace( '\\', '/', $path );
   }
   
   static function isAbsolutePath( $path )
   {
      // This looks complex, but its really fairly simple.
      //
      // We're detecting existing absolute paths in the include
      // by converting it to absolute, normalizing the slashes,
      // and comparing the results.
      //
      // If we get an absolute path we just don't prepend the
      // project relative path part.
      //
      $orgPath = FileUtil::normalizeSlashes( $path );
      $absPath = FileUtil::normalizeSlashes( realpath( $path ) );
      return strcasecmp( $orgPath, $absPath ) == 0;
   }
}
?>
