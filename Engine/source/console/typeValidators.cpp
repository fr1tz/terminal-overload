// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "console/console.h"
#include "console/consoleObject.h"
#include "console/typeValidators.h"
#include "console/simBase.h"
#include "math/mPoint3.h"
#include <stdarg.h>

void TypeValidator::consoleError(SimObject *object, const char *format, ...)
{
   char buffer[1024];
   va_list argptr;
   va_start(argptr, format);
   dVsprintf(buffer, sizeof(buffer), format, argptr);
   va_end(argptr);

   AbstractClassRep *rep = object->getClassRep();
   AbstractClassRep::Field &fld = rep->mFieldList[fieldIndex];
   const char *objectName = object->getName();
   if(!objectName)
      objectName = "unnamed";


   Con::warnf("%s - %s(%d) - invalid value for %s: %s",
      rep->getClassName(), objectName, object->getId(), fld.pFieldname, buffer);
}

void FRangeValidator::validateType(SimObject *object, void *typePtr)
{
	F32 *v = (F32 *) typePtr;
	if(*v < minV || *v > maxV)
	{
		consoleError(object, "Must be between %g and %g", minV, maxV);
		if(*v < minV)
			*v = minV;
		else if(*v > maxV)
			*v = maxV;
	}
}

void IRangeValidator::validateType(SimObject *object, void *typePtr)
{
	S32 *v = (S32 *) typePtr;
	if(*v < minV || *v > maxV)
	{
		consoleError(object, "Must be between %d and %d", minV, maxV);
		if(*v < minV)
			*v = minV;
		else if(*v > maxV)
			*v = maxV;
	}
}

void IRangeValidatorScaled::validateType(SimObject *object, void *typePtr)
{
	S32 *v = (S32 *) typePtr;
	*v /= factor;
	if(*v < minV || *v > maxV)
	{
		consoleError(object, "Scaled value must be between %d and %d", minV, maxV);
		if(*v < minV)
			*v = minV;
		else if(*v > maxV)
			*v = maxV;
	}
}

void Point3NormalizeValidator::validateType(SimObject *object, void *typePtr)
{
   Point3F *v = (Point3F *) typePtr;
   const F32 len = v->len();
   if(!mIsEqual(len, 1.0f))
   {
      consoleError(object, "Vector length must be %g", length);
      *v *= length / len;
   }
}

namespace CommonValidators
{
   FRangeValidator PositiveFloat(0.0f, F32_MAX);
   FRangeValidator PositiveNonZeroFloat(F32( POINT_EPSILON ) , F32_MAX);
   FRangeValidator NormalizedFloat(0.0f, 1.0f);
   Point3NormalizeValidator NormalizedPoint3(1.0f);
};

