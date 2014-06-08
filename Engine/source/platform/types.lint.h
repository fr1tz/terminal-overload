// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef TORQUE_TYPES_LINT_H_
#define TORQUE_TYPES_LINT_H_

typedef signed long long S64;
typedef unsigned long long U64;

typedef unsigned int dsize_t;

struct FileTime
{
   U32 v1;
   U32 v2;
};

#define TORQUE_OS_STRING "Lint"
#define TORQUE_CPU_STRING "x86"
#define TORQUE_LITTLE_ENDIAN
#define TORQUE_SUPPORTS_NASM
#define TORQUE_SUPPORTS_VC_INLINE_X86_ASM
#define TORQUE_OS_WIN
#define TORQUE_COMPILER_VISUALC 1500

#ifndef FN_CDECL
#define FN_CDECL
#endif

#ifndef Offset
#define Offset(x, cls) _Offset_Normal(x, cls)
#define OffsetNonConst(x, cls) _Offset_Normal(x, cls)
#endif

#ifndef NULL
#define NULL 0
#endif

#endif
