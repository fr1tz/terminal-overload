{*                                   *}
{*      Is this a dir or an item?    *}
{*                                   *}
{if is_array($dirWalk)}
   {*                                   *}
   {*      Iterate over children        *}
   {*                                   *}
   {foreach from=$dirWalk item=dir key=key}{include file="codeblocks/codeblocks_fileRecurse.tpl" dirWalk=$dir dirName=$key dirPath="$dirPath$dirName/" depth=$depth+1}{/foreach}   
{else}
   {*                                   *}
   {*      Output an item               *}
   {*                                   *}
   {* we don't compile some files. *}
{capture assign="itemOut"}
{if !dontCompile($dirWalk->path, $projOutput)} 
   {* {else} *}
   <Unit filename="{$dirWalk->path|replace:'//':'/'|replace:'/':'\\'}" />
{/if}
{/capture}
{$itemOut|indent:$depth:"\t"}
{/if}