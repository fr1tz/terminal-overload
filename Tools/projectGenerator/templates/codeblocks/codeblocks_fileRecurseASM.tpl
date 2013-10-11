{*                                   *}
{*      Is this a dir or an item?    *}
{*                                   *}
{if is_array($dirWalk)}
   {*                                   *}
   {*      Iterate over children        *}
   {*                                   *}
   {foreach from=$dirWalk item=dir key=key}{include file="codeblocks/codeblocks_fileRecurseASM.tpl" dirWalk=$dir dirName=$key dirPath="$dirPath$dirName/" depth=$depth+1}{/foreach}
{else}
   {*                                   *}
   {*      Output an item               *}
   {*                                   *}
   {* we don't compile some files. *}
   {capture assign="itemOut"}
   {if !dontCompile($dirWalk->path, $projOutput)}
      {if substr($dirWalk->path, -4, 4) == ".asm"}
		<Add before="mkdir -p ../../Link/cb.{$build}/{$dirWalk->offsetPath}/" />
         <Add before="nasm -f elf {$dirWalk->path} -o ../../Link/cb.{$build}/{$dirWalk->offsetPath}/{$dirWalk->filename}.o" />
      {/if}
   {/if}
   {/capture}
   {$itemOut|indent:$depth:"\t"}
{/if}
