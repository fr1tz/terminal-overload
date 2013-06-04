// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "core/util/tSignal.h"


void SignalBase::DelegateLink::insert(DelegateLink* node, float order)
{
   // Note: can only legitimately be called on list head
   DelegateLink * walk = next;
   while (order >= walk->order && walk->next != this)
      walk = walk->next;
   if (order >= walk->order)
   {
      // insert after walk
      node->prev = walk;
      node->next = walk->next;
      walk->next->prev = node;
      walk->next = node;
   }
   else
   {
      // insert before walk
      node->prev = walk->prev;
      node->next = walk;
      walk->prev->next = node;
      walk->prev = node;
   }
   node->order = order;
}

void SignalBase::DelegateLink::unlink()
{
   // Unlink this node
   next->prev = prev;
   prev->next = next;
}

SignalBase::~SignalBase()
{
   removeAll();
}

void SignalBase::removeAll()
{
   while (mList.next != &mList)
   {
      DelegateLink* ptr = mList.next;
      ptr->unlink();
      delete ptr;
   }
}
