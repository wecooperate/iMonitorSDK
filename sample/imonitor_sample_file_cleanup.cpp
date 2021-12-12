//******************************************************************************
/*++
	Description:
		监控文件新增加、修改

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
#define FILE_SUPERSEDED		0x00000000
#define FILE_OPENED			0x00000001
#define FILE_CREATED		0x00000002
#define FILE_OVERWRITTEN	0x00000003
#define FILE_EXISTS			0x00000004
#define FILE_DOES_NOT_EXIST 0x00000005
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGFileCleanup)
			return;

		cxMSGFileCleanup* msg = (cxMSGFileCleanup*)Message;

		if (msg->Information() == FILE_CREATED) {
			printf("new file : [%S] -> %S\n", msg->CurrentProcessPath(), msg->Path());
		} else if (msg->GetHeader()->Modified) {
			printf("mod file : [%S] -> %S\n", msg->CurrentProcessPath(), msg->Path());
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
	config.Config[emMSGFileCleanup] = emMSGConfigPost;
	manager.InControl(config);

	WaitForExit("正在监控文件新增加、修改");

	return 0;
}
//******************************************************************************
