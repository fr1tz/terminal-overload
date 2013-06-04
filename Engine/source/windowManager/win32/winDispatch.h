// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _WINDOWMANAGER_WIN32_WINDISPATCH_H_
#define _WINDOWMANAGER_WIN32_WINDISPATCH_H_

//
// *** This header requires that Window.h be included before this.
//

/// Some events must be processed immediately, and others can or should be
/// processed later. This enum allows us to distinguish between the two
/// types.
enum DispatchType {
   DelayedDispatch,
   ImmediateDispatch,
};

/// Dispatch the event into the journaling system.
///
/// Dispatch Win32 events into the journaling system. To avoid problems
/// with journaling, events should normally use the DelayedDispatch type.
///
/// Delayed events are pushed onto a queue for later processing by DispatchNext().
void Dispatch(DispatchType,HWND hWnd,UINT message,WPARAM wparam,WPARAM lparam);

/// Remove messages from the event queue, matching a msg value range or hWnd
///
/// If no filter is specified, either HWND or MessageRange, nothing will be removed
/// You may not match HWND and MsgRange both, currently.
///
/// Message Range is calculated as follows.
/// @li Both Begin and End are specified as message values, ex WM_MOUSEMOVE
/// @li Specifying an identical set of begin/end will remove all messages matching that message value (WM_MOUSEMOVE)
/// @li If you specify a range it will remove from that beginning value through the end value
/// 
/// @note : The range is useful because on windows messages declared such that you can filter a block of
///  messages just by specifying the beginning value and end.  
///  ex. WM_MOUSEFIRST,WM_MOUSELAST range will match all mouse messages.

/// 
/// @param hWnd The HWND to filter by, this cannot be combined with a msg range filter currently
/// @param msgBegin The beginning msg value to filter from
/// @param msgEnd The ending msg value to filter to
void RemoveMessages(HWND hWnd,UINT msgBegin,UINT msgEnd );

/// Dispatch the next event in the delayed dispatch queue.
/// This function should be called outside of any journaled calls.
/// Returns true if an event was dispatched.
bool DispatchNext();

/// Remove events related to the window from the dispatch queue.
void DispatchRemove(HWND hWnd);

#endif