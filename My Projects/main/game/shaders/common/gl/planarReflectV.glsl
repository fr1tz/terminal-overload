// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
in vec4 vPosition;
in vec2 vTexCoord0;

uniform mat4 modelview;

out vec2 TEX0;
out vec4 TEX1;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   mat4 texGenTest  = mat4(0.5, 0.0, 0.0, 0.0,
                           0.0, -0.5, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0,
                           0.5, 0.5, 0.0, 1.0);
                          
   gl_Position = modelview * vPosition;
   
   TEX0 = vTexCoord0;
   
   TEX1 = texGenTest * gl_Position;
   TEX1.y = -TEX1.y;

}
