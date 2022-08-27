//******************************************************************************
/*++
	FileName:		imonitor_sample.h
	Description:

--*/
//******************************************************************************
#ifndef __imonitor_sample_0E0533C1_62F5_4052_94C4_D07EF8A9AD82__
#define __imonitor_sample_0E0533C1_62F5_4052_94C4_D07EF8A9AD82__
//******************************************************************************
#include <iMonitorSDK.h>
#include <iMonitorProtocol.h>
#include <stdio.h>
//******************************************************************************
inline void CheckSignError(HRESULT hr)
{
	if (hr == HRESULT_FROM_WIN32(ERROR_INVALID_IMAGE_HASH)) {
		printf("============= Attention ===============\n");
		printf("Driver loading requires signature, please sign before testing.\n");
		printf("If you don't have an official signing certificate, you can use test signing.\n");
		printf("For test signing details, refer to the bin\\test_signed directory.\n");
		printf("More information can be obtained through the https://iMonitorSDK.com/docs/sign \n");
		printf("================================\n");
		system("PAUSE");
	}
}
//******************************************************************************
inline void WaitForExit(const char* message)
{
	printf("%s\n", message);

	system("PAUSE");
}
//******************************************************************************
#endif
