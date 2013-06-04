// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _DYNAMIC_CONSOLEMETHOD_COMPONENT_H_
#define _DYNAMIC_CONSOLEMETHOD_COMPONENT_H_

#ifndef _SIMCOMPONENT_H_
#include "component/simComponent.h"
#endif

#ifndef _CONSOLEINTERNAL_H_
#include "console/consoleInternal.h"
#endif

#ifndef _ICALLMETHOD_H_
#include "console/ICallMethod.h"
#endif

#ifdef TORQUE_DEBUG
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#endif

//-----------------------------------------------------------------------------

class DynamicConsoleMethodComponent : public SimComponent, public ICallMethod
{
#ifdef TORQUE_DEBUG
public:
   typedef Map<StringTableEntry, S32> callMethodMetricType;
#endif

private:
   typedef SimComponent Parent;

#ifdef TORQUE_DEBUG
   // Call Method Debug Stat.
   callMethodMetricType mCallMethodMetrics;
#endif

protected:
   /// Internal callMethod : Actually does component notification and script method execution
   ///  @attention This method does some magic to the argc argv to make Con::execute act properly
   ///   as such it's internal and should not be exposed or used except by this class
   virtual const char* _callMethod( U32 argc, const char *argv[], bool callThis = true );

public:

#ifdef TORQUE_DEBUG
   /// Call Method Metrics.
   const callMethodMetricType& getCallMethodMetrics( void ) const { return mCallMethodMetrics; };

   /// Inject Method Call.
   void injectMethodCall( const char* method );
#endif

   /// Call Method
   virtual const char* callMethodArgList( U32 argc, const char *argv[], bool callThis = true );

   /// Call Method format string
   const char* callMethod( S32 argc, const char* methodName, ... );

   // query for console method data
   virtual bool handlesConsoleMethod(const char * fname, S32 * routingId);

   DECLARE_CONOBJECT(DynamicConsoleMethodComponent);
};

#endif