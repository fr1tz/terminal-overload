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

#include "shaderGen/featureMgr.h"

void ShaderGenPrinter::printShaderHeader(Stream& stream)
{
    const char *header1 = "//*****************************************************************************\r\n";
    const char *header2 = "// Torque -- procedural shader\r\n";

    stream.write( dStrlen(header1), header1 );
    stream.write( dStrlen(header2), header2 );
    stream.write( dStrlen(header1), header1 );

    const char* header3 = "\r\n";      
    stream.write( dStrlen(header3), header3 );
}

void ShaderGenPrinter::printMainComment(Stream& stream)
{
    const char * header5 = "// Main\r\n";
    const char * line    = "//-----------------------------------------------------------------------------\r\n";

    stream.write( dStrlen(line), line );
    stream.write( dStrlen(header5), header5 );
    stream.write( dStrlen(line), line );
}

void ShaderGenPrinter::printVertexShaderCloser(Stream& stream)
{
    const char *closer = "   return OUT;\r\n}\r\n";
    stream.write( dStrlen(closer), closer );
}

void ShaderGenPrinter::printPixelShaderOutputStruct(Stream& stream, const MaterialFeatureData &featureData)
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

void ShaderGenPrinter::printPixelShaderCloser(Stream& stream)
{
    WRITESTR( "\r\n   return OUT;\r\n}\r\n" );
}

void ShaderGenPrinter::printLine(Stream& stream, const String& line)
{
    stream.write(line.length(), line.c_str());
    const char* end = "\r\n";
    stream.write(dStrlen(end), end);
}