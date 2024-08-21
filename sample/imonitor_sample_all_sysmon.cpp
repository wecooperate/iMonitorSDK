//******************************************************************************
/*++
	Description:
	
	打印监控到的所有事件信息，输出如下：

ProcessOpen ==> C:\Windows\System32\conhost.exe
             CurrentProcessCommandline : \??\C:\Windows\system32\conhost.exe
                                  Path : F:\Git\iMonitor\bin\Debug\imonitor_sample_all_sysmon.exe
                             ProcessId : 31912
                       ParentProcessId : 23424
                         DesiredAccess : 4096
                             Duplicate : false

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* msg) override
	{
		printf("%S ==> %S\n", msg->GetTypeName(), msg->GetFormatedString(emMSGFieldCurrentProcessPath));

		for (ULONG i = emMSGFieldCurrentProcessCommandline; i < msg->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", msg->GetFieldName(i), msg->GetFormatedString(i));
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
	for (int i = 0; i < emMSGMax; i++) {
		config.Config[i] = emMSGConfigPost;
	}
	manager.InControl(config);

	WaitForExit("");

	return 0;
}
//******************************************************************************
