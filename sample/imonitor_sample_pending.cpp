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
	void OnCallback(IMonitorMessage* msg) override
	{
		if (msg->GetType() != emMSGProcessCreate)
			return;

		if (!msg->Pending())
			return;

		QueueUserWorkItem(Worker, msg, 0);
	}

	static DWORD WINAPI Worker(PVOID param)
	{
		cxMSGProcessCreate* msg = (cxMSGProcessCreate*)param;

		if (MessageBox(nullptr, msg->Path(), L"是否允许启动进程", MB_OKCANCEL) != IDOK) {
			msg->SetBlock();
		}

		msg->CompletePending();

		return 0;
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

	cxMSGUserSetSessionConfig session_config;
	session_config.MSGTimeoutMS = 1000 * 20;
	manager.InControl(session_config);

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGProcessCreate] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("阻止继续执行，异步到其他线程处理后再继续");

	return 0;
}
//******************************************************************************
