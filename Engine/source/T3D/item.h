// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ITEM_H_
#define _ITEM_H_

#ifndef _SHAPEBASE_H_
   #include "T3D/shapeBase.h"
#endif
#ifndef _BOXCONVEX_H_
   #include "collision/boxConvex.h"
#endif
#ifndef _DYNAMIC_CONSOLETYPES_H_
   #include "console/dynamicTypes.h"
#endif


class PhysicsBody;


//----------------------------------------------------------------------------

struct ItemData: public ShapeBaseData {
   typedef ShapeBaseData Parent;

   F32 friction;
   F32 elasticity;

   bool sticky;
   F32  gravityMod;
   F32  maxVelocity;

   bool        lightOnlyStatic;
   S32         lightType;
   ColorF      lightColor;
   S32         lightTime;
   F32         lightRadius;

   bool        simpleServerCollision;

   ItemData();
   DECLARE_CONOBJECT(ItemData);
   static void initPersistFields();
   virtual void packData(BitStream* stream);
   virtual void unpackData(BitStream* stream);
};


//----------------------------------------------------------------------------

class Item: public ShapeBase
{
  protected:
   typedef ShapeBase Parent;

   enum MaskBits {
      HiddenMask   = Parent::NextFreeMask,
      ThrowSrcMask = Parent::NextFreeMask << 1,
      PositionMask = Parent::NextFreeMask << 2,
      RotationMask = Parent::NextFreeMask << 3,
      NextFreeMask = Parent::NextFreeMask << 4
   };

   // Client interpolation data
   struct StateDelta {
      Point3F pos;
      VectorF posVec;
      S32 warpTicks;
      Point3F warpOffset;
      F32     dt;
   };
   StateDelta delta;

   // Static attributes
   ItemData* mDataBlock;
   static F32 mGravity;
   bool mStatic;
   bool mRotate;

   //
   VectorF mVelocity;
   bool mAtRest;

   S32 mAtRestCounter;
   static const S32 csmAtRestTimer;

   bool mInLiquid;

   ShapeBase* mCollisionObject;
   U32 mCollisionTimeout;

   PhysicsBody *mPhysicsRep;

   bool mSubclassItemHandlesScene;  ///< A subclass of Item will handle all of the adding to the scene

  protected:
	DECLARE_CALLBACK( void, onStickyCollision, ( const char* objID ));
	DECLARE_CALLBACK( void, onEnterLiquid, ( const char* objID, const char* waterCoverage, const char* liquidType ));
	DECLARE_CALLBACK( void, onLeaveLiquid, ( const char* objID, const char* liquidType ));

  public:

   void registerLights(LightManager * lightManager, bool lightingScene);
   enum LightType
   {
      NoLight = 0,
      ConstantLight,
      PulsingLight,

      NumLightTypes,
   };

  private:
   S32         mDropTime;
   LightInfo*  mLight;

  public:

   Point3F mStickyCollisionPos;
   Point3F mStickyCollisionNormal;

   //
  private:
   OrthoBoxConvex mConvex;
   Box3F          mWorkingQueryBox;

   void updateVelocity(const F32 dt);
   void updatePos(const U32 mask, const F32 dt);
   void updateWorkingCollisionSet(const U32 mask, const F32 dt);
   bool buildPolyList(PolyListContext context, AbstractPolyList* polyList, const Box3F &box, const SphereF &sphere);
   void buildConvex(const Box3F& box, Convex* convex);
   void onDeleteNotify(SimObject*);

   static bool _setStatic(void *object, const char *index, const char *data);
   static bool _setRotate(void *object, const char *index, const char *data);

  protected:
   void _updatePhysics();
   void prepRenderImage(SceneRenderState *state);
   void advanceTime(F32 dt);

  public:
   DECLARE_CONOBJECT(Item);


   Item();
   ~Item();
   static void initPersistFields();
   static void consoleInit();

   bool onAdd();
   void onRemove();
   bool onNewDataBlock( GameBaseData *dptr, bool reload );

   bool isStatic()   { return mStatic; }
   bool isAtRest()   { return mAtRest; }
   bool isRotating() { return mRotate; }
   Point3F getVelocity() const;
   void setVelocity(const VectorF& vel);
   void applyImpulse(const Point3F& pos,const VectorF& vec);
   void setCollisionTimeout(ShapeBase* obj);
   ShapeBase* getCollisionObject()   { return mCollisionObject; };

   void processTick(const Move *move);
   void interpolateTick(F32 delta);
   virtual void setTransform(const MatrixF &mat);
   virtual void onUnmount(SceneObject* obj, S32 node);

   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);
};

typedef Item::LightType ItemLightType;
DefineEnumType( ItemLightType );

#endif
