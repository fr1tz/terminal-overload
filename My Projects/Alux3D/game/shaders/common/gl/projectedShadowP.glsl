// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

varying vec2 texCoord;
varying vec4 color;
varying float fade;

uniform sampler2D inputTex;
uniform vec4 ambient;
            
            
void main()
{   
   vec3 LUMINANCE_VECTOR  = vec3(0.2125f, 0.4154f, 0.1721f);
   float esmFactor = 200.0;
   
   float lum = dot( ambient.rgb, LUMINANCE_VECTOR );   

   gl_FragColor.rgb = ambient.rgb * lum; 
   gl_FragColor.a = 0.0;
   float depth = texture2D(inputTex, texCoord).a;
   
   depth = depth * exp(depth - 10.0);
   depth = exp(esmFactor * depth) - 1.0;
   
   gl_FragColor.a = clamp(depth * 300.0, 0.0, 1.0) * (1.0 - lum) * fade * color.a;
}
