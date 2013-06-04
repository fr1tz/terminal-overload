// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/strings/stringFunctions.h"
#include "core/module.h"
#include "console/console.h"
#include "console/engineAPI.h"
#include "platform/nativeDialogs/msgBox.h"


DefineEnumType( MBButtons );
DefineEnumType( MBIcons );
DefineEnumType( MBReturnVal );


static const MBReturnVal gsOK = MROk;
static const MBReturnVal gsCancel = MRCancel;
static const MBReturnVal gsRetry = MRRetry;
static const MBReturnVal gsDontSave = MRDontSave;

AFTER_MODULE_INIT( Sim )
{
   #if !defined( _XBOX ) && !defined( TORQUE_DEDICATED )
   Con::addConstant( "$MROk", TypeS32, &gsOK, "Determines the ok button press state in a message box.\n"
	   "@ingroup Platform" );
   Con::addConstant( "$MRCancel", TypeS32, &gsCancel, "Determines the cancel button press state in a message box.\n"
	   "@ingroup Platform" );
   Con::addConstant( "$MRRetry", TypeS32, &gsRetry, "Determines the retry button press state in a message box.\n"
	   "@ingroup Platform");
   Con::addConstant( "$MRDontSave", TypeS32, &gsDontSave, "Determines the don't save button press state in a message box.\n"
	   "@ingroup Platform" );
   #endif
}


//-----------------------------------------------------------------------------

ImplementEnumType( MBButtons,
   "Which buttons to display on a message box.\n\n"
   "@ingroup Platform" )
   { MBOk,                 "Ok" },
   { MBOkCancel,           "OkCancel" },
   { MBRetryCancel,        "RetryCancel" },
   { MBSaveDontSave,       "SaveDontSave" }, // maps to yes/no on win, to save/discard on mac.
   { MBSaveDontSaveCancel, "SaveDontSaveCancel" }, // maps to yes/no/cancel on win, to save/cancel/don'tsave on mac.
EndImplementEnumType;

ImplementEnumType( MBIcons,
   "What icon to show on a message box.\n\n"
   "@ingroup Platform" )
   { MIInformation,        "Information" },// win: blue i, mac: app icon or talking head
   { MIWarning,            "Warning" },    // win & mac: yellow triangle with exclamation pt
   { MIStop,               "Stop" },       // win: red x, mac: app icon or stop icon, depending on version
   { MIQuestion,           "Question" },   // win: blue ?, mac: app icon
EndImplementEnumType;

ImplementEnumType( MBReturnVal,
   "Return value for messageBox() indicating which button was pressed by the user.\n\n"
   "@ingroup Platform" )
   { MROk, "OK" },
   { MRCancel, "Cancelled" },
   { MRRetry, "Retry" },
   { MRDontSave, "DontSave" }
EndImplementEnumType;


//-----------------------------------------------------------------------------

DefineEngineFunction( messageBox, S32, ( const char* title, const char* message, MBButtons buttons, MBIcons icons ), ( MBOkCancel, MIInformation ),
   "Display a modal message box using the platform's native message box implementation.\n\n"
   "@param title The title to display on the message box window.\n"
   "@param message The text message to display in the box.\n"
   "@param buttons Which buttons to put on the message box.\n"
   "@param icons Which icon to show next to the message.\n"
   "@return One of $MROK, $MRCancel, $MRRetry, and $MRDontSave identifying the button that the user pressed.\n"
   "@tsexample\n"
      "messageBox( \"Error\", \"\" );\n" //TODO
   "@endtsexample\n\n"
   "@ingroup Platform" )
{
   return Platform::messageBox( title, message, buttons, icons );
}
