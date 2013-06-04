// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


#if defined( SOFTSHADOW ) && defined( SOFTSHADOW_HIGH_QUALITY )

#define NUM_PRE_TAPS 4
#define NUM_TAPS 12

/// The non-uniform poisson disk used in the
/// high quality shadow filtering.
static float2 sNonUniformTaps[NUM_TAPS] = 
{      
   // These first 4 taps are located around the edges
   // of the disk and are used to predict fully shadowed
   // or unshadowed areas.
   { 0.992833, 0.979309 },
   { -0.998585, 0.985853 },
   { 0.949299, -0.882562 },
   { -0.941358, -0.893924 },

   // The rest of the samples.
   { 0.545055, -0.589072 },
   { 0.346526, 0.385821 },
   { -0.260183, 0.334412 },
   { 0.248676, -0.679605 },
   { -0.569502, -0.390637 },
   { -0.614096, 0.212577 },
   { -0.259178, 0.876272 },
   { 0.649526, 0.864333 },
};

#else

#define NUM_PRE_TAPS 5

/// The non-uniform poisson disk used in the
/// high quality shadow filtering.
static float2 sNonUniformTaps[NUM_PRE_TAPS] = 
{      
   { 0.892833, 0.959309 },
   { -0.941358, -0.873924 },
   { -0.260183, 0.334412 },
   { 0.348676, -0.679605 },
   { -0.569502, -0.390637 },
};

#endif


/// The texture used to do per-pixel pseudorandom
/// rotations of the filter taps.
uniform sampler2D gTapRotationTex : register(S3);


float softShadow_sampleTaps(  sampler2D shadowMap,
                              float2 sinCos,
                              float2 shadowPos,
                              float filterRadius,
                              float distToLight,
                              float esmFactor,
                              int startTap,
                              int endTap )
{
   float shadow = 0;

   float2 tap = 0;
   for ( int t = startTap; t < endTap; t++ )
   {
      tap.x = ( sNonUniformTaps[t].x * sinCos.y - sNonUniformTaps[t].y * sinCos.x ) * filterRadius;
      tap.y = ( sNonUniformTaps[t].y * sinCos.y + sNonUniformTaps[t].x * sinCos.x ) * filterRadius;
      float occluder = tex2Dlod( shadowMap, float4( shadowPos + tap, 0, 0 ) ).r;

      float esm = saturate( exp( esmFactor * ( occluder - distToLight ) ) );
      shadow += esm / float( endTap - startTap );
   }

   return shadow;
}


float softShadow_filter(   sampler2D shadowMap,
                           float2 vpos,
                           float2 shadowPos,
                           float filterRadius,
                           float distToLight,
                           float dotNL,
                           float esmFactor )
{
   #ifndef SOFTSHADOW

      // If softshadow is undefined then we skip any complex 
      // filtering... just do a single sample ESM.

      float occluder = tex2Dlod( shadowMap, float4( shadowPos, 0, 0 ) ).r;
      float shadow = saturate( exp( esmFactor * ( occluder - distToLight ) ) );

   #else

      // Lookup the random rotation for this screen pixel.
      float2 sinCos = ( tex2Dlod( gTapRotationTex, float4( vpos * 16, 0, 0 ) ).rg - 0.5 ) * 2;

      // Do the prediction taps first.
      float shadow = softShadow_sampleTaps(  shadowMap,
                                             sinCos,
                                             shadowPos,
                                             filterRadius,
                                             distToLight,
                                             esmFactor,
                                             0,
                                             NUM_PRE_TAPS );

      // We live with only the pretap results if we don't
      // have high quality shadow filtering enabled.
      #ifdef SOFTSHADOW_HIGH_QUALITY

         // Only do the expensive filtering if we're really
         // in a partially shadowed area.
         if ( shadow * ( 1.0 - shadow ) * max( dotNL, 0 ) > 0.06 )
         {
            shadow += softShadow_sampleTaps( shadowMap,
                                             sinCos,
                                             shadowPos,
                                             filterRadius,
                                             distToLight,
                                             esmFactor,
                                             NUM_PRE_TAPS,
                                             NUM_TAPS );
                                             
            // This averages the taps above with the results
            // of the prediction samples.
            shadow *= 0.5;                              
         }

      #endif // SOFTSHADOW_HIGH_QUALITY

   #endif // SOFTSHADOW

   return shadow;
}