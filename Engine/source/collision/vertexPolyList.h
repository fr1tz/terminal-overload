// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _VERTEXPOLYLIST_H_
#define _VERTEXPOLYLIST_H_

#ifndef _ABSTRACTPOLYLIST_H_
#include "collision/abstractPolyList.h"
#endif


/// A simple polylist which only gathers the unique verticies passed to it.
class VertexPolyList : public AbstractPolyList
{
public:

   VertexPolyList();
   virtual ~VertexPolyList() {}

   // AbstractPolyList
   U32 addPoint(const Point3F& p);
   U32 addPlane(const PlaneF& plane) { return 0; } 
   void begin(BaseMatInstance* material,U32 surfaceKey) {}
   void plane(U32 v1,U32 v2,U32 v3) {}
   void plane(const PlaneF& p) {}
   void plane(const U32 index) {}
   void vertex(U32 vi) {}
   void end() {}
   const PlaneF& getIndexedPlane(const U32 index);

   /// Clears any captured verts.
   void clear();

   /// Returns true if the polylist contains no verts.
   bool isEmpty() const { return mVertexList.empty(); }

   /// Returns the vertex list.
   Vector<Point3F>& getVertexList() { return mVertexList; }

   /// Returns the constant vertex list.
   const Vector<Point3F>& getVertexList() const { return mVertexList; }

protected:

   /// The unique verts we captured.
   Vector<Point3F> mVertexList;

};


#endif  // _VERTEXPOLYLIST_H_
