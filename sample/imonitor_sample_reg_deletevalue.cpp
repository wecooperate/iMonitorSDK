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
		//
		// 禁止修改删除带 protect 的注册表值
		//
		if (Message->GetType() == emMSGRegDeleteValue) {
			cxMSGRegDeleteValue* msg = (cxMSGRegDeleteValue*)Message;

			if (msg->IsMatchValueName(L"*protect*"))
				msg->SetBlock();
		} else if (Message->GetType() == emMSGRegSetValue) {
			cxMSGRegSetValue* msg = (cxMSGRegSetValue*)Message;

			if (msg->IsMatchValueName(L"*protect*"))
				msg->SetBlock();
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

	manager.InControl(cxMSGUserSetGlobalConfig());

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGRegDeleteValue] = emMSGConfigSend;
	config.Config[emMSGRegSetValue] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("禁止修改删除带 protect 的注册表值");

	return 0;
}
//******************************************************************************
