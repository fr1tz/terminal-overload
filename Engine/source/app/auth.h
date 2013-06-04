// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _AUTH_H_
#define _AUTH_H_

/// Formerly contained a certificate, showing that something was valid.
class Auth2Certificate
{
   U32 xxx;
};

/// Formerly contained data indicating whether a user is valid.
struct AuthInfo
{
   enum {
      MaxNameLen = 31,
   };

   bool valid;
   char name[MaxNameLen + 1];
};

/// Formerly validated the server's authentication info.
inline bool validateAuthenticatedServer()
{
   return true;
}

/// Formerly validated the client's authentication info.
inline bool validateAuthenticatedClient()
{
   return true;
}

#endif
