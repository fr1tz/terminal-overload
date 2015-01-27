// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "tResponseCurve.h"
#include "console/engineAPI.h"

IMPLEMENT_CONOBJECT( SimResponseCurve );

ConsoleDocClass( SimResponseCurve,
				"@brief A ResponseCurve<F32> wrapped as a SimObject.\n\n"
				"Currently no applied use, not network ready, not intended "
				"for game development, for editors or internal use only.\n\n "
				"@internal");

SimResponseCurve::SimResponseCurve()
{

}

bool SimResponseCurve::onAdd()
{
   if ( !Parent::onAdd() )
      return false;

   return true;
}

void SimResponseCurve::onRemove()
{
   Parent::onRemove();
}

void SimResponseCurve::addPoint(F32 value, F32 time)
{
   mCurve.addPoint( value, time );
}

F32 SimResponseCurve::getValue(F32 time)
{
   return mCurve.getVal( time );
}

void SimResponseCurve::clear()
{
   mCurve.clear();
}

DefineConsoleMethod( SimResponseCurve, addPoint, void, ( F32 value, F32 time ), , "addPoint( F32 value, F32 time )" )
{
   object->addPoint( value, time );
}

DefineConsoleMethod( SimResponseCurve, getValue, F32, ( F32 time ), , "getValue( F32 time )" )
{
   return object->getValue( time );
}

DefineConsoleMethod( SimResponseCurve, clear, void, (), , "clear()" )
{
   object->clear();
}