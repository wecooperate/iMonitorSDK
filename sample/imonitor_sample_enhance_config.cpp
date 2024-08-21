//******************************************************************************
/*++
	Description:

	自定义配置

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
	}

	void OnConfig(GlobalConfig& Config) override
	{
		Config.DisableNPMSMonitor = true;	// 禁止开启NampedPipe的监控
		Config.DisableSocketMonitor = true; // 禁止开启Socket监控
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

	WaitForExit("自定义配置");

	return 0;
}
//******************************************************************************
