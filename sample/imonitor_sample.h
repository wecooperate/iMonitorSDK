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
//******************************************************************************
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <string>
//******************************************************************************
#include "nlohmann/json.hpp"
//******************************************************************************
inline void CheckSignError(HRESULT hr)
{
	if (hr == HRESULT_FROM_WIN32(ERROR_INVALID_IMAGE_HASH)) {
		printf("============= Attention ===============\n");
		printf("Driver loading requires signature, please sign before testing.\n");
		printf("If you don't have an official signing certificate, you can use test signing.\n");
		printf("For test signing details, refer to the bin\\test_signed directory.\n");
		printf("More information can be obtained through the https://trustsing.com/imonitorsdk/sign \n");
		printf("测试版本带的驱动没有签名，测试可以使用开启测试签名的方式来测试，或者自己使用证书签名。\n");
		printf("详细可以参考：https://trustsing.com/imonitorsdk/sign \n");
		printf("================================\n");
		system("PAUSE");
	} else if (hr == S_OK) {
		printf("============= Attention ===============\n");
		printf("Start success in test mode， the SDK will expire after one hour of running, please restart the process after expired.\n");
		printf("启动成功，当前处于测试模式，功能将在运行一个小时后失效，失效后请自行重启进程。\n");
		printf("================================\n\n");
	}
}
//******************************************************************************
inline void WaitForExit(const char* message)
{
	printf("%s\n\n", message);

	system("PAUSE");
}
//******************************************************************************
inline std::string UTF8StringToDriverString(const std::string& str)
{
	return (const char*)CW2A((const wchar_t*)CA2W(str.c_str(), CP_UTF8));
}
//******************************************************************************
#endif
