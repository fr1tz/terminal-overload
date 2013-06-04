// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _COLLADA_SHAPELOADER_H_
#define _COLLADA_SHAPELOADER_H_

#ifndef _TSSHAPELOADER_H_
#include "ts/loader/tsShapeLoader.h"
#endif

class domCOLLADA;
class domAnimation;
struct AnimChannels;

//-----------------------------------------------------------------------------
class ColladaShapeLoader : public TSShapeLoader
{
   friend TSShape* loadColladaShape(const Torque::Path &path);

   domCOLLADA*             root;
   Vector<AnimChannels*>   animations;       ///< Holds all animation channels for deletion after loading

   void processAnimation(const domAnimation* anim, F32& maxEndTime, F32& minFrameTime);

   void cleanup();

public:
   ColladaShapeLoader(domCOLLADA* _root);
   ~ColladaShapeLoader();

   void enumerateScene();
   bool ignoreNode(const String& name);
   bool ignoreMesh(const String& name);
   void computeBounds(Box3F& bounds);

   static bool canLoadCachedDTS(const Torque::Path& path);
   static bool checkAndMountSketchup(const Torque::Path& path, String& mountPoint, Torque::Path& daePath);
   static domCOLLADA* getDomCOLLADA(const Torque::Path& path);
   static domCOLLADA* readColladaFile(const String& path);
};

#endif // _COLLADA_SHAPELOADER_H_
