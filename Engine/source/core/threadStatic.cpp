// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/threadStatic.h"

//-----------------------------------------------------------------------------
// Statics
U32 _TorqueThreadStatic::mListIndex = 0;

_TorqueThreadStaticReg *_TorqueThreadStaticReg::smFirst = NULL;
//-----------------------------------------------------------------------------

inline Vector<TorqueThreadStaticList> &_TorqueThreadStaticReg::getThreadStaticListVector()
{
   // This function assures that the static vector of ThreadStatics will get initialized
   // before first use.
   static Vector<TorqueThreadStaticList> sTorqueThreadStaticVec( __FILE__, __LINE__ );

   return sTorqueThreadStaticVec;
}

//-----------------------------------------------------------------------------

// Destructor, size should == 1 otherwise someone didn't clean up, or someone
// did horrible things to list index 0
_TorqueThreadStaticReg::~_TorqueThreadStaticReg()
{
   AssertFatal( getThreadStaticListVector().size() == 1, "Destruction of static list was not performed on program exit" );
}

//-----------------------------------------------------------------------------

void _TorqueThreadStaticReg::destroyInstances()
{
   // mThreadStaticInstances[0] does *not* need to be deallocated
   // because all members of the list are pointers to static memory
   while( getThreadStaticListVector().size() > 1 )
   {
      // Delete the members of this list
      while( getThreadStaticListVector().last().size() )
      {
         _TorqueThreadStatic *biscuit = getThreadStaticListVector().last().first();

         // Erase the vector entry
         getThreadStaticListVector().last().pop_front();

         // And finally the memory
         delete biscuit;
      }

      // Remove the entry from the list of lists
      getThreadStaticListVector().pop_back();
   }
}

//-----------------------------------------------------------------------------

void _TorqueThreadStaticReg::destroyInstance( TorqueThreadStaticList *instanceList )
{
   AssertFatal( instanceList != &getThreadStaticListVector().first(), "Cannot delete static instance list index 0" );

   while( instanceList->size() )
   {
      _TorqueThreadStatic *biscuit = getThreadStaticListVector().last().first();

      // Erase the vector entry
      getThreadStaticListVector().last().pop_front();

      // And finally the memory
      delete biscuit;
   }

   getThreadStaticListVector().erase( instanceList );
}

//-----------------------------------------------------------------------------

TorqueThreadStaticListHandle _TorqueThreadStaticReg::spawnThreadStaticsInstance()
{
   AssertFatal( getThreadStaticListVector().size() > 0, "List is not initialized somehow" );

   // Add a new list of static instances
   getThreadStaticListVector().increment();

   // Copy mThreadStaticInstances[0] (master copy) into new memory, and
   // pass it back.
   for( int i = 0; i < getThreadStaticListVector()[0].size(); i++ )
   {
      getThreadStaticListVector().last().push_back( getThreadStaticListVector()[0][i]->_createInstance() );
   }

   // Return list index of newly allocated static instance list
   return &getThreadStaticListVector().last();
}