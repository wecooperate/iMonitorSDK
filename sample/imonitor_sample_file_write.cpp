//******************************************************************************
/*++
	Description:
		监控文件写入内容

--*/
//******************************************************************************
#include "imonitor_sample.h"
#include <string>
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGFilePostWrite)
			return;

		cxMSGFilePostWrite* msg = (cxMSGFilePostWrite*)Message;

		if (!msg->IsMatchPath(L"*.json"))
			return;

		auto binary = msg->Data();
		std::string str((const char*)binary.Data, binary.Length);

		printf("%S -> %S\n%s\n", msg->CurrentProcessPath(), msg->Path(), str.c_str());
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

	manager.InControl(cxMSGUserSetGlobalConfig());

	//
	// emMSGConfigSend 同步事件，可以SetBlock禁止相应的动作
	//

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGFilePostWrite] = emMSGConfigPost;
	manager.InControl(config);

	WaitForExit("监控.json文件写入内容");

	return 0;
}
//******************************************************************************
