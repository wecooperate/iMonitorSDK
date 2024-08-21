//******************************************************************************
/*++
	Description:

	�Զ�������

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
		Config.DisableNPMSMonitor = true;	// ��ֹ����NampedPipe�ļ��
		Config.DisableSocketMonitor = true; // ��ֹ����Socket���
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

	WaitForExit("�Զ�������");

	return 0;
}
//******************************************************************************
