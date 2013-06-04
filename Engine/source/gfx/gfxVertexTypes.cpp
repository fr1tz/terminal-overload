// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gfx/gfxVertexTypes.h"


GFXImplementVertexFormat( GFXVertexP )
{
   addElement( "POSITION", GFXDeclType_Float3 );
}

GFXImplementVertexFormat( GFXVertexPT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
}

GFXImplementVertexFormat( GFXVertexPTT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 1 );
}

GFXImplementVertexFormat( GFXVertexPTTT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 1 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 2 );
}

GFXImplementVertexFormat( GFXVertexPC )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "COLOR", GFXDeclType_Color );
}

GFXImplementVertexFormat( GFXVertexPCN )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "NORMAL", GFXDeclType_Float3 );
   addElement( "COLOR", GFXDeclType_Color );
}

GFXImplementVertexFormat( GFXVertexPCT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "COLOR", GFXDeclType_Color );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
}

GFXImplementVertexFormat( GFXVertexPCTT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "COLOR", GFXDeclType_Color );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 1 );
}

GFXImplementVertexFormat( GFXVertexPN )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "NORMAL", GFXDeclType_Float3 );
}

GFXImplementVertexFormat( GFXVertexPNT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "NORMAL", GFXDeclType_Float3 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
}

GFXImplementVertexFormat( GFXVertexPNTT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "NORMAL", GFXDeclType_Float3 );
   addElement( "TANGENT", GFXDeclType_Float3 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
}

GFXImplementVertexFormat( GFXVertexPNTBT )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "NORMAL", GFXDeclType_Float3 );
   addElement( "TANGENT", GFXDeclType_Float3 );
   addElement( "BINORMAL", GFXDeclType_Float3 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
}

GFXImplementVertexFormat( GFXVertexPNTTB )
{
   addElement( "POSITION", GFXDeclType_Float3 );
   addElement( "NORMAL", GFXDeclType_Float3 );
   addElement( "TANGENT", GFXDeclType_Float3 );
   addElement( "BINORMAL", GFXDeclType_Float3 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 0 );
   addElement( "TEXCOORD", GFXDeclType_Float2, 1 );
}
