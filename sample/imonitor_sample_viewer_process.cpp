//******************************************************************************
/*++
	Description:

--*/
//******************************************************************************
#include "imonitor_sample.h"
#include <set>
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
	std::set<ULONG> m_MSGs;

public:
	void OnCallback(IMonitorMessage* msg) override
	{
		if (m_MSGs.find(msg->GetType()) != m_MSGs.end())
			return;

		m_MSGs.insert(msg->GetType());

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
	for (int i = emMSGProcess; i < emMSGProcess + 100; i++) {
		config.Config[i] = emMSGConfigPost;
	}
	manager.InControl(config);

	WaitForExit("方便查看、验证消息的监控和各字段是否正常");

	return 0;
}
//******************************************************************************
