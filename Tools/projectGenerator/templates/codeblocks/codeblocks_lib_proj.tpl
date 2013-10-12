<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<!-- Lib Project Template: codeblocks_lib_proj.tpl -->
<CodeBlocks_project_file>
	<FileVersion major="1" minor="6" />
	<Project>
		<Option title="{$projName}" />
		<Option pch_mode="2" />
		<Option compiler="gcc" />
		<Build>
			<Target title="Debug">
				<Option output="{$libDir}compiled/debug.cb/{$projName}_DEBUG.lib" prefix_auto="1"  extension_auto="1" />
				<Option object_output="{$projectOffset}../Link/cb.Debug/" />
				<Option type="2" /> <!-- Static Library -->
				<Option compiler="gcc" />
				<Compiler>
					<Add option="-g" />
					{include file="codeblocks/codeblocks_add_defines.tpl" projDefines=$projDefines isDebug=1}
				</Compiler>
				<Linker>
					<!-- <Add nameLib" /> -->
					{foreach item=dep from=$projLibsDebug}
					<Add library="{$dep}" />
					{/foreach}
				</Linker>
			</Target>
			<Target title="Release">
				<Option output="{$libDir}compiled/release.cb/{$projName}.lib" prefix_auto="1"  extension_auto="1" />
				<Option object_output="{$projectOffset}../Link/cb.Release/" />
				<Option type="2" /> <!-- Static Library -->
				<Option compiler="gcc" />
				<Compiler>
					<Add option="-O3" />
					{include file="codeblocks/codeblocks_add_defines.tpl" projDefines=$projDefines isDebug=0}
				</Compiler>
				<Linker>
					<Add option="-s" />
					<!-- <Add nameLib" /> -->
					{foreach item=dep from=$projLibs}
					<Add library="{$dep}" />
					{/foreach}
				</Linker>
			</Target>
		</Build>
		<Compiler>
			<Add option="-Wall" />
			<Add option="-Wundef" />
			<Add option="-m32 -msse -pipe -Wfatal-errors" />
			{foreach item=def from=$projIncludes}<Add directory="{$def}" />;
			{/foreach}
		</Compiler>
		<Linker>
			<Add directory="..\..\..\..\..\Engine\lib\compiled\debug.cb\" />;			
		</Linker>
		<!-- <Unit filename="../../../../../Engine/lib/tinyxml/tinystr.cpp" /> -->
		{assign var="dirWalk" value=$fileArray}
		{include file="codeblocks/codeblocks_fileRecurse.tpl" dirWalk=$dirWalk depth=1 dirPath=$projOutput->base_dir}		
		<Extensions>
			<code_completion />
			<envvars />
			<debugger />
			<lib_finder disable_auto="1" />
		</Extensions>
	</Project>
</CodeBlocks_project_file>
