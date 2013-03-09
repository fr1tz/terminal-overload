//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "platform/platform.h"
#include "shaderGen/shaderGen.h"

#include "shaderGen/shaderComp.h"
#include "shaderGen/featureMgr.h"


const char* ShaderGenComponentFactory::typeToString( GFXDeclType type )
{
    switch ( type )
    {
    default:
    case GFXDeclType_Float:
        return "float";

    case GFXDeclType_Float2:
        return "float2";

    case GFXDeclType_Float3:
        return "float3";

    case GFXDeclType_Float4:
    case GFXDeclType_Color:
        return "float4";
    }
}

ShaderComponent* ShaderGenComponentFactory::createVertexInputConnector( const GFXVertexFormat &vertexFormat )
{
    ShaderConnector *vertComp = new ShaderConnector;
    vertComp->setName( "VertData" );

    // Loop thru the vertex format elements.
    for ( U32 i=0; i < vertexFormat.getElementCount(); i++ )
    {
        const GFXVertexElement &element = vertexFormat.getElement( i );

        Var *var = NULL;

        if ( element.isSemantic( GFXSemantic::POSITION ) )
        {
            var = vertComp->getElement( RT_POSITION );
            var->setName( "position" );
        }
        else if ( element.isSemantic( GFXSemantic::NORMAL ) )
        {
            var = vertComp->getElement( RT_NORMAL );
            var->setName( "normal" );
        }
        else if ( element.isSemantic( GFXSemantic::TANGENT ) )
        {
            var = vertComp->getElement( RT_TANGENT );
            var->setName( "T" );
        }
        else if ( element.isSemantic( GFXSemantic::TANGENTW ) )
        {
            var = vertComp->getIndexedElement( element.getSemanticIndex(), RT_TEXCOORD );
            var->setName( "tangentW" );
        }
        else if ( element.isSemantic( GFXSemantic::BINORMAL ) )
        {
            var = vertComp->getElement( RT_BINORMAL );
            var->setName( "B" );
        }
        else if ( element.isSemantic( GFXSemantic::COLOR ) )
        {
            var = vertComp->getElement( RT_COLOR );
            var->setName( "diffuse" );
        }
        else if ( element.isSemantic( GFXSemantic::TEXCOORD ) )
        {
            var = vertComp->getIndexedElement( element.getSemanticIndex(), RT_TEXCOORD );
            if ( element.getSemanticIndex() == 0 )
                var->setName( "texCoord" );
            else
                var->setName( String::ToString( "texCoord%d", element.getSemanticIndex() + 1 ) );
        }
        else
        {
            // Everything else is a texcoord!
            var = vertComp->getIndexedElement( element.getSemanticIndex(), RT_TEXCOORD );
            var->setName( "tc" + element.getSemantic() );
        }

        if ( !var )
            continue;

        var->setStructName( "IN" );
        var->setType( typeToString( element.getType() ) );
    }

    return vertComp;
}

ShaderComponent* ShaderGenComponentFactory::createVertexPixelConnector()
{
    ShaderComponent* comp = new ShaderConnector;
    ((ShaderConnector*)comp)->setName("ConnectData");
    return comp;
}

ShaderComponent* ShaderGenComponentFactory::createVertexParamsDef()
{
    ShaderComponent* comp = new VertexParamsDef;
    return comp;
}

ShaderComponent* ShaderGenComponentFactory::createPixelParamsDef()
{
    ShaderComponent* comp = new PixelParamsDef;
    return comp;
}