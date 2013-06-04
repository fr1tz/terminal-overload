// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SIMPERSISTSET_H_
#define _SIMPERSISTSET_H_

#ifndef _SIMSET_H_
   #include "console/simSet.h"
#endif


/// A SimSet that can be safely persisted.  Uses SimPersistIDs to reference
/// objects in the set while persisted on disk.  This allows the set to resolve
/// its references no matter whether they are loaded before or after the set
/// is created.
///
class SimPersistSet : public SimSet
{
   public:
   
      typedef SimSet Parent;
      
   protected:
   
      /// List of unresolved persistent IDs.
      Vector< SimPersistID* > mUnresolvedPIDs;
      
      /// If true, the set is currently resolving persistent IDs.
      bool mIsResolvingPIDs;

   public:
   
      ///
      SimPersistSet();
   
      /// Try to resolve all persistent IDs that as of yet are still unresolved.
      void resolvePIDs();

      // SimSet.
      virtual void addObject( SimObject* );
      virtual void write( Stream &stream, U32 tabStop, U32 flags = 0 );
      virtual bool processArguments( S32 argc, const char** argv );
      
      DECLARE_CONOBJECT( SimPersistSet );
      DECLARE_CATEGORY( "Console" );
      DECLARE_DESCRIPTION( "A SimSet that can be safely persisted." );
};

#endif // !_SIMPERSISTSET_H_
