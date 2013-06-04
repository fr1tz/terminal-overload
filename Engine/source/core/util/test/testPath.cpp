// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "unit/test.h"
#include "core/util/path.h"

using namespace UnitTesting;

#define TEST( x ) test( ( x ), "FAIL: " #x )

CreateUnitTest(TestPathMakeRelativePath, "Core/Util/Path/MakeRelativePath")
{
   void run()
   {      
      TEST(Torque::Path::MakeRelativePath("art/interiors/burg/file.png", "art/interiors/") == "burg/file.png"); 
      TEST(Torque::Path::MakeRelativePath("art/interiors/file.png", "art/interiors/burg/") == "../file.png");
      TEST(Torque::Path::MakeRelativePath("art/file.png", "art/interiors/burg/") == "../../file.png");
      TEST(Torque::Path::MakeRelativePath("file.png", "art/interiors/burg/") == "../../../file.png");
      TEST(Torque::Path::MakeRelativePath("art/interiors/burg/file.png", "art/interiors/burg/") == "file.png");
      TEST(Torque::Path::MakeRelativePath("art/interiors/camp/file.png", "art/interiors/burg/") == "../camp/file.png");
      TEST(Torque::Path::MakeRelativePath("art/interiors/burg/file.png", "art/shapes/") == "../interiors/burg/file.png");
      TEST(Torque::Path::MakeRelativePath("levels/den/file.png", "art/interiors/burg/") == "../../../levels/den/file.png");
      TEST(Torque::Path::MakeRelativePath("art/interiors/burg/file.png", "art/dts/burg/") == "../../interiors/burg/file.png");
   }
};
