<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//
//	Solution info container
//
class Solution
{
	public $name;
	public $guid;
	public $project_refs = array();
    public $project_extRefs = array();
	public $outputs		 = array();
	
	public function Solution( $name, $guid, $outputs = null )
	{
	    $this->name = $name;
	    $this->guid = $guid;
	    
	  	$this->setOutputs( $outputs );
	}
	
	public function addProjectRef( $pname )
	{
	    array_push( $this->project_refs, $pname );
	}
    
    public function addSolutionProjectRefExt( $pname, $ppath, $pguid )
    {
        $v = array();
        $v[0] = $ppath;
        $v[1] = $pguid;
        // This is the project GUID for a C# project
        // TODO: Add support for C++ projects if need to add them
        // as an external project, to date this hasn't been necessary
        $v[2] = "{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}";
        $this->project_extRefs[$pname] = $v;
    }
	
	public function setOutputs( $outputs )
	{
	    if( isset( $outputs ) )
	    	$this->outputs = array_merge( $this->outputs, $outputs );
	}
	
	public function generate( $tpl, $platform, $root_dir )
	{
		// Project container for templates
		$projects = array();
        $refs = array();
        
        // make sure that startup project is the first in the solution
        
        if (getGameProjectName())
            array_push( $refs, getGameProjectName() );
        
        foreach( $this->project_refs as $pname )
        {
            if (getGameProjectName() && $pname == getGameProjectName())
                continue;
               
            array_push( $refs, $pname );
        }

		// Look up each project ref and add its info to the list
		foreach( $refs as $pname ) 
		{
			$project = TorqueGenerator::lookupProjectByName( $pname );
	
			if( isset( $project ) )
			{
				echo( "      - project ref: " . $pname . " = " . $project->guid . "\n" );    
			
				array_push( $projects, $project );
                
        // Let the project update any dependencies
        $project->validateDependencies(); 												
			}
			else
				trigger_error( "Solution::generate() - project ref not found: " . $pname . "\n", E_USER_ERROR );
		}
		
		// No use going forward if there were no projects for this solution is there?
		// (Would we ever want to generate an empty solution at all?)
		if( count( $projects ) == 0 )
		{
		    echo( "Solution::generate() - no project refs found for solution: " . $this->name . "\n" );
		    
		    continue;
		}
		
		// 
		//sort( $projects );
		
		// Set smarty params that dont change during loop once here
		$tpl->assign_by_ref( "solution_guid",	$this->guid );
		$tpl->assign_by_ref( "projects", 		$projects );
        $tpl->assign_by_ref( "projectExtRefs",  $this->project_extRefs );
		
		// Generate a solution file for all outputs for this solution
		foreach( $this->outputs as $output )
		{
         // Supported platform?
         if( !$output->supportsPlatform( $platform ) )
         {
             //echo( "      # Skipping output: '$outputName'.\n" );

             continue;
         }
      
		    // Reset to base dir
		    chdir( $root_dir );
		    
		    // Then offset
		    if( !FileUtil::prepareOutputDir( $output->output_dir ) || !$output->template_sln )
				continue;
		    
			$outfile = $this->name . $output->solution_ext;			    
		
			echo( "   - Writing solution file: " . $output->output_dir . "/" . $outfile );    
		
			// Project filenames are <projectname>.<outputext> where ext is set per output.
			// The template builds each project output using the project name and this ext. 			
			$tpl->assign_by_ref( "project_ext", $output->output_ext );
					
			if( $f = fopen( $outfile, 'w' ) ) 
			{					
				fputs( $f, $tpl->fetch( $output->template_sln ) );

				fclose( $f );
				
				echo( " - success " . "\n" );
			} 
			else
				trigger_error( "\nCould not write output file: " . $outfile, E_USER_ERROR );
		}
	}
}
?>
