//******************************************************************************
/*++
	Description:
		文件打开拦截

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGFileCreate)
			return;

		cxMSGFileCreate* msg = (cxMSGFileCreate*)Message;

		//
		// 保护带 .json 的文件不被修改、删除
		//

		if (FlagOn(msg->Access(), DELETE | FILE_WRITE_DATA)) {
			if (msg->IsMatchPath(L"*.json")) {
				msg->SetBlock();
			}
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

	//
	// emMSGConfigSend 同步事件，可以SetBlock禁止相应的动作
	//

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGFileCreate] = emMSGConfigSend;
	manager.InControl(config);

	cxMSGUserSetSessionConfig sconfig;
	sconfig.FilterFileCreateOnlyModifiable = TRUE;
	manager.InControl(sconfig);

	WaitForExit("保护带 .json 的文件不被修改、删除");

	return 0;
}
//******************************************************************************
