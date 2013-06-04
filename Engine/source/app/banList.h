// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BANLIST_H_
#define _BANLIST_H_

#ifndef _ENGINEAPI_H_
   #include "console/engineAPI.h"
#endif
#ifndef _TVECTOR_H_
   #include "core/util/tVector.h"
#endif

/// Helper class to keep track of bans.
class BanList
{
   public:
   
      DECLARE_STATIC_CLASS( BanList );
   
      struct BanInfo
      {
         S32      uniqueId;
         char     transportAddress[128];
         S32      bannedUntil;
      };
      
   protected:

      Vector< BanInfo > list;
      
      static BanList* smInstance;

   public:

      BanList();
      
      static BanList* instance() { return smInstance; }

      void addBan(S32 uniqueId, const char *TA, S32 banTime);
      void addBanRelative(S32 uniqueId, const char *TA, S32 numSeconds);
      void removeBan(S32 uniqueId, const char *TA);
      bool isBanned(S32 uniqueId, const char *TA);
      bool isTAEq(const char *bannedTA, const char *TA);
      void exportToFile(const char *fileName);
};

#endif
