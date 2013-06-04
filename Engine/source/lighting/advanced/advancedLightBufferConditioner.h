// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _ADVANCED_LIGHTBUFFER_CONDITIONER_H_
#define _ADVANCED_LIGHTBUFFER_CONDITIONER_H_

#ifndef _CONDITIONER_BASE_H_
#include "shaderGen/conditionerFeature.h"
#endif


class AdvancedLightBufferConditioner : public ConditionerFeature
{
   typedef ConditionerFeature Parent;

public:
   enum ColorFormat
   {
      RGB,
      LUV
   };

public:

   AdvancedLightBufferConditioner(const GFXFormat bufferFormat, const ColorFormat colorFormat) 
      : Parent(bufferFormat), mColorFormat(colorFormat)
   {

   }

   virtual ~AdvancedLightBufferConditioner();

   virtual String getName()
   {
      return String("Light Buffer Conditioner ") + String( mColorFormat == RGB ? "[RGB]" : "[LUV]" );
   }

protected:
   ColorFormat mColorFormat;

   virtual Var *_conditionOutput( Var *unconditionedOutput, MultiLine *meta );
   virtual Var *_unconditionInput( Var *conditionedInput, MultiLine *meta );
   virtual Var *printMethodHeader( MethodType methodType, const String &methodName, Stream &stream, MultiLine *meta );
   virtual void printMethodFooter( MethodType methodType, Var *retVar, Stream &stream, MultiLine *meta );
};

#endif // _ADVANCED_LIGHTBUFFER_CONDITIONER_H_