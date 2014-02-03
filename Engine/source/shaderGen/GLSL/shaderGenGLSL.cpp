// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "shaderGen/GLSL/shaderGenGLSL.h"

#include "shaderGen/GLSL/shaderCompGLSL.h"


void ShaderGenPrinterGLSL::printShaderHeader( Stream& stream )
{
   const char *header1 = "//*****************************************************************************\r\n";
   const char *header2 = "// Torque -- GLSL procedural shader\r\n";

   stream.write( dStrlen(header1), header1 );
   stream.write( dStrlen(header2), header2 );
   stream.write( dStrlen(header1), header1 );

   // Cheap HLSL compatibility.
   const char* header3 = "#include \"shaders/common/gl/hlslCompat.glsl\"\r\n";      
   stream.write( dStrlen(header3), header3 );

   const char* header4 = "\r\n";      
   stream.write( dStrlen(header4), header4 );
}

void ShaderGenPrinterGLSL::printMainComment( Stream& stream )
{
   // Print out main function definition
   const char * header5 = "// Main                                                                        \r\n";
   const char * line    = "//-----------------------------------------------------------------------------\r\n";

   stream.write( dStrlen(line), line );
   stream.write( dStrlen(header5), header5 );
   stream.write( dStrlen(line), line );
}

void ShaderGenPrinterGLSL::printVertexShaderCloser( Stream& stream )
{
   const char *closer = "}\r\n";
   stream.write( dStrlen(closer), closer );
}

void ShaderGenPrinterGLSL::printPixelShaderOutputStruct( Stream& stream, const MaterialFeatureData &featureData )
{
   // Nothing here
}

void ShaderGenPrinterGLSL::printPixelShaderCloser( Stream& stream )
{
   const char *closer = "   gl_FragColor = col;\r\n}\r\n";
   stream.write( dStrlen(closer), closer );
}

void ShaderGenPrinterGLSL::printLine(Stream& stream, const String& line)
{
   stream.write(line.length(), line.c_str());
   const char* end = "\r\n";
   stream.write(dStrlen(end), end);
} 

const char* ShaderGenComponentFactoryGLSL::typeToString( GFXDeclType type )
{
   switch ( type )
   {
      default:
      case GFXDeclType_Float:
         return "float";

      case GFXDeclType_Float2:
         return "vec2";

      case GFXDeclType_Float3:
         return "vec3";

      case GFXDeclType_Float4:
      case GFXDeclType_Color:
         return "vec4";
   }
}

ShaderComponent* ShaderGenComponentFactoryGLSL::createVertexInputConnector( const GFXVertexFormat &vertexFormat )
{
   AppVertConnectorGLSL *vertComp = new AppVertConnectorGLSL;

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
         var = vertComp->getElement( RT_TANGENTW );
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
         var = vertComp->getElement( RT_TEXCOORD );
         if ( element.getSemanticIndex() == 0 )
            var->setName( "texCoord" );
         else
            var->setName( String::ToString( "texCoord%d", element.getSemanticIndex() + 1 ) );
      }
      else
      {
         // Everything else is a texcoord!
         var = vertComp->getElement( RT_TEXCOORD );
         var->setName( "tc" + element.getSemantic() );
      }

      if ( !var )
         continue;

      var->setStructName( "IN" );
      var->setType( typeToString( element.getType() ) );
   }

   return vertComp;
}

ShaderComponent* ShaderGenComponentFactoryGLSL::createVertexPixelConnector()
{
   VertPixelConnectorGLSL* comp = new VertPixelConnectorGLSL;
   return comp;
}

ShaderComponent* ShaderGenComponentFactoryGLSL::createVertexParamsDef()
{
   VertexParamsDefGLSL* comp = new VertexParamsDefGLSL;
   return comp;
}

ShaderComponent* ShaderGenComponentFactoryGLSL::createPixelParamsDef()
{
   PixelParamsDefGLSL* comp = new PixelParamsDefGLSL;
   return comp;
}

