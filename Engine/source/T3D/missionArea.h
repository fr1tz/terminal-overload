// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MISSIONAREA_H_
#define _MISSIONAREA_H_

#ifndef _NETOBJECT_H_
#include "sim/netObject.h"
#endif

class MissionArea : public NetObject
{
  private:
   typedef NetObject Parent;
   RectI             mArea;

   F32 mFlightCeiling;
   F32 mFlightCeilingRange;

   static MissionArea * smServerObject;

  public:
   MissionArea();

   static RectI      smMissionArea;

   static MissionArea * getServerObject();

   F32 getFlightCeiling()      const { return mFlightCeiling;      }
   F32 getFlightCeilingRange() const { return mFlightCeilingRange; }

   //
   const RectI & getArea(){return(mArea);}
   void setArea(const RectI & area);

   /// @name SimObject Inheritance
   /// @{
   bool onAdd();
   void onRemove();

   void inspectPostApply();

   static void initPersistFields();
   /// @}

   /// @name NetObject Inheritance
   /// @{
   enum NetMaskBits {
      UpdateMask     = BIT(0)
   };

   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);
   /// @}

   DECLARE_CONOBJECT(MissionArea);
};

#endif
