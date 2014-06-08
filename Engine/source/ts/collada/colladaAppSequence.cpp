// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "ts/collada/colladaExtensions.h"
#include "ts/collada/colladaAppSequence.h"


ColladaAppSequence::ColladaAppSequence(const domAnimation_clip* clip)
   : pClip(clip), clipExt(new ColladaExtension_animation_clip(clip))
{
   seqStart = pClip->getStart();
   seqEnd = pClip->getEnd();
}

ColladaAppSequence::~ColladaAppSequence()
{
   delete clipExt;
}

const char* ColladaAppSequence::getName() const
{
   return _GetNameOrId(pClip);
}

S32 ColladaAppSequence::getNumTriggers()
{
   return clipExt->triggers.size();
}

void ColladaAppSequence::getTrigger(S32 index, TSShape::Trigger& trigger)
{
   trigger.pos = clipExt->triggers[index].time;
   trigger.state = clipExt->triggers[index].state;
}

U32 ColladaAppSequence::getFlags() const
{
   U32 flags = 0;
   if (clipExt->cyclic) flags |= TSShape::Cyclic;
   if (clipExt->blend)  flags |= TSShape::Blend;
   return flags;
}

F32 ColladaAppSequence::getPriority()
{
   return clipExt->priority;
}

F32 ColladaAppSequence::getBlendRefTime()
{
   return clipExt->blendReferenceTime;
}

void ColladaAppSequence::setActive(bool active)
{
   for (S32 iAnim = 0; iAnim < getClip()->getInstance_animation_array().getCount(); iAnim++) {
      domAnimation* anim = daeSafeCast<domAnimation>(getClip()->getInstance_animation_array()[iAnim]->getUrl().getElement());
      if (anim)
         setAnimationActive(anim, active);
   }
}

void ColladaAppSequence::setAnimationActive(const domAnimation* anim, bool active)
{
   // Enabled/disable data channels for this animation
   for (S32 iChannel = 0; iChannel < anim->getChannel_array().getCount(); iChannel++) {
      domChannel* channel = anim->getChannel_array()[iChannel];
      AnimData* animData = reinterpret_cast<AnimData*>(channel->getUserData());
      if (animData)
         animData->enabled = active;
   }

   // Recurse into child animations
   for (S32 iAnim = 0; iAnim < anim->getAnimation_array().getCount(); iAnim++)
      setAnimationActive(anim->getAnimation_array()[iAnim], active);
}
