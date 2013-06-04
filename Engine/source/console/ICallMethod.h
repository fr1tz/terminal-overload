// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ICALLMETHOD_H_
#define _ICALLMETHOD_H_

class ICallMethod
{
public:
   virtual const char* callMethod( S32 argc, const char* methodName, ... ) = 0;
   virtual const char* callMethodArgList( U32 argc, const char *argv[], bool callThis = true ) = 0;
};

#endif