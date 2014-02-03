// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENEPOLYHEDRALOBJECT_H_
#define _SCENEPOLYHEDRALOBJECT_H_

#ifndef _MPOLYHEDRON_H_
#include "math/mPolyhedron.h"
#endif

#include "scene/zones/sceneSimpleZone.h"

/// Shared interface for polyhedral objects.
struct IScenePolyhedralObject
{
      /// Convert the polyhedral object to a raw polyhedron.
      virtual AnyPolyhedron ToAnyPolyhedron() const = 0;
};


/// Helper template for mixing a polyhedral volume definition into
/// the superclass hierarchy of a SceneSpace-derived class.
class ScenePolyhedralObject : public SceneSimpleZone, public IScenePolyhedralObject
{
   public:

      typedef SceneSimpleZone Parent;
      typedef Polyhedron PolyhedronType;

      enum
      {
         MAX_PLANES = 256,
         MAX_POINTS = 256,
         MAX_EDGES = 256
      };

   protected:

      enum
      {
         PolyMask = Parent::NextFreeMask << 0,
         NextFreeMask = Parent::NextFreeMask << 1
      };

      /// Whether the polyhedron corresponds to the object box.  If so,
      /// several things can be fast-tracked.  For example, serializing the
      /// polyhedron is pointless as it can be easily reconstructed from the
      /// object box on load time.  Also, certain operations like containment
      /// tests have significantly faster formulations for AABBs (given that the
      /// input data is transformed into object space) than for general
      /// polyhedrons.
      bool mIsBox;

      /// The polyhedron that defines the volume of the object.
      /// @note Defined in object space by default.
      PolyhedronType mPolyhedron;

      ///
      virtual void _renderObject( ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat );

   public:

      ScenePolyhedralObject()
         : mIsBox( true ) {}

      ScenePolyhedralObject( const PolyhedronType& polyhedron )
         : mIsBox( false ),
           mPolyhedron( polyhedron ) {}

      /// Return the polyhedron that describes the space.
      const PolyhedronType& getPolyhedron() const { return mPolyhedron; }

      // SimObject.
      virtual bool onAdd();
      virtual void writeFields( Stream& stream, U32 tabStop );
      virtual bool writeField( StringTableEntry name, const char* value );

      static void initPersistFields();

      // NetObject.
      virtual U32 packUpdate( NetConnection* connection, U32 mask, BitStream* stream );
      virtual void unpackUpdate( NetConnection* connection, BitStream* stream );
      
      // SceneObject.
      virtual bool containsPoint( const Point3F& point );

      // IScenePolyhedralObject.
      virtual AnyPolyhedron ToAnyPolyhedron() const { return getPolyhedron(); }

   private:

      static bool _setPlane( void* object, const char* index, const char* data );
      static bool _setPoint( void* object, const char* index, const char* data );
      static bool _setEdge( void* object, const char* index, const char* data );
};

#endif // !_SCENEPOLYHEDRALOBJECT_H_
