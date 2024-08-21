//******************************************************************************
/*++
	Description:

	快速过滤示例：
		只监控53端口的UDP发送数据

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		printf("%S ==> %S\n", Message->GetTypeName(), Message->GetFormatedString(emMSGFieldCurrentProcessPath));

		for (ULONG i = emMSGFieldCurrentProcessCommandline; i < Message->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", Message->GetFieldName(i), Message->GetFormatedString(i));
		}
	}
};
//******************************************************************************
int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	CheckSignError(hr);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGWFPSendTo] = emMSGConfigPost;
	manager.InControl(config);

	cxMSGUserGetGlobalFilter filter;
	filter.SendToPorts.Count = 1;
	filter.SendToPorts.Port[0] = 0x3500; // 53
	manager.InControl(filter);

	WaitForExit("只监控53端口的UDP发送数据");

	return 0;
}
//******************************************************************************
