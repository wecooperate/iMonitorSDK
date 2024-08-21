//******************************************************************************
/*++
	Description:

	Rpc、DCOM调用溯源示例：
		可以跟踪到Rpc、DCOM调用的进程

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
MonitorManager manager;
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* msg) override
	{
		if (msg->GetHeader()->RpcCallerProcessId == 0)
			return;

		CComPtr<IMonitorProcess> process;
		manager.FindProcess(msg->GetHeader()->RpcCallerProcessId, &process);

		if (!process)
			return;

		printf("%S ==> %S\n", msg->GetTypeName(), msg->GetFormatedString(emMSGFieldCurrentProcessPath));
		printf("[rpc call from] ==> %S\n", process->GetProcessPath());

		for (ULONG i = emMSGFieldCurrentProcessCommandline; i < msg->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", msg->GetFieldName(i), msg->GetFormatedString(i));
		}
	}
};
//******************************************************************************
int main()
{
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	CheckSignError(hr);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	cxMSGUserSetMSGConfig config;
	for (int i = 0; i < emMSGMax; i++) {
		config.Config[i] = emMSGConfigPost | emMSGConfigFetchRpcCaller;
	}
	manager.InControl(config);

	WaitForExit("可以跟踪到Rpc、DCOM调用的进程");

	return 0;
}
//******************************************************************************
