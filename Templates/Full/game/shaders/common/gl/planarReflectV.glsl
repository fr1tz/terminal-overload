// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform mat4 modelview;

varying vec2 TEX0;
varying vec4 TEX1;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   mat4 texGenTest  = mat4(0.5, 0.0, 0.0, 0.0,
                           0.0, -0.5, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.5, 0.5, 0.0, 1.0);
                          
   gl_Position = modelview * gl_Vertex;
   
   TEX0 = gl_MultiTexCoord0.st;
   
   TEX1 = texGenTest * gl_Position;
   TEX1.y = -TEX1.y;

}
