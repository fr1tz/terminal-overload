// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


float calcBlend( float texId, float2 layerCoord, float layerSize, float4 layerSample )
{
   // This is here to disable the blend if none of 
   // the neighbors equal the current id.
   //
   // We depend on the input layer samples being 
   // rounded to the correct integer ids.
   //
   float4 diff = saturate( abs( layerSample - texId ) );
   float noBlend = any( 1 - diff );

   // Use step to see if any of the layer samples 
   // match the current texture id.
   float4 factors = step( texId, layerSample );

   // This is a custom bilinear filter.

   float2 uv = layerCoord * layerSize;
   float2 xy = floor( uv );
   float2 ratio = uv - xy;
   float2 opposite = 1 - ratio;

   // NOTE: This will optimize down to two lerp operations.
   float blend = ( factors.b * opposite.x + factors.g * ratio.x ) * opposite.y +
                 ( factors.r * opposite.x + factors.a * ratio.x ) * ratio.y;

   return noBlend * blend;
}
