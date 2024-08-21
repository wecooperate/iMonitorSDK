//******************************************************************************
/*++
	Description:

	扩展能力示例：
		可以为IMonitorMessage扩展更多的字段，这些字段同时也可以用于规则引擎。
--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
#include <atlstr.h>
#include <Shlwapi.h>
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	const MonitorExtensionFieldTable& GetExtensionFieldTable(void)
	{
		static MonitorExtensionField fields[] = {
			{ MONITOR_SUPPORT_ALL_MESSAGE, L"FileExtension", nullptr, GetFileExtension },
			{ emMSGProcessCreate, L"IsVirus", IsVirus, nullptr },
		};

		static MonitorExtensionFieldTable table = {
			_countof(fields),
			fields,
		};

		return table;
	}

	void OnConfig(GlobalConfig& Config)
	{
		Config.ExtensionFieldTable = GetExtensionFieldTable();
	}

	void OnCallback(IMonitorMessage* Message) override
	{
		auto is_virus = Message->GetNumber(L"IsVirus");
		auto file_ext = Message->GetString(L"FileExtension");

		printf("file_ext = %S, is_virus = %d\n", file_ext, (ULONG)is_virus);
	}

	static CString GetFileExtension(IMonitorMessage* Message)
	{
		return PathFindExtension(Message->GetString(emMSGFieldPath));
	}

	static ULONGLONG IsVirus(IMonitorMessage* Message)
	{
		return FALSE;
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
	config.Config[emMSGProcessCreate] = emMSGConfigPost;
	manager.InControl(config);

	WaitForExit("扩展能力示例：可以为IMonitorMessage扩展更多的字段，这些字段同时也可以用于规则引擎。");

	return 0;
}
//******************************************************************************
