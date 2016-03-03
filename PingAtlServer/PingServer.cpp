// PingServer.cpp : Implementation of CPingServer

#include "stdafx.h"
#include "PingServer.h"


// CPingServer



STDMETHODIMP CPingServer::Initialize()
{
	printf("CoPingEngine initialized\n");
	return S_OK;
}


STDMETHODIMP CPingServer::Ping(SHORT pingCode, StatusResponse* status)
{
	if (pingCode == 12345) {
		status->Description = SysAllocString(TEXT("OK"));
		status->Code = 200;
	}
	else {
		status->Description = SysAllocString(TEXT("Unauthorized"));
		status->Code = 401;
	}

	return S_OK;
}
