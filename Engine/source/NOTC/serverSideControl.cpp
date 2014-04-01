// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#include "game/serverSideControl.h"
#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------

ServerSideController::ServerSideController()
{

}

//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(HoverPodController);

HoverPodController::HoverPodController()
{
	mClientId = -1;
	mDirection.set(1, 0, 0);
}

Move HoverPodController::getMove(ShapeBase* obj)
{
	Move retMove = NullMove;

	GameConnection* client = NULL;
	if(!Sim::findObject(mClientId, client)) 
		return retMove;

	ShapeBase* control = client->getControlObject();
	if(control)
	{
		Move cMove = client->lastReceivedMove();

		Point3F v1, v2;
		control->getTransform().getColumn(0, &v1);
		control->getTransform().getColumn(1, &v2);
		Point3F pv = v1*cMove.x + v2*cMove.y;

		//pv = mDirection * mDot(pv, mDirection);

		obj->getTransform().getColumn(0, &v1);
		obj->getTransform().getColumn(1, &v2);
		retMove.x = mDot(v1, pv);
		retMove.y = mDot(v2, pv);
	}
	return retMove;	
#if 0
   if(this->isServerObject() && this->isMounted())
   {
		Move mMove = NullMove;
		ShapeBase* mount = this->getObjectMount();
		if(mount->getType() & VehicleObjectType)
		{
			Vehicle* vehicle = (Vehicle*)mount;
			if(move && move->x != 0)
			{
				mMove.yaw = move->x;
			}
			else
			{
				Point3F zv; vehicle->getTransform().getColumn(2, &zv);
				zv.normalize();
				Point3F m = vehicle->getRigid().angMomentum;
				//Point3F v = vehicle->getRigid().angVelocity;
				F32 dot = mDot(zv, m);
				//Con::printf("%f / %f %f %f / %f %f %f", dot,
				//	m.x, m.y, m.z, v.x, v.y, v.z);
				mMove.yaw = dot / 50;
			}

			if(move)
				mMove.y = move->y;

		}
		else if(move)
		{
			Point3F v1, v2;
			this->getTransform().getColumn(0, &v1);
			this->getTransform().getColumn(1, &v2);
			Point3F pv = v1*move->x + v2*move->y;

			mount->getTransform().getColumn(0, &v1);
			mount->getTransform().getColumn(1, &v2);

			mMove.x = mDot(v1, pv);
			mMove.y = mDot(v2, pv);
		}
		mount->processTick(&mMove);
   }
#endif
}

void HoverPodController::initPersistFields()
{
   addField("client",     TypeS32,     Offset(mClientId, HoverPodController));
}

#endif // BORQUE_NEEDS_PORTING
