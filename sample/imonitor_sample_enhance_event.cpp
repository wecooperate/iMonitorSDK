//******************************************************************************
/*++
	Description:

	自定义事件示例：
		抛事件到监控的线程
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

	void OnCustomEvent(ULONG Type, PVOID Context) override
	{
		printf("type=%d, context=%s\n", Type, (const char*)Context);
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

	manager.SendCustomEvent(1234, "hello");

	WaitForExit("抛事件到监控的线程");

	return 0;
}
//******************************************************************************
