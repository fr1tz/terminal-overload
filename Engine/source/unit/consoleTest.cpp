// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/strings/stringFunctions.h"

#include "unit/test.h"
#include "console/console.h"

using namespace UnitTesting;

ConsoleFunction(unitTest_runTests, void, 1, 3, "([searchString[, bool skipInteractive]])"
				"@brief Run unit tests, or just the tests that prefix match against the searchString.\n\n"
				"@ingroup Console")
{
   const char *searchString = (argc > 1 ? argv[1] : "");
   bool skip = (argc > 2 ? dAtob(argv[2]) : false);

   TestRun tr;
   tr.test(searchString, skip);
}