// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "torque.glsl"


#define IMPOSTER_MAX_UVS 64


void imposter_v(
                    // These parameters usually come from the vertex.
                    vec3 center,
                    int corner,
                    float halfSize,
                    vec3 imposterUp,
                    vec3 imposterRight,

                    // These are from the imposter shader constant.
                    int numEquatorSteps,
                    int numPolarSteps,
                    float polarAngle,
                    bool includePoles,

                    // Other shader constants.
                    vec3 camPos,
                    vec4 uvs[IMPOSTER_MAX_UVS],
                    
                    // The outputs of this function.
                    out vec3 outWsPosition,
                    out vec2 outTexCoord,
                    out mat3 outWorldToTangent
    )
{

   float M_HALFPI_F   = 1.57079632679489661923;
   float M_PI_F       = 3.14159265358979323846;
   float M_2PI_F      = 6.28318530717958647692;


   float sCornerRight[4];// = float[]( -1.0, 1.0, 1.0, -1.0 );
   sCornerRight[0] = -1.0;
   sCornerRight[1] = 1.0;
   sCornerRight[2] = 1.0;
   sCornerRight[3] = -1.0;
   float sCornerUp[4];// = float[]( -1.0, -1.0, 1.0, 1.0 );
   sCornerUp[0] = -1.0;
   sCornerUp[1] = -1.0;
   sCornerUp[2] = 1.0;
   sCornerUp[3] = 1.0;
   vec2 sUVCornerExtent[4];// = vec2[](vec2( 0.0, 1.0 ), vec2( 1.0, 1.0 ), vec2( 1.0, 0.0 ), vec2( 0.0, 0.0 ));
   sUVCornerExtent[0] = vec2( 0.0, 1.0 );
   sUVCornerExtent[1] = vec2( 1.0, 1.0 ); 
   sUVCornerExtent[2] = vec2( 1.0, 0.0 ); 
   sUVCornerExtent[3] = vec2( 0.0, 0.0 );

    // TODO: This could all be calculated on the CPU.
    float equatorStepSize = M_2PI_F / float( numEquatorSteps );
    float equatorHalfStep = ( equatorStepSize / 2.0 ) - 0.0001;
    float polarStepSize = M_PI_F / float( numPolarSteps );
    float polarHalfStep = ( polarStepSize / 2.0 ) - 0.0001;

    // The vector between the camera and the billboard.
    vec3 lookVec = normalize( camPos - center );

    // Generate the camera up and right vectors from
    // the object transform and camera forward.
    vec3 camUp = imposterUp;
    vec3 camRight = cross( -lookVec, camUp );

    // The billboarding is based on the camera directions.
    vec3 rightVec  = camRight * sCornerRight[corner];
    vec3 upVec     = camUp * sCornerUp[corner];

    float lookPitch = acos( dot( imposterUp, lookVec ) );

    // First check to see if we need to render the top billboard.   
    int index;
    /*
    if ( includePoles && ( lookPitch < polarAngle || lookPitch > sPi - polarAngle ) )
    {
      index = numEquatorSteps * 3; 

      // When we render the top/bottom billboard we always use
      // a fixed vector that matches the rotation of the object.
      rightVec = vec3( 1, 0, 0 ) * sCornerRight[corner];
      upVec = vec3( 0, 1, 0 ) * sCornerUp[corner];

      if ( lookPitch > sPi - polarAngle )
      {
         upVec = -upVec;
         index++;
      }
    }
    else
    */
    {
        // Calculate the rotation around the z axis then add the
        // equator half step.  This gets the images to switch a
        // half step before the captured angle is met.
        float lookAzimuth = atan( lookVec.y, lookVec.x );
        float azimuth = atan( imposterRight.y, imposterRight.x );
        float rotZ = ( lookAzimuth - azimuth ) + equatorHalfStep;

        // The y rotation is calculated from the look vector and 
        // the object up vector.
        float rotY = lookPitch - polarHalfStep;

        // TODO: How can we do this without conditionals?
        // Normalize the result to 0 to 2PI.
        if ( rotZ < 0.0 )
            rotZ += M_2PI_F;
        if ( rotZ > M_2PI_F )
            rotZ -= M_2PI_F;
        if ( rotY < 0.0 )
            rotY += M_2PI_F;
        if ( rotY > M_PI_F ) // Not M_2PI_F?
            rotY -= M_2PI_F;

        float polarIdx = round( abs( rotY ) / polarStepSize );

        // Get the index to the start of the right polar
        // images for this viewing angle.
        int numPolarOffset = int( float( numEquatorSteps ) * polarIdx );

        // Calculate the final image index for lookup 
        // of the texture coords.
        index = int( rotZ / equatorStepSize ) + numPolarOffset;
    }

    // Generate the final world space position.         
    outWsPosition = center + ( upVec * halfSize ) + ( rightVec * halfSize );

    // Grab the uv set and setup the texture coord.
    vec4 uvSet = uvs[index];
    outTexCoord.x = uvSet.x + ( uvSet.z * sUVCornerExtent[corner].x );
    outTexCoord.y = uvSet.y + ( uvSet.w * sUVCornerExtent[corner].y );

    // Needed for normal mapping and lighting.    
    outWorldToTangent[0] = vec3( 1, 0, 0 );
    outWorldToTangent[1] = vec3( 0, 1, 0 );
    outWorldToTangent[2] = vec3( 0, 0, -1 );
}
