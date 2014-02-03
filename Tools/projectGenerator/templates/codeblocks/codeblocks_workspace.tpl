<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<CodeBlocks_workspace_file>
	<Workspace title="Workspace">
		<!-- <Project filename="projects/projectName.cbp" />  -->		
{foreach name=projects item=project from=$projects}
		<Project filename="projects/{$project->name}{$project_ext}" >
{foreach item=dep from=$project->dependencies}
{foreach item=projectDep from=$projects}
{if $projectDep->guid eq $dep}
			<Depends filename="projects/{$projectDep->name}.cbp" />
{/if}
{/foreach}
{/foreach}
		</Project>
{/foreach}
	</Workspace>
</CodeBlocks_workspace_file>
