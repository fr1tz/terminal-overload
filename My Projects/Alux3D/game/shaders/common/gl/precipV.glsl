// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform mat4 modelview;
uniform vec3 cameraPos, ambient;
uniform vec2 fadeStartEnd;

varying vec4 color;
varying vec2 texCoord;

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
void main()
{
   gl_Position = modelview * gl_Vertex;
   texCoord = gl_MultiTexCoord0.st;
   color = vec4( ambient.r, ambient.g, ambient.b, 1.0 );

   // Do we need to do a distance fade?
   if ( fadeStartEnd.x < fadeStartEnd.y )
   {

      float distance = length( cameraPos - gl_Vertex.xyz );
      color.a = abs( clamp( ( distance - fadeStartEnd.x ) / ( fadeStartEnd.y - fadeStartEnd.x ), 0.0, 1.0 ) - 1.0 );
   }
}

