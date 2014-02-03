// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "renderInstance/renderPassStateToken.h"
#include "console/consoleTypes.h"

#include "console/engineAPI.h"


IMPLEMENT_CONOBJECT(RenderPassStateToken);

ConsoleDocClass( RenderPassStateToken,
   "@brief Abstract base class for RenderFormatToken, used to manipulate what goes on in the render manager\n\n"

   "You cannot actually instantiate RenderPassToken, only its child: RenderFormatToken. "
   "RenderFormatToken is an implementation which changes the format of the "
   "back buffer and/or the depth buffer.\n\n"
   
   "The RenderPassStateBin manager changes the rendering state associated with "
   "a token it is declared with. In stock Torque 3D, a single example exists in the "
   "way of AL_FormatToken (found in renderManager.cs). In that script file, all the "
   "render managers are intialized, and a single RenderFormatToken is used. This "
   "implementation basically exists to ensure Advanced Lighting works with MSAA.\n\n"

   "@see RenderFormatToken\n"
   "@see RenderPassStateBin\n"
   "@see game/core/scripts/client/renderManager.cs\n"

   "@ingroup RenderBin\n"
);

void RenderPassStateToken::process(SceneRenderState *state, RenderPassStateBin *callingBin)
{
   TORQUE_UNUSED(state);
   TORQUE_UNUSED(callingBin);
   AssertWarn(false, "RenderPassStateToken is an abstract class, you must re-implement process()");
}

void RenderPassStateToken::reset()
{
   AssertWarn(false, "RenderPassStateToken is an abstract class, you must re-implement reset()");
}

void RenderPassStateToken::enable( bool enabled /*= true*/ )
{
   TORQUE_UNUSED(enabled);
   AssertWarn(false, "RenderPassStateToken is an abstract class, you must re-implement enable()");
}

bool RenderPassStateToken::isEnabled() const
{
   AssertWarn(false, "RenderPassStateToken is an abstract class, you must re-implement isEnabled()");
   return false;
}

static bool _set_enable( void *object, const char *index, const char *data )
{
   reinterpret_cast<RenderPassStateToken *>(object)->enable(dAtob(data));
   return false;
}

static const char *_get_enable(void* obj, const char* data)
{
   TORQUE_UNUSED(data);
   return reinterpret_cast<RenderPassStateToken *>(obj)->isEnabled() ? "true" : "false";
}

void RenderPassStateToken::initPersistFields()
{
   addProtectedField("enabled", TypeBool, 0, &_set_enable, &_get_enable, "Enables or disables this token.");
   Parent::initPersistFields();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(RenderPassStateBin);


ConsoleDocClass( RenderPassStateBin,
   "@brief A non-rendering render bin used to enable/disable a RenderPassStateToken.\n\n"

   "This is a utility RenderBinManager which does not render any render instances.  Its only "
   "used to define a point in the render bin order at which a RenderPassStateToken is triggered.\n\n"   

   "@see RenderPassStateToken\n"

   "@ingroup RenderBin\n"
);

RenderPassStateBin::RenderPassStateBin() 
   : Parent()
{
}

RenderPassStateBin::~RenderPassStateBin()
{

}

void RenderPassStateBin::render(SceneRenderState *state)
{
   if(mStateToken.isValid())
      mStateToken->process(state, this);
}

void RenderPassStateBin::clear()
{
   if(mStateToken.isValid())
      mStateToken->reset();
}

void RenderPassStateBin::sort()
{

}

void RenderPassStateBin::initPersistFields()
{
   addProtectedField( "stateToken", TYPEID< RenderPassStateToken >(), Offset( mStateToken, RenderPassStateBin ),
      _setStateToken, _getStateToken );
   
   Parent::initPersistFields();
}

//------------------------------------------------------------------------------

DefineEngineMethod(RenderPassStateToken, enable, void, (),,
   "@brief Enables the token." )
{
   object->enable(true);
}

DefineEngineMethod(RenderPassStateToken, disable, void, (),,
   "@brief Disables the token.")
{
   object->enable(false);
}

DefineEngineMethod(RenderPassStateToken, toggle, void, (),,
   "@brief Toggles the token from enabled to disabled or vice versa." )
{
   object->enable(!object->isEnabled());
}