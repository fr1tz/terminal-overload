// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/stringStack.h"

void StringStack::getArgcArgv(StringTableEntry name, U32 *argc, const char ***in_argv, bool popStackFrame /* = false */)
{
   U32 startStack = mFrameOffsets[mNumFrames-1] + 1;
   U32 argCount   = getMin(mStartStackSize - startStack, (U32)MaxArgs - 1);

   *in_argv = mArgV;
   mArgV[0] = name;
   
   for(U32 i = 0; i < argCount; i++)
      mArgV[i+1] = mBuffer + mStartOffsets[startStack + i];
   argCount++;
   
   *argc = argCount;

   if(popStackFrame)
      popFrame();
}