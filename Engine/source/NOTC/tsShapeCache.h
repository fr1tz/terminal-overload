// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TSSHAPECACHE_H_
#define _TSSHAPECACHE_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif

//----------------------------------------------------------------------------

class TSShapeCache
{
 public:
	 static void insertPtr(U32 id, TSShape* ptr);
	 static void removePtr(U32 id);
	 static TSShape* getPtr(U32 id);

 private:
	struct TSShapeRef
	{
		TSShape* ptr;
		U32 id;
	};

	static Vector<TSShapeRef> mCachedShapes;
};

#endif // _TSSHAPECACHE_H_
