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
		if (Message->GetType() != emMSGProcessOpen)
			return;

		cxMSGProcessOpen* msg = (cxMSGProcessOpen*)Message;

		//
		// 禁止结束notepad.exe
		//	 如果需要自保护请参考自保护功能，禁止结束还会有其他方式结束进程（远程注入、操作内存等）
		//

		if (msg->IsMatchPath(L"*\\notepad.exe"))
			msg->SetGrantedAccess(msg->DesiredAccess() & ~PROCESS_TERMINATE);
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
	config.Config[emMSGProcessOpen] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("禁止结束notepad.exe");

	return 0;
}
//******************************************************************************
