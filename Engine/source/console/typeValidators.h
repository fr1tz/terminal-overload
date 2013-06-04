// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TYPEVALIDATORS_H_
#define _TYPEVALIDATORS_H_

class TypeValidator
{
   public:
   S32 fieldIndex;

   /// Prints a console error message for the validator.
   ///
   /// The message is prefaced with with:
   /// @code
   /// className objectName (objectId) - invalid value for fieldName: msg
   /// @endcode
   void consoleError(SimObject *object, const char *format, ...);

   /// validateType is called for each assigned value on the field this
   /// validator is attached to.
   virtual void validateType(SimObject *object, void *typePtr) = 0;
};


/// Floating point min/max range validator
class FRangeValidator : public TypeValidator
{
   F32 minV, maxV;
public:
   FRangeValidator(F32 minValue, F32 maxValue)
   {
      minV = minValue;
      maxV = maxValue;
   }
   void validateType(SimObject *object, void *typePtr);
};

/// Signed integer min/max range validator
class IRangeValidator : public TypeValidator
{
   S32 minV, maxV;
public:
   IRangeValidator(S32 minValue, S32 maxValue)
   {
      minV = minValue;
      maxV = maxValue;
   }
   void validateType(SimObject *object, void *typePtr);
};

/// Scaled integer field validator
///
/// @note This should NOT be used on a field that gets exported -
/// the field is only validated once on initial assignment
class IRangeValidatorScaled : public TypeValidator
{
   S32 minV, maxV;
   S32 factor;
public:
   IRangeValidatorScaled(S32 scaleFactor, S32 minValueScaled, S32 maxValueScaled)
   {
      minV = minValueScaled;
      maxV = maxValueScaled;
      factor = scaleFactor;
   }
   void validateType(SimObject *object, void *typePtr);
};

/// Vector normalization validator
class Point3NormalizeValidator : public TypeValidator
{
   F32 length;
public:
   Point3NormalizeValidator(F32 normalizeLength = 1.0f) : length(normalizeLength) { }
   void validateType(SimObject *object, void *typePtr);
};

namespace CommonValidators
{
   // Floats
   extern FRangeValidator PositiveFloat;
   extern FRangeValidator PositiveNonZeroFloat;
   extern FRangeValidator NormalizedFloat;

   // Other Math Types
   extern Point3NormalizeValidator NormalizedPoint3;
};

#endif
