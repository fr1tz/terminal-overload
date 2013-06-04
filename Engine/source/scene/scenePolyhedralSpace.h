// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENEPOLYHEDRALSPACE_H_
#define _SCENEPOLYHEDRALSPACE_H_

#ifndef _SCENESPACE_H_
#include "scene/sceneSpace.h"
#endif

#ifndef _SCENEPOLYHEDRALOBJECT_H_
#include "scene/mixin/scenePolyhedralObject.h"
#endif


///
class ScenePolyhedralSpace : public ScenePolyhedralObject< SceneSpace >
{
   public:

      typedef ScenePolyhedralObject< SceneSpace > Parent;

      ScenePolyhedralSpace() {}
      ScenePolyhedralSpace( const PolyhedronType& polyhedron )
         : Parent( polyhedron ) {}
};

#endif // !_SCENEPOLYHEDRALSPACE_H_
