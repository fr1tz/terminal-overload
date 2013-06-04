// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENESPACE_H_
#define _SCENESPACE_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif


/// Abstract base class for SceneObjects that define subspaces in a scene.
///
/// Use SceneObject::containsPoint to find out whether a given space contains a particular point.
class SceneSpace : public SceneObject
{
   public:

      typedef SceneObject Parent;

   protected:

      enum
      {
         TransformMask = Parent::NextFreeMask << 0,   ///< Object transform has changed.
         NextFreeMask  = Parent::NextFreeMask << 1,
      };

      ///
      BaseMatInstance* mEditorRenderMaterial;

      ///
      virtual BaseMatInstance* _createEditorRenderMaterial();

      /// Render a visualization of the volume.
      virtual void _renderObject( ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat );

      ///
      virtual ColorI _getDefaultEditorSolidColor() const { return ColorI( 255, 255, 255, 45 ); }
      virtual ColorI _getDefaultEditorWireframeColor() const { return ColorI::BLACK; }

   public:

      SceneSpace();
      ~SceneSpace();

      // SimObject.
      virtual bool onAdd();
      virtual void onRemove();

      // SceneObject.
      virtual void setTransform( const MatrixF &mat );
      virtual void prepRenderImage( SceneRenderState* state );

      // NetObject.
      virtual U32 packUpdate( NetConnection* connection, U32 mask, BitStream* stream );
      virtual void unpackUpdate( NetConnection* connection, BitStream* stream );

      // SimObject.
      virtual void onEditorEnable();
      virtual void onEditorDisable();
};

#endif // !_SCENESPACE_H_
