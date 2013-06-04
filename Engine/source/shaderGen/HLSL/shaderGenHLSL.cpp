// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "shaderGen/HLSL/shaderGenHLSL.h"

#include "shaderGen/HLSL/shaderCompHLSL.h"
#include "shaderGen/featureMgr.h"


void ShaderGenPrinterHLSL::printShaderHeader(Stream& stream)
{
   const char *header1 = "//*****************************************************************************\r\n";
   const char *header2 = "// Torque -- HLSL procedural shader\r\n";

   stream.write( dStrlen(header1), header1 );
   stream.write( dStrlen(header2), header2 );
   stream.write( dStrlen(header1), header1 );

   const char* header3 = "\r\n";      
   stream.write( dStrlen(header3), header3 );
}

void ShaderGenPrinterHLSL::printMainComment(Stream& stream)
{
   const char * header5 = "// Main\r\n";
   const char * line    = "//-----------------------------------------------------------------------------\r\n";

   stream.write( dStrlen(line), line );
   stream.write( dStrlen(header5), header5 );
   stream.write( dStrlen(line), line );
}

void ShaderGenPrinterHLSL::printVertexShaderCloser(Stream& stream)
{
   const char *closer = "   return OUT;\r\n}\r\n";
   stream.write( dStrlen(closer), closer );
}

void ShaderGenPrinterHLSL::printPixelShaderOutputStruct(Stream& stream, const MaterialFeatureData &featureData)
{
   // Determine the number of output targets we need
   U32 numMRTs = 0;
   for( U32 i = 0; i < FEATUREMGR->getFeatureCount(); i++ )
   {
      const FeatureInfo &info = FEATUREMGR->getAt( i );
      if( featureData.features.hasFeature( *info.type ) )
         numMRTs |= info.feature->getOutputTargets( featureData );
   }

   WRITESTR( "struct Fragout\r\n" );
   WRITESTR( "{\r\n" );
   WRITESTR( "   float4 col : COLOR0;\r\n" );
   for( U32 i = 1; i < 4; i++ )
   {
      if( numMRTs & 1 << i )
         WRITESTR( avar( "   float4 col%d : COLOR%d;\r\n", i, i ) );
   }
   WRITESTR( "};\r\n" );
   WRITESTR( "\r\n" );
   WRITESTR( "\r\n" );
}

void ShaderGenPrinterHLSL::printPixelShaderCloser(Stream& stream)
{
   WRITESTR( "\r\n   return OUT;\r\n}\r\n" );
}

void ShaderGenPrinterHLSL::printLine(Stream& stream, const String& line)
{
   stream.write(line.length(), line.c_str());
   const char* end = "\r\n";
   stream.write(dStrlen(end), end);
}

const char* ShaderGenComponentFactoryHLSL::typeToString( GFXDeclType type )
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

ShaderComponent* ShaderGenComponentFactoryHLSL::createVertexInputConnector( const GFXVertexFormat &vertexFormat )
{
   ShaderConnectorHLSL *vertComp = new ShaderConnectorHLSL;
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

ShaderComponent* ShaderGenComponentFactoryHLSL::createVertexPixelConnector()
{
   ShaderComponent* comp = new ShaderConnectorHLSL;
   ((ShaderConnector*)comp)->setName("ConnectData");
   return comp;
}

ShaderComponent* ShaderGenComponentFactoryHLSL::createVertexParamsDef()
{
   ShaderComponent* comp = new VertexParamsDefHLSL;
   return comp;
}

ShaderComponent* ShaderGenComponentFactoryHLSL::createPixelParamsDef()
{
   ShaderComponent* comp = new PixelParamsDefHLSL;
   return comp;
}
