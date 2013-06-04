// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCRIPTFILENAME_H_
#define _SCRIPTFILENAME_H_

namespace Con
{

extern void setScriptPathExpando(const char *expando, const char *path, bool toolsOnly = false);
extern void removeScriptPathExpando(const char *expando);
extern bool isScriptPathExpando(const char *expando);

} // end namespace Con

#endif // _SCRIPTFILENAME_H_
