//******************************************************************************
/*++
	Description:

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
MonitorManager manager;
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGExtensionDnsQuery)
			return;

		CComPtr<IMonitorProcess> process;
		manager.FindProcess(Message->GetHeader()->RpcCallerProcessId, &process);

		if (process) {
			printf("[rpc call from] ==> %S\n", process->GetProcessPath());
		}

		printf("%S ==> %S\n", Message->GetTypeName(), Message->GetFormatedString(emMSGFieldCurrentProcessPath));

		for (ULONG i = emMSGFieldCurrentProcessCommandline; i < Message->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", Message->GetFieldName(i), Message->GetFormatedString(i));
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

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGExtensionDnsQuery] = emMSGConfigPost | emMSGConfigFetchSystemRpcCaller;
	manager.InControl(config);

	WaitForExit("DNSÇëÇó¼à¿Ø");

	return 0;
}
//******************************************************************************
