// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
in vec4 vPosition;
in vec2 vTexCoord0;

uniform mat4 modelview;
uniform vec3 cameraPos, ambient;
uniform vec2 fadeStartEnd;

out vec4 color;
out vec2 texCoord;

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
void main()
{
   gl_Position = modelview * vPosition;
   texCoord = vTexCoord0.st;
   color = vec4( ambient.r, ambient.g, ambient.b, 1.0 );

   // Do we need to do a distance fade?
   if ( fadeStartEnd.x < fadeStartEnd.y )
   {

      float distance = length( cameraPos - vPosition.xyz );
      color.a = abs( clamp( ( distance - fadeStartEnd.x ) / ( fadeStartEnd.y - fadeStartEnd.x ), 0.0, 1.0 ) - 1.0 );
   }
   gl_Position.y *= -1;
}

