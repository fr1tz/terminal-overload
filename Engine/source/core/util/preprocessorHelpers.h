// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef TORQUE_CORE_UTIL_PREPROCESSORHELPERS_H_
#define TORQUE_CORE_UTIL_PREPROCESSORHELPERS_H_

/// @defgroup preprocess_helpers Preprocessor Helpers
/// These are some handy preprocessor macros to simplify certain tasks, like
/// preprocessor concatenation that works properly with __LINE__.

#define _TORQUE_CONCAT(x, y) x ## y

/// @ingroup preprocess_helpers
/// This command concatenates two tokens in a way that will work with things such
/// as __LINE__.
/// @hideinitializer
#define TORQUE_CONCAT(x, y) _TORQUE_CONCAT(x, y)

#endif
