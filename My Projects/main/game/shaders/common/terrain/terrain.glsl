// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


float calcBlend( float texId, vec2 layerCoord, float layerSize, vec4 layerSample )
{
   // This is here to disable the blend if none of 
   // the neighbors equal the current id.
   //
   // We depend on the input layer samples being 
   // rounded to the correct integer ids.
   //
   vec4 diff = clamp( abs( layerSample - texId ), 0.0, 1.0 );
   float noBlend = float(any( bvec4(1 - diff) ));

   // Use step to see if any of the layer samples 
   // match the current texture id.
   vec4 factors = step( texId, layerSample );

   // This is a custom bilinear filter.

   vec2 uv = layerCoord * layerSize;
   vec2 xy = floor( uv );
   vec2 ratio = uv - xy;
   vec2 opposite = 1 - ratio;

   float blend = ( factors.b * opposite.x + factors.g * ratio.x ) * opposite.y +
                 ( factors.r * opposite.x + factors.a * ratio.x ) * ratio.y;

   return noBlend * blend;
}
