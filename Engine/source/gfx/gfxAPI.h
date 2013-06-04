// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXAPI_H_
#define _GFXAPI_H_

#ifndef _ENGINEAPI_H_
   #include "console/engineAPI.h"
#endif
#ifndef _GFXSTRUCTS_H_
   #include "gfx/gfxStructs.h"
#endif
#ifndef _GFXENUMS_H_
   #include "gfx/gfxEnums.h"
#endif


DECLARE_SCOPE( GFXAPI );

DefineEnumType( GFXBlend );
DefineEnumType( GFXCmpFunc );
DefineEnumType( GFXTextureAddressMode );
DefineEnumType( GFXFormat );
DefineEnumType( GFXTextureTransformFlags );
DefineEnumType( GFXTextureFilterType );
DefineEnumType( GFXTextureOp );
DefineEnumType( GFXTextureArgument );
DefineEnumType( GFXCullMode );
DefineEnumType( GFXStencilOp );
DefineEnumType( GFXBlendOp );
DefineEnumType( GFXAdapterType );

DECLARE_STRUCT( GFXVideoMode );

DefineConsoleType( TypeGFXAdapterType, GFXAdapterType );
DefineConsoleType( TypeGFXBlend, GFXBlend );
DefineConsoleType( TypeGFXCmpFunc, GFXCmpFunc );
DefineConsoleType( TypeGFXTextureAddressMode, GFXTextureAddressMode );
DefineConsoleType( TypeGFXFormat, GFXFormat );
DefineConsoleType( TypeGFXTextureTransformFlags, GFXTextureTransformFlags );
DefineConsoleType( TypeGFXTextureFilterType, GFXTextureFilterType );
DefineConsoleType( TypeGFXTextureOp, GFXTextureOp );
DefineConsoleType( TypeGFXTextureArgument, GFXTextureArgument );
DefineConsoleType( TypeGFXCullMode, GFXCullMode );
DefineConsoleType( TypeGFXStencilOp, GFXStencilOp );
DefineConsoleType( TypeGFXBlendOp, GFXBlendOp );

#endif // !_GFXAPI_H_
