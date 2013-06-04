// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/engineStructs.h"
#include "console/engineAPI.h"
#include "core/util/tVector.h"
#include "core/util/uuid.h"
#include "core/color.h"


IMPLEMENT_STRUCT( Vector< bool >,
   BoolVector,,
   "" )
END_IMPLEMENT_STRUCT;


IMPLEMENT_STRUCT( Vector< S32 >,
   IntVector,,
   "" )
END_IMPLEMENT_STRUCT;


IMPLEMENT_STRUCT( Vector< F32 >,
   FloatVector,,
   "" )
END_IMPLEMENT_STRUCT;


IMPLEMENT_STRUCT( Torque::UUID,
   UUID,,
   "" )
END_IMPLEMENT_STRUCT;


IMPLEMENT_STRUCT( ColorI,
   ColorI,,
   "RGBA color quadruple in 8bit integer precision per channel." )
   
   FIELD( red, red, 1, "Red channel value." )
   FIELD( green, green, 1, "Green channel value." )
   FIELD( blue, blue, 1, "Blue channel value." )
   FIELD( alpha, alpha, 1, "Alpha channel value." )
   
END_IMPLEMENT_STRUCT;


IMPLEMENT_STRUCT( ColorF,
   ColorF,,
   "RGBA color quadruple in 32bit floating-point precision per channel." )

   FIELD( red, red, 1, "Red channel value." )
   FIELD( green, green, 1, "Green channel value." )
   FIELD( blue, blue, 1, "Blue channel value." )
   FIELD( alpha, alpha, 1, "Alpha channel value." )

END_IMPLEMENT_STRUCT;
