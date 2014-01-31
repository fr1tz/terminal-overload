// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#pragma once

#include "stdafx.h"
#include <vector>
#include <string>

// "Platform" window specifics to keep IE plugin consistent with Safari/Firefox/Chrome

class WebGameWindow : public CWindowImpl<WebGameWindow>
{
public:
	WebGameWindow();
	virtual ~WebGameWindow();

	DECLARE_WND_CLASS(_T("WebGameCtrl:WebGameWindow"))

	BEGIN_MSG_MAP(WebGameWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate);
		MESSAGE_HANDLER(WM_SIZE, OnSize);
	END_MSG_MAP()

public:

   // message handlers (all window based)
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected: 

   // // checks a given domain against the allowed domains in webConfig.h (defined in IEWebGamePlugin)
	virtual bool checkDomain() = 0;

private:

	bool mTimer;
	bool mInitialized;

};

