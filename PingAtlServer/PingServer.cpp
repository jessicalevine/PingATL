// PingServer.cpp : Implementation of CPingServer


#include "stdafx.h"
#include "PingServer.h"

#define INITIAL_HISTORY_LENGTH 16

// CPingServer
CPingServer::CPingServer() : m_lHistoryIndex(0) {
	m_asiReceivedCodes = CComSafeArray<SHORT>(INITIAL_HISTORY_LENGTH, 0);
}

CPingServer::~CPingServer() {
	m_asiReceivedCodes.Destroy();
}


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

	RecordPing(pingCode);

	return S_OK;
}

STDMETHODIMP CPingServer::RetrieveHistory(VARIANT * pingHistory) {
	VariantInit(pingHistory);
	CComVariant historyVariant = CComVariant(m_asiReceivedCodes);

	// Resize the output array to only include used indices
	SAFEARRAYBOUND historySize = { (ULONG) m_lHistoryIndex, 0 };
	SafeArrayRedim(historyVariant.parray, &historySize);

	historyVariant.Detach(pingHistory);
	return S_OK;
}


void CPingServer::RecordPing(SHORT pingCode) {
	m_asiReceivedCodes[m_lHistoryIndex] = pingCode;

	m_lHistoryIndex++;
	if (m_lHistoryIndex == m_asiReceivedCodes.GetUpperBound()) {
		m_asiReceivedCodes.Resize(m_lHistoryIndex * 2, 0);
	}
}