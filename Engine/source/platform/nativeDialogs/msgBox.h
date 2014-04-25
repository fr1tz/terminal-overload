// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MSGBOX_H_
#define _MSGBOX_H_


// [tom, 10/17/2006] Note: If you change either of these enums, make sure you
// update the relevant code in the all the platform layers.

// [pauls, 3/20/2007] Reduced the available types of dialog boxes in order to
// maintain a consistent but platform - appropriate look and feel in Torque.

enum MBButtons
{
   MBOk,
   MBOkCancel,
   MBRetryCancel,
   MBSaveDontSave,
   MBSaveDontSaveCancel,
   MBAlertAssert
};

enum MBIcons
{
   MIWarning,
   MIInformation,
   MIQuestion,
   MIStop,
};

enum MBReturnVal
{
   MROk = 1,   // Start from 1 to allow use of 0 for errors
   MRCancel,
   MRRetry,
   MRDontSave,
};



extern void initMessageBoxVars();

#endif // _MSGBOX_H_
