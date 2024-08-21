//******************************************************************************
/*++
	Description:

	应用层注入扩展监控示例

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	MonitorCallback(void)
	{
		TCHAR path[MAX_PATH] = {};
		GetModuleFileName(nullptr, path, MAX_PATH);
		PathRemoveFileSpec(path);
		m_Dll32 = path;
		m_Dll32 += _T("\\iMonitorH2K.i32");
		m_Dll64 = path;
		m_Dll64 += _T("\\iMonitorH2K.i64");
	}

	void OnCallback(IMonitorMessage* msg) override
	{
		if (msg->GetType() == emMSGImageLoad) {
			auto ptr = (cxMSGImageLoad*)msg;
			if (ptr->IsMatchPath(L"*\\kernel32.dll")) {
				msg->SetInjectDll(msg->GetProcess()->Is64Bit() ? m_Dll64 : m_Dll32, false);
			}
			return;
		}

		printf("%S ==> %S\n", msg->GetTypeName(), msg->GetFormatedString(emMSGFieldCurrentProcessPath));

		for (ULONG i = emMSGFieldCurrentProcessCommandline; i < msg->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", msg->GetFieldName(i), msg->GetFormatedString(i));
		}
	}

	void OnConfig(GlobalConfig& Config)
	{
		Config.DisableUserMonitor = false;
	}

protected:
	CString m_Dll64;
	CString m_Dll32;
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
	for (int i = emMSGHook; i < emMSGHook + 100; i++) {
		config.Config[i] = emMSGConfigPost;
	}
	config.Config[emMSGImageLoad] = emMSGConfigSend;

	manager.InControl(config);

	WaitForExit("应用层注入扩展监控示例");

	return 0;
}
//******************************************************************************
