// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

varying vec2 texCoord;
varying vec4 color;
varying float fade;

uniform sampler2D inputTex;
uniform vec4 ambient;
            
            
void main()
{   
	float shadow = texture2D( inputTex, texCoord ).a * color.a;           
    gl_FragColor = ( ambient * shadow ) + ( 1 - shadow );
}
