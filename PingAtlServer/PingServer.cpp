// PingServer.cpp : Implementation of CPingServer

#include "stdafx.h"
#include "PingServer.h"


// CPingServer



STDMETHODIMP CPingServer::Initialize()
{
	printf("CoPingEngine initialized\n");
	return S_OK;
}


STDMETHODIMP CPingServer::Ping(SHORT pingCode, SHORT* statusCode)
{
	if (pingCode == 12345) {
		*statusCode = 200;
	}
	else {
		*statusCode = 401;
	}

	return S_OK;
}
