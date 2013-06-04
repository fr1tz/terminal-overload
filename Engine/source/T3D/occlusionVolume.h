// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _OCCLUSIONVOLUME_H_
#define _OCCLUSIONVOLUME_H_

#ifndef _SCENEPOLYHEDRALSPACE_H_
#include "scene/scenePolyhedralSpace.h"
#endif

#ifndef _MSILHOUETTEEXTRACTOR_H_
#include "math/mSilhouetteExtractor.h"
#endif



/// A volume in space that blocks visibility.
class OcclusionVolume : public ScenePolyhedralSpace
{
   public:

      typedef ScenePolyhedralSpace Parent;

   protected:

      typedef SilhouetteExtractorPerspective< PolyhedronType > SilhouetteExtractorType;

      /// Whether the volume's transform has changed and we need to recompute
      /// transform-based data.
      bool mTransformDirty;

      /// World-space points of the volume's polyhedron.
      Vector< Point3F > mWSPoints;

      /// Silhouette extractor when using perspective projections.
      SilhouetteExtractorType mSilhouetteExtractor;
      
      // SceneSpace.
      virtual void _renderObject( ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat );

   public:

      OcclusionVolume();

      // SimObject.
      DECLARE_CONOBJECT( OcclusionVolume );
      DECLARE_DESCRIPTION( "A visibility blocking volume." );
      DECLARE_CATEGORY( "3D Scene" );

      virtual bool onAdd();

      static void consoleInit();

      // SceneObject.
      virtual void buildSilhouette( const SceneCameraState& cameraState, Vector< Point3F >& outPoints );
      virtual void setTransform( const MatrixF& mat );
};

#endif // !_OCCLUSIONVOLUME_H_
