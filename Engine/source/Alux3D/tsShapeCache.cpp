// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "tsShapeCache.h"

Vector<TSShapeCache::TSShapeRef> TSShapeCache::mCachedShapes;

void TSShapeCache::insertPtr(U32 id, TSShape* ptr)
{
	for(U32 i = 0; i < mCachedShapes.size(); i++)
	{
		TSShapeRef& ref = mCachedShapes[i];
		if(ref.id == id)
		{
			ref.ptr = ptr;
			return;
		}
	}

	TSShapeRef ref;
	ref.id = id;
	ref.ptr = ptr;

	mCachedShapes.push_back(ref);
}

void TSShapeCache::removePtr(U32 id)
{
	for(U32 i = 0; i < mCachedShapes.size(); i++)
	{
		const TSShapeRef& ref = mCachedShapes[i];
		if(ref.id == id)
		{
			mCachedShapes.erase(i);
			return;
		}
	}
}

TSShape* TSShapeCache::getPtr(U32 id)
{
	for(U32 i = 0; i < mCachedShapes.size(); i++)
	{
		const TSShapeRef& ref = mCachedShapes[i];
		if(ref.id == id)
			return ref.ptr;
	}

	return NULL;
}
