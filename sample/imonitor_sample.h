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
		printf("���԰汾��������û��ǩ�������Կ���ʹ�ÿ�������ǩ���ķ�ʽ�����ԣ������Լ�ʹ��֤��ǩ����\n");
		printf("��ϸ���Բο���https://trustsing.com/imonitorsdk/sign \n");
		printf("================================\n");
		system("PAUSE");
	} else if (hr == S_OK) {
		printf("============= Attention ===============\n");
		printf("Start success in test mode�� the SDK will expire after one hour of running, please restart the process after expired.\n");
		printf("�����ɹ�����ǰ���ڲ���ģʽ�����ܽ�������һ��Сʱ��ʧЧ��ʧЧ���������������̡�\n");
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
