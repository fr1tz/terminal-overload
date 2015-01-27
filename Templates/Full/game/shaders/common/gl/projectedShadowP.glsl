// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

in vec2 texCoord;
in vec4 color;
in float fade;

out vec4 OUT_col;

uniform sampler2D inputTex;
uniform vec4 ambient;
            
            
void main()
{   
	float shadow = texture( inputTex, texCoord ).a * color.a;           
    OUT_col = ( ambient * shadow ) + ( 1 - shadow );
}
