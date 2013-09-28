<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<!-- Shared Lib Project Template: codeblocks_dll_proj.tpl -->
<CodeBlocks_project_file>
	<FileVersion major="1" minor="6" />
	<Project>
		<Option title="{$projName}" />
		<Option pch_mode="2" />
		<Option compiler="gcc" />
		<Build>
			<Target title="Debug">
				<Option output="{$projectOffset}../../{$gameFolder}/{$projOutName}_DEBUG.dll" prefix_auto="0"  extension_auto="1" />
				<Option object_output="{$projectOffset}../Link/cb.Debug/" />
				<Option type="3" /> <!-- DLL Library -->
				<Option compiler="gcc" />
				<Compiler>
					<Add option="-g" />
					{include file="codeblocks/codeblocks_add_defines.tpl" projDefines=$projDefines isDebug=1}
				</Compiler>
				<Linker>
					<!-- <Add nameLib" /> -->
					{foreach item=dep from=$projLibsDebug}
					<Add library= "{$dep}" />
					{/foreach}
					{foreach item=dep from=$projDepend}
					<Add library="{$projectDepends[$dep]->outputName}_DEBUG" />
					{/foreach}
				</Linker>
			</Target>
			<Target title="Release">
				<Option output="{$projectOffset}../../{$gameFolder}/{$projOutName}.dll" prefix_auto="0"  extension_auto="1" />
				<Option object_output="{$projectOffset}../Link/cb.Release/" />
				<Option type="3" /> <!-- DLL Library -->
				<Option compiler="gcc" />
				<Compiler>
					<Add option="-O2" />
					{include file="codeblocks/codeblocks_add_defines.tpl" projDefines=$projDefines isDebug=0}
				</Compiler>
				<Linker>
					<Add option="-s" />
					<!-- <Add nameLib" /> -->
					{foreach item=dep from=$projLibs}
					<Add library="{$dep}" />
					{/foreach}
					{foreach item=dep from=$projDepend}
					<Add library="{$projectDepends[$dep]->outputName}_DEBUG" />
					{/foreach}
				</Linker>
			</Target>
		</Build>
		<Compiler>
			<Add option="-Wall" />
			<Add option="-Wundef" />
			<Add option="-m32 -msse" />
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
		<ExtraCommands>
			{assign var="dirWalk" value=$fileArray}
			{include file="codeblocks/codeblocks_fileRecurseASM.tpl" dirWalk=$dirWalk depth=1 dirPath=$projOutput->base_dir}
		</ExtraCommands>
	</Project>
</CodeBlocks_project_file>
