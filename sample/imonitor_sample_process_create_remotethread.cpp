//******************************************************************************
/*++
	Description:

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGThreadCreate)
			return;

		cxMSGThreadCreate* msg = (cxMSGThreadCreate*)Message;

		if (msg->RemoteThread()) {
			//
			// 进程刚才创建的时候，父进程也会创建远程线程，自行过滤
			//
			printf("found remote thread : %S -> %S\n", msg->CurrentProcessPath(), msg->Path());
		}
	}
};
//******************************************************************************
int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGThreadCreate] = emMSGConfigPost;
	manager.InControl(config);

	WaitForExit("监控远程线程");

	return 0;
}
//******************************************************************************
