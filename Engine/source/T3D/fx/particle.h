// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif

#define MaxParticleSize 50.0

struct Particle;

//*****************************************************************************
// Particle Data
//*****************************************************************************
class ParticleData : public SimDataBlock
{
   typedef SimDataBlock Parent;

  public:
   enum PDConst
   {
      PDC_NUM_KEYS = 4,
   };

   F32   dragCoefficient;
   F32   windCoefficient;
   F32   gravityCoefficient;

   F32   inheritedVelFactor;
   F32   constantAcceleration;

   S32   lifetimeMS;
   S32   lifetimeVarianceMS;

   F32   spinSpeed;        // degrees per second
   F32   spinRandomMin;
   F32   spinRandomMax;

   bool  useInvAlpha;

   bool  animateTexture;
   U32   numFrames;
   U32   framesPerSec;

   ColorF colors[ PDC_NUM_KEYS ];
   F32    sizes[ PDC_NUM_KEYS ];
   F32    times[ PDC_NUM_KEYS ];

   Point2F*          animTexUVs;
   Point2F           texCoords[4];   // default: {{0.0,0.0}, {0.0,1.0}, {1.0,1.0}, {1.0,0.0}} 
   Point2I           animTexTiling;
   StringTableEntry  animTexFramesString;
   Vector<U8>        animTexFrames;
   StringTableEntry  textureName;
   GFXTexHandle      textureHandle;

   static bool protectedSetSizes( void *object, const char *index, const char *data );
   static bool protectedSetTimes( void *object, const char *index, const char *data );

  public:
   ParticleData();
   ~ParticleData();

   // move this procedure to Particle
   void initializeParticle(Particle*, const Point3F&);

   void packData(BitStream* stream);
   void unpackData(BitStream* stream);
   bool onAdd();
   bool preload(bool server, String &errorStr);
   DECLARE_CONOBJECT(ParticleData);
   static void  initPersistFields();

   bool reload(char errorBuffer[256]);
};

//*****************************************************************************
// Particle
// 
// This structure should be as small as possible.
//*****************************************************************************
struct Particle
{
   Point3F  pos;     // current instantaneous position
   Point3F  vel;     //   "         "         velocity
   Point3F  acc;     // Constant acceleration
   Point3F  orientDir;  // direction particle should go if using oriented particles

   U32           totalLifetime;   // Total ms that this instance should be "live"
   ParticleData* dataBlock;       // datablock that contains global parameters for
                                  //  this instance
   U32       currentAge;


   // are these necessary to store here? - they are interpolated in real time
   ColorF           color;
   F32              size;

   F32              spinSpeed;

   Point3F moveWithObjectLastPos; // the position of the object this particle
                                  // is moving with on the particle's last update
   Particle *       next;
};


#endif // _PARTICLE_H_