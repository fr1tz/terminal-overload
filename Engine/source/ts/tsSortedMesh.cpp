// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "ts/tsSortedMesh.h"
#include "math/mMath.h"
#include "ts/tsShapeInstance.h"

// Not worth the effort, much less the effort to comment, but if the draw types
// are consecutive use addition rather than a table to go from index to command value...
/*
#if ((GL_TRIANGLES+1==GL_TRIANGLE_STRIP) && (GL_TRIANGLE_STRIP+1==GL_TRIANGLE_FAN))
   #define getDrawType(a) (GL_TRIANGLES+(a))
#else
   U32 drawTypes[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN };
   #define getDrawType(a) (drawTypes[a])
#endif
*/

// found in tsmesh
extern void forceFaceCamera();
extern void forceFaceCameraZAxis();

//-----------------------------------------------------
// TSSortedMesh render methods
//-----------------------------------------------------

void TSSortedMesh::render(S32 frame, S32 matFrame, TSMaterialList * materials)
{
}

//-----------------------------------------------------
// TSSortedMesh collision methods
//-----------------------------------------------------

bool TSSortedMesh::buildPolyList( S32 frame, AbstractPolyList *polyList, U32 &surfaceKey, TSMaterialList *materials )
{
   TORQUE_UNUSED(frame);
   TORQUE_UNUSED(polyList);
   TORQUE_UNUSED(surfaceKey);
   TORQUE_UNUSED(materials);

   return false;
}

bool TSSortedMesh::castRay( S32 frame, const Point3F &start, const Point3F &end, RayInfo *rayInfo, TSMaterialList *materials )
{
   TORQUE_UNUSED(frame);
   TORQUE_UNUSED(start);
   TORQUE_UNUSED(end);
   TORQUE_UNUSED(rayInfo);
   TORQUE_UNUSED(materials);

   return false;
}

bool TSSortedMesh::buildConvexHull()
{
   return false;
}

S32 TSSortedMesh::getNumPolys()
{
   S32 count = 0;
   S32 cIdx = !clusters.size() ? -1 : 0;
   while (cIdx>=0)
   {
      Cluster & cluster = clusters[cIdx];
      for (S32 i=cluster.startPrimitive; i<cluster.endPrimitive; i++)
      {
         if (primitives[i].matIndex & TSDrawPrimitive::Triangles)
            count += primitives[i].numElements / 3;
         else
            count += primitives[i].numElements - 2;
      }
      cIdx = cluster.frontCluster; // always use frontCluster...we assume about the same no matter what
   }
   return count;
}

//-----------------------------------------------------
// TSSortedMesh assembly/dissembly methods
// used for transfer to/from memory buffers
//-----------------------------------------------------

#define tsalloc TSShape::smTSAlloc

void TSSortedMesh::assemble(bool skip)
{
   bool save1 = TSMesh::smUseTriangles;
   bool save2 = TSMesh::smUseOneStrip;
   TSMesh::smUseTriangles = false;
   TSMesh::smUseOneStrip = false;

   TSMesh::assemble(skip);

   TSMesh::smUseTriangles = save1;
   TSMesh::smUseOneStrip = save2;

   S32 numClusters = tsalloc.get32();
   S32 * ptr32 = tsalloc.copyToShape32(numClusters*8);
   clusters.set(ptr32,numClusters);

   S32 sz = tsalloc.get32();
   ptr32 = tsalloc.copyToShape32(sz);
   startCluster.set(ptr32,sz);

   sz = tsalloc.get32();
   ptr32 = tsalloc.copyToShape32(sz);
   firstVerts.set(ptr32,sz);

   sz = tsalloc.get32();
   ptr32 = tsalloc.copyToShape32(sz);
   numVerts.set(ptr32,sz);

   sz = tsalloc.get32();
   ptr32 = tsalloc.copyToShape32(sz);
   firstTVerts.set(ptr32,sz);

   alwaysWriteDepth = tsalloc.get32()!=0;

   tsalloc.checkGuard();
}

void TSSortedMesh::disassemble()
{
   TSMesh::disassemble();

   tsalloc.set32(clusters.size());
   tsalloc.copyToBuffer32((S32*)clusters.address(),clusters.size()*8);

   tsalloc.set32(startCluster.size());
   tsalloc.copyToBuffer32((S32*)startCluster.address(),startCluster.size());

   tsalloc.set32(firstVerts.size());
   tsalloc.copyToBuffer32((S32*)firstVerts.address(),firstVerts.size());

   tsalloc.set32(numVerts.size());
   tsalloc.copyToBuffer32((S32*)numVerts.address(),numVerts.size());

   tsalloc.set32(firstTVerts.size());
   tsalloc.copyToBuffer32((S32*)firstTVerts.address(),firstTVerts.size());

   tsalloc.set32(alwaysWriteDepth ? 1 : 0);

   tsalloc.setGuard();
}



