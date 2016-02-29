// PingAtlServer.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "PingAtlServer_i.h"


using namespace ATL;


class CPingAtlServerModule : public ATL::CAtlExeModuleT< CPingAtlServerModule >
{
public :
	DECLARE_LIBID(LIBID_PingAtlServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PINGATLSERVER, "{5477D4B3-F406-41E3-94B5-0724B1621D37}")
	};

CPingAtlServerModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

