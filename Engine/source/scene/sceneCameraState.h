// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENECAMERASTATE_H_
#define _SCENECAMERASTATE_H_

#ifndef _MATHUTIL_FRUSTUM_H_
#include "math/util/frustum.h"
#endif

#ifndef _MRECT_H_
#include "math/mRect.h"
#endif

#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif


/// An object that combines all the state that is relevant to looking into the
/// scene from a particular point of view.
class SceneCameraState
{
   protected:

      /// The screen-space viewport rectangle.
      RectI mViewport;

      /// The viewing frustum.
      Frustum mFrustum;

      /// The inverse of the frustum's transform stored here for caching.
      MatrixF mWorldViewMatrix;

      /// The projection matrix.
      MatrixF mProjectionMatrix;

      /// World-space vector representing the view direction.
      Point3F mViewDirection;

      /// Internal constructor.
      SceneCameraState() {}

   public:

      /// Freeze the given viewing state.
      ///
      /// @param viewport Screen-space viewport rectangle.
      /// @param frustum Camera frustum.
      /// @param worldView World->view matrix.
      /// @param projection Projection matrix.
      SceneCameraState( const RectI& viewport, const Frustum& frustum, const MatrixF& worldView, const MatrixF& projection );

      /// Capture the view state from the current GFX state.
      static SceneCameraState fromGFX();

      ///
      static SceneCameraState fromGFXWithViewport( const RectI& viewport );

      /// Return the screen-space viewport rectangle.
      const RectI& getViewport() const { return mViewport; }

      /// Return the camera frustum.
      const Frustum& getFrustum() const { return mFrustum; }

      /// Return the view position.  This is a shortcut for getFrustum().getPosition().
      const Point3F& getViewPosition() const { return mFrustum.getPosition(); }

      /// Return the world-space view vector.
      const Point3F& getViewDirection() const { return mViewDirection; }

      /// Return the view->world transform.  This is a shortcut for getFrustum().getTransform().
      const MatrixF& getViewWorldMatrix() const { return mFrustum.getTransform(); }

      /// Return the world->view transform.
      const MatrixF& getWorldViewMatrix() const { return mWorldViewMatrix; }

      /// Return the projection transform.
      const MatrixF& getProjectionMatrix() const { return mProjectionMatrix; }
};

#endif // !_SCENECAMERASTATE_H_
