// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TEXTUREDPOLYLIST_H_
#define _TEXTUREDPOLYLIST_H_

#ifndef _MMATH_H_
#include "math/mMath.h"
#endif
#ifndef _TVECTORSPEC_H_
#include "core/util/tVectorSpecializations.h"
#endif
#ifndef _ABSTRACTPOLYLIST_H_
#include "collision/abstractPolyList.h"
#endif

#define CLIPPEDPOLYLIST_FLAG_ALLOWCLIPPING		0x01

//----------------------------------------------------------------------------
/// Clipped Textured PolyList
///
/// This takes the geometry passed to it and clips against the PlaneList set
/// by the caller.
///
/// It also offers functions to:
///    - Create texture coordinates
///    - Create a "coat" of user defined "thickness" out of the polys.
///      (Can for example be used to create a shield effect around an object.)
///
/// @see AbstractPolyList
class TexturedPolyList : public AbstractPolyList
{
   void memcpy(U32* d, U32* s,U32 size);

public:
   struct Vertex {
      Point3F point;
      Point3F normal;
      Point2F texCoord;
      Point2F peakness;
      F32 dangerScale;
      U32 mask;
   };

   struct Poly {
      PlaneF plane;
      SceneObject* object;
      BaseMatInstance* material;

      U32 vertexStart;
      U32 vertexCount;
      U32 surfaceKey;
	  U32 polyFlags;
   };

   /// ???
   static bool allowClipping;

   typedef Vector<PlaneF> PlaneList;
   typedef Vector<Vertex> VertexList;
   typedef Vector<Poly> PolyList;
   typedef FastVector<U32> IndexList;

   typedef PlaneList::iterator PlaneListIterator;
   typedef VertexList::iterator VertexListIterator;
   typedef PolyList::iterator PolyListIterator;
   typedef IndexList::iterator IndexListIterator;

   // Internal data
   PolyList   mPolyList;
   VertexList mVertexList;
   IndexList  mIndexList;

   // Temporary lists used by triangulate and kept
   // here to reduce memory allocations.
   PolyList    mTempPolyList;
   IndexList   mTempIndexList;

   const static U32 IndexListReserveSize = 128;

   /// The per-vertex normals.
   /// @see generateNormals()
   Vector<VectorF> mNormalList;

   PlaneList mPolyPlaneList;

   /// The list of planes to clip against.
   ///
   /// This should be set before filling the polylist.
   PlaneList mPlaneList;
   
   /// If non-zero any poly facing away from this 
   /// normal is removed from the list.
   /// 
   /// This should be set before filling the polylist.
   VectorF mNormal;

   /// If the dot product result between a poly's normal and mNormal is greater 
   /// than this value it will be rejected.
   /// The default value is 0.  
   /// 90 degrees = mCos( mDegToRad( 90.0f ) = 0
   F32 mNormalTolCosineRadians;

   //
   TexturedPolyList();
   ~TexturedPolyList();
   void clear();

   // AbstractPolyList
   bool isEmpty() const;
   U32 addPoint(const Point3F& p);
   U32 addPointAndNormal(const Point3F& p, const Point3F& normal);
   U32 addPlane(const PlaneF& plane);
   void begin(BaseMatInstance* material,U32 surfaceKey);
   void plane(U32 v1,U32 v2,U32 v3);
   void plane(const PlaneF& p);
   void plane(const U32 index);
   void vertex(U32 vi);
   void end();

   /// Often after clipping you'll end up with orphan verticies
   /// that are unused by the poly list.  This removes these unused
   /// verts and updates the index list.
   void cullUnusedVerts();
   
   /// This breaks all polys in the polylist into triangles.
   void triangulate();
   
   /// Generates averaged normals from the poly normals.
   /// @see mNormalList
   void generateNormals();

	void addCoat(F32 thickness); // NOTE: Slow as hell!
	void addTexture(S32 squareSize);

  protected:

   // AbstractPolyList
   const PlaneF& getIndexedPlane(const U32 index);
};

#endif // _TEXTUREDPOLYLIST_H_
