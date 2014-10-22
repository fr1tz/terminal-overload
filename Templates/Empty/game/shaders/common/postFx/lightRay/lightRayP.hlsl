// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../postFx.hlsl"

uniform sampler2D frameSampler : register( s0 );
uniform sampler2D backBuffer : register( s1 );

uniform float3 camForward;
uniform float3 lightDirection;
uniform float2 screenSunPos;
uniform float2 oneOverTargetSize;
uniform int numSamples;
uniform float density;
uniform float weight;
uniform float decay;
uniform float exposure;

float4 main( PFXVertToPix IN ) : COLOR0  
{  
    float4 texCoord = float4( IN.uv0.xy, 0, 0 );        
    
    // Store initial sample.
    half3 color = (half3)tex2D( frameSampler, texCoord.xy ).rgb;  
	
	// Store original bb color.
	float4 bbCol = tex2D( backBuffer, IN.uv1 );

    // Set up illumination decay factor.
    half illuminationDecay = 1.0;  		
	
	float amount = saturate( dot( -lightDirection, camForward ) );
		
	int samples = numSamples * amount;
	
	if ( samples <= 0 )
	   return bbCol;	

	// Calculate vector from pixel to light source in screen space.
    half2 deltaTexCoord = (half2)( texCoord.xy - screenSunPos );  

    // Divide by number of samples and scale by control factor.  
    deltaTexCoord *= (half)(1.0 / samples * density); 
	
    // Evaluate summation from Equation 3 NUM_SAMPLES iterations.  
    for ( int i = 0; i < samples; i++ )  
    {  
        // Step sample location along ray.
        texCoord.xy -= deltaTexCoord;  

        // Retrieve sample at new location.
        half3 sample = (half3)tex2Dlod( frameSampler, texCoord );  

        // Apply sample attenuation scale/decay factors.
        sample *= half(illuminationDecay * weight);

        // Accumulate combined color.
        color += sample;

        // Update exponential decay factor.
        illuminationDecay *= half(decay);
    }       
   
    //return saturate( amount ) * color * Exposure;
	//return bbCol * decay;
	
    // Output final color with a further scale control factor.      
    return saturate( amount ) * float4( color * exposure, 1 ) + bbCol;
}  
