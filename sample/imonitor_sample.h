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
		printf("============= 注意 ===============\n");
		printf("驱动加载需要签名，测试前请先签名。\n");
		printf("如果没有正式的签名证书，可以使用测试签名，详细参考：\n");
		printf("1. 开启测试模式： https://docs.microsoft.com/zh-cn/windows-hardware/drivers/install/the-testsigning-boot-configuration-option\n");
		printf("2. 对启动进行签名： https://docs.microsoft.com/zh-cn/windows-hardware/drivers/install/test-signing-a-driver-file\n");
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
