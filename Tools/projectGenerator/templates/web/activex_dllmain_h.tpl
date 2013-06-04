// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// dllmain.h : Declaration of module class.

class CIEWebGamePluginModule : public CAtlDllModuleT< CIEWebGamePluginModule >
{
public :
	DECLARE_LIBID(LIBID___WEBGAME_PLUGINNAME__Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_IEWEBGAMEPLUGIN, "{__REGISTRY_APPID_RESOURCEID__}")
};

extern class CIEWebGamePluginModule _AtlModule;
