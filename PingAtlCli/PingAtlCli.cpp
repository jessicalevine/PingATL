// PingCli.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <atlsafe.h>

void DisplayStatus(wchar_t *pwszMsg, HRESULT hr)
{

	if (hr == S_OK) {
		wprintf(TEXT("%s\n"), pwszMsg);
		return;
	}

	if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS) {
		hr = HRESULT_CODE(hr);
	}

	wchar_t *pwszStatus;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&pwszStatus,
		0,
		NULL);

	wprintf(TEXT("%s: %s (ECode: %lx)\n"), pwszMsg, pwszStatus, hr);

	LocalFree(pwszStatus);
}


int main() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (SUCCEEDED(hr)) {
		IPingable * ptrPingable;
		HRESULT hr = CoCreateInstance(CLSID_CoPingEngine, NULL, CLSCTX_LOCAL_SERVER, IID_IPingable, reinterpret_cast<void**>(&ptrPingable));
		if (SUCCEEDED(hr)) {
			ptrPingable->Initialize();

			StatusResponse status;
			ptrPingable->Ping(12345, &status);
			printf("Status for ping code 12345: %d %S\n", status.Code, status.Description);
			ptrPingable->Ping(777, &status);
			printf("Status for ping code 777: %d %S\n", status.Code, status.Description);
			ptrPingable->Ping(1800, &status);
			printf("Status for ping code 1800: %d %S\n", status.Code, status.Description);

			CComVariant history;
			hr = ptrPingable->RetrieveHistory(&history);

			if (SUCCEEDED(hr)) {
				if (history.vt == (VT_ARRAY | VT_I2)) {
					printf("Ping code history for server: ");

					CComSafeArray<SHORT> codes = history.parray;

					int codeCount = codes.GetCount();
					for (int i = 0; i < codeCount; i++) {
						printf("%hd ", codes[i]);
					}
					printf("\n");
					codes.Destroy();
				}
				else {
					printf("Incorrect variant type\n");
				}
			}
			else {
				DisplayStatus(TEXT("RetrieveHistory failed: "), hr);
			}

			SysFreeString(status.Description);
			ptrPingable->Release();
		}
		else {
			DisplayStatus(TEXT("CoCreateInstance(CoPingEngine) failed: "), hr);
		}
		CoUninitialize();
	}
	else {
		DisplayStatus(TEXT("CoInitializeEx failed: "), hr);
	}


	return 0;
}