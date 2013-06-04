// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _COLLADA_APPSEQUENCE_H_
#define _COLLADA_APPSEQUENCE_H_

#ifndef _APPSEQUENCE_H_
#include "ts/loader/appSequence.h"
#endif

class domAnimation_clip;
class ColladaExtension_animation_clip;

class ColladaAppSequence : public AppSequence
{
   const domAnimation_clip*            pClip;
   ColladaExtension_animation_clip*    clipExt;

   F32      seqStart;
   F32      seqEnd;

   void setAnimationActive(const domAnimation* anim, bool active);

public:
   ColladaAppSequence(const domAnimation_clip* clip);
   ~ColladaAppSequence();

   void setActive(bool active);

   const domAnimation_clip* getClip() const { return pClip; }

   S32 getNumTriggers();
   void getTrigger(S32 index, TSShape::Trigger& trigger);

   const char* getName() const;

   F32 getStart() const { return seqStart; }
   F32 getEnd() const { return seqEnd; }
   void setEnd(F32 end) { seqEnd = end; }

   U32 getFlags() const;
   F32 getPriority();
   F32 getBlendRefTime();
};

#endif // _COLLADA_APPSEQUENCE_H_
