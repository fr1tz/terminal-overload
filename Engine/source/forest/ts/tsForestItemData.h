// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TSFORESTITEMDATA_H_
#define _TSFORESTITEMDATA_H_

#ifndef _FORESTITEM_H_
#include "forest/forestItem.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif
#ifndef _RESOURCEMANAGER_H_
#include "core/resourceManager.h"
#endif


class TSShapeInstance;
class TSLastDetail;


class TSForestItemData : public ForestItemData 
{
protected:

   typedef ForestItemData Parent;

   bool mIsClientObject;

   // This is setup during forest creation.
   mutable TSShapeInstance *mShapeInstance;

   Resource<TSShape> mShape;

   Vector<S32> mCollisionDetails;
   Vector<S32> mLOSDetails;
   
   TSShapeInstance* _getShapeInstance() const;

   void _loadShape();

   void _onResourceChanged( const Torque::Path &path );

   void _checkLastDetail();

   void _updateCollisionDetails();

   // ForestItemData
   void _preload() { _loadShape(); }

public:
  
   DECLARE_CONOBJECT(TSForestItemData);
   TSForestItemData();
   virtual ~TSForestItemData();
   
   bool preload( bool server, String &errorBuffer );   
   void onRemove();
   bool onAdd();

   virtual void inspectPostApply();

   TSLastDetail* getLastDetail() const;

   // JCF: need access to this to build convex(s) in ForestConvex
   TSShapeInstance* getShapeInstance() const { return _getShapeInstance(); }

   const Vector<S32>& getCollisionDetails() const { return mCollisionDetails; }
   const Vector<S32>& getLOSDetails() const { return mLOSDetails; }

   // ForestItemData
   const Box3F& getObjBox() const { return mShape ? mShape->bounds : Box3F::Invalid; }
   bool render( TSRenderState *rdata, const ForestItem& item ) const;
   ForestCellBatch* allocateBatch() const;
   bool canBillboard( const SceneRenderState *state, const ForestItem &item, F32 distToCamera ) const;
   bool buildPolyList( const ForestItem& item, AbstractPolyList *polyList, const Box3F *box ) const { return false; }
};

#endif // _TSFORESTITEMDATA_H_
