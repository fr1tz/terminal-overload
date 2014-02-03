{foreach item=def from=$projDefines}<Add option="-D{$def}" />;
{/foreach}
					<Add option="-DUNICODE" />;
					<Add option="-D_CRT_SECURE_NO_DEPRECATE" />;
					<Add option="-D_CRT_SECURE_NO_WARNINGS" />;

{if $isDebug eq 1}
					<Add option="-DTORQUE_DEBUG" />;
					<Add option="-DTORQUE_DEBUG_GUARD" />;
					<Add option="-DD3D_DEBUG_INFO" />;
					<Add option="-DTORQUE_NET_STATS" />;
{/if}

