// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _STRINGUNIT_H_
#define _STRINGUNIT_H_

#include "platform/types.h"

/// These functions are used for chunking up strings by delimiter.
/// Especially useful for handling TorqueScript space-delimited fields
namespace StringUnit
{
   const char *getUnit(const char *string, U32 index, const char *set, char* buffer = 0, U32 bufferSize = 0);
   const char *getUnits(const char *string, S32 startIndex, S32 endIndex, const char *set);
   U32 getUnitCount(const char *string, const char *set);
   const char* setUnit(const char *string, U32 index, const char *replace, const char *set);
   const char* removeUnit(const char *string, U32 index, const char *set);
};

#endif