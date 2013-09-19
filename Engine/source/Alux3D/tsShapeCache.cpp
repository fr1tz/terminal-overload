// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "tsShapeCache.h"

Vector<TSShapeCache::TSShapeRef> TSShapeCache::mCachedShapes;

void TSShapeCache::allocate(U32 id)
{
	TSShapeRef ref;
	ref.id = id;
	ref.ptr = new TSShape();

	mCachedShapes.push_back(ref);
}

void TSShapeCache::destroy(U32 id)
{
	for(U32 i = 0; i < mCachedShapes.size(); i++)
	{
		const TSShapeRef& ref = mCachedShapes[i];
		if(ref.id == id)
		{
			delete ref.ptr;
			mCachedShapes.erase(i);
			return;
		}
	}
}

TSShape* TSShapeCache::get(U32 id)
{
	for(U32 i = 0; i < mCachedShapes.size(); i++)
	{
		const TSShapeRef& ref = mCachedShapes[i];
		if(ref.id == id)
			return ref.ptr;
	}

	return NULL;
}
