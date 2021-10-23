//******************************************************************************
/*++
	Description:
		�Ա�����������

--*/
//******************************************************************************
#include "imonitor_sample.h"
//******************************************************************************
class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* msg) override
	{
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

	manager.InControl(cxMSGUserEnableProtect());

	//
	// Path·��֧��ͨ���
	//	* ��ʾ����n���ַ�
	//	? ��ʾ����һ���ַ�
	//	> �����ַ�����β����ʾ�ַ�������������\\��β������Ŀ¼�жϣ�����protect> ƥ�� protect �� protect\\*��
	//
	{
		//
		// ���ӽ��̡��ļ������� ������������notepad.exe�Ľ��̲����������ļ������޸ġ�ɾ��
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeProcessPath | emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\notepad.exe", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// �����ļ��б����� ����protectĿ¼������ļ������ⲿ�޸ġ�Ŀ¼������������ɾ��
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeFilePath;
		wcsncpy(rule.Path, L"*\\protect>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// ����ע��������� ����iMonitor������ɾ�����޸ģ�������ֵ
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeRegPath;
		wcsncpy(rule.Path, L"*\\iMonitor>", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	{
		//
		// �������ν��̣����Բ����������Ľ��̡��ļ���ע��������ǽ��̱������ܱ���
		//
		cxMSGUserAddProtectRule rule;
		rule.ProtectType = emProtectTypeTrustProcess;
		wcsncpy(rule.Path, L"*taskkill*", MONITOR_MAX_BUFFER);
		manager.InControl(rule);
	}

	WaitForExit("�Ա���������");

	manager.InControl(cxMSGUserRemoveAllProtectRule());
	manager.InControl(cxMSGUserDisableProtect());

	return 0;
}
//******************************************************************************