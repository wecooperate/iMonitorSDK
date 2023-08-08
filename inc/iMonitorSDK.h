//******************************************************************************
/*++
	FileName:		iMonitorSDK.h
	Description:

--*/
//******************************************************************************
#ifndef __iMonitorSDK_41E77D06_B3FA_45EC_A1C4_117CF979D841__
#define __iMonitorSDK_41E77D06_B3FA_45EC_A1C4_117CF979D841__
//******************************************************************************
// clang-format off
//******************************************************************************
#include <tchar.h>
#include <windows.h>
#include <atlbase.h>
#include <atlstr.h>
//******************************************************************************
#include "iMonitor.h"
#include "iMonitorSDKExtension.h"
//******************************************************************************
#ifdef _M_IX86
#define IMONITOR_MODULE_NAME _T("iMonitor.dll")
#else
#define IMONITOR_MODULE_NAME _T("iMonitor64.dll")
#endif
//******************************************************************************
#define IMONITOR_IID "{51237525-2811-4BE2-A6A3-D8889E0D0CA0}"
//******************************************************************************
//
// 注意：部分扩展为了跨模块接口方便引入了CAtlStringW作为字符串，如果使用，需要保证CAtlStringW的编译版本一致
//
using cxMSGDataString = CAtlStringW;
//******************************************************************************
//
//	interface
//
//******************************************************************************
interface IMonitorMessageProcess
{
	enum emProcessType {
		emProcessUnknown,
		emProcessServices,
		emProcessCsrss,
		emProcessSvchost,
		emProcessExplorer,
	};

	virtual ULONG			GetProcessId		(void) = 0;
	virtual ULONG			GetParentProcessId	(void) = 0;
	virtual	ULONG			GetCreatorProcessId	(void) = 0;
	virtual LPCWSTR			GetProcessName		(void) = 0;
	virtual LPCWSTR			GetProcessPath		(void) = 0;
	virtual LPCWSTR			GetCommandline		(void) = 0;
	virtual LPCWSTR			GetCompanyName		(void) = 0;
	virtual LPCWSTR			GetProductName		(void) = 0;
	virtual LPCWSTR			GetFileDescription	(void) = 0;
	virtual LPCWSTR			GetSigner			(void) = 0;
	virtual bool			IsSignerVerified	(void) = 0;
	virtual LPCWSTR			GetCatalogSigner	(void) = 0;
	virtual bool			IsCatalogSignerVerified(void) = 0;
	virtual ULONGLONG		GetCreateTime		(void) = 0;
	virtual emProcessType	GetProcessType		(void) = 0;
	virtual bool			GetMD5				(UCHAR Hash[16]) = 0;
	virtual LPCWSTR			GetMD5String		(void) = 0;
};
//******************************************************************************
interface IMonitorMessage
{
	struct Binary {
		PVOID Data;
		ULONG Length;
	};

	//
	// 基础字段
	//

	virtual cxMSGHeader*	GetHeader			(void) = 0;
	inline ULONG			GetType				(void) { return GetHeader()->Type; }
	inline ULONG			GetStatus			(void) { return GetHeader()->Status; }
	inline ULONG			GetCurrentProcessId	(void) { return GetHeader()->CurrentProcessId; }
	inline ULONG			GetCurrentThreadId	(void) { return GetHeader()->CurrentThreadId; }

	virtual IMonitorMessageProcess* GetProcess	(void) = 0;

	virtual LPCWSTR			GetTypeName			(void) = 0;
	virtual ULONG			GetFieldCount		(void) = 0;
	virtual emMSGDataType	GetFieldType		(ULONG Index) = 0;
	virtual LPCWSTR			GetFieldName		(ULONG Index) = 0;
	virtual ULONG			GetFieldIndex		(LPCWSTR Name) = 0;

	virtual ULONG			GetULONG			(ULONG Index) = 0;
	virtual ULONGLONG		GetULONGLONG		(ULONG Index) = 0;
	virtual cxMSGDataIPRef	GetIP				(ULONG Index) = 0;
	virtual Binary			GetBinary			(ULONG Index) = 0;
	virtual LPCWSTR			GetString			(ULONG Index) = 0;
	virtual LPCWSTR			GetFormatedString	(ULONG Index) = 0;

	virtual bool			IsMatch				(ULONG Index, LPCWSTR Pattern, bool IgnoreCase = true) = 0;

	//
	// 扩展字段，由开发者自行定义的字段，这些字段可以用于规则引擎，详细参考MonitorExtensionFieldTable
	//	HasValue: 表示是否有值，如果没有字段则返回默认值并且HasValue = false
	//

	virtual ULONGLONG		GetNumber			(LPCWSTR Name, bool* HasValue = nullptr) = 0;
	virtual LPCWSTR			GetString			(LPCWSTR Name, bool* HasValue = nullptr) = 0;

	//
	// Action 相关操作，用于返回消息结果给驱动：需要Waiting状态才能设置返回结果
	//

	virtual bool			IsWaiting			(void) = 0;
	virtual bool			SetAction			(const cxMSGAction& Action) = 0;
	virtual bool			SetBlock			(void) = 0;
	virtual bool			SetGrantedAccess	(ULONG Access) = 0;
	virtual bool			SetIPRedirect		(ULONG IP, USHORT Port, ULONG ProcessId = ::GetCurrentProcessId()) = 0;
	virtual bool			SetTerminateProcess	(void) = 0;
	virtual bool			SetTerminateThread	(void) = 0;
	virtual bool			SetInjectDll		(LPCWSTR Path) = 0;
	virtual bool			SetFileRedirect		(LPCWSTR Path) = 0;

	//
	//	异步处理：
	//		设置Pending成功后，可以拥有IMonitorMessage的生命周期，允许在回调返回后继续使用。
	//		使用完毕，一定需要使用CompletePending来恢复状态，不然内核等待事件需要超时才能返回。
	//
	//	使用场景：需要弹框交互确认、或者是多线程处理的场景。
	//

	virtual bool			Pending				(void) = 0;
	virtual void			CompletePending		(void) = 0;

	virtual void			SetCustomContext	(PVOID Context) = 0;
	virtual PVOID			GetCustomContext	(void) = 0;
};
//******************************************************************************
struct MonitorExtensionField
{
#define MONITOR_SUPPORT_ALL_MESSAGE 0

	ULONG					SupportMessageType	= MONITOR_SUPPORT_ALL_MESSAGE;
	LPCWSTR					FieldName			= nullptr;
	ULONGLONG				(*GetNumber)		(IMonitorMessage* Message) = nullptr;
	cxMSGDataString			(*GetString)		(IMonitorMessage* Message) = nullptr;
};
//******************************************************************************
struct MonitorExtensionFieldTable
{
	ULONG					Count				= 0;
	MonitorExtensionField*	Fields				= nullptr;
};
//******************************************************************************
interface IMonitorCallback
{
	//
	//	DisableXxxMonitor: (在驱动启动前设置生效) 表示是否关闭Xxx的监控，如果只需要部分能力，建议关闭其他不需要的监控。一般用于优化性能，解决冲突。
	//	InternalCallback: 内部使用，接管原始的消息
	//	ExtensionFieldTable: 消息扩展字段
	//
	struct GlobalConfig {
			bool			DisableFileMonitor	= false;
			bool			DisableRegMonitor	= false;
			bool			DisableSocketMonitor= false;
			bool			DisableWFPMonitor	= false;
			bool			DisableNPMSMonitor	= false;

			bool			InternalCallback	= false;

			MonitorExtensionFieldTable ExtensionFieldTable;
	};

	virtual void			OnConfig			(GlobalConfig& Config) {}
	virtual void			OnCustomEvent		(ULONG Type, PVOID Context) {}
	virtual bool			OnInternalCallback	(cxMSGHeader* Header, HANDLE FilterHandle, ULONGLONG MessageId) { return false; }
	virtual void			OnCallback			(IMonitorMessage* Message) = 0;
};
//******************************************************************************
interface __declspec (uuid("{87AFD09D-59D7-47AD-8A32-5852F2FB958D}")) IMonitorProcess : public IUnknown, public IMonitorMessageProcess
{
};
//******************************************************************************
interface IMonitorExtension
{
	virtual	HRESULT			CreateRuleEngine	(LPCWSTR Path, IMonitorRuleEngine** Engine) = 0;
	virtual HRESULT			CreateAgentEngine	(ULONG MaxThread, IMonitorAgentEngine** Engine) = 0;

	virtual HRESULT			FindProcess			(ULONG ProcessId, IMonitorProcess** Process) = 0;

	//
	// 是否开启域名解析，开启后可以通过IP反查对应的域名，默认开启，如果需要关闭可以通过EnableDomainParser(false）关闭
	//
	virtual void			EnableDomainParser	(bool Enable) = 0;
	virtual cxMSGDataString	GetDomainFromIP		(ULONG IP) = 0;
	virtual cxMSGDataString	GetDomainFromIP		(const cxMSGDataIP& IP) = 0;
};
//******************************************************************************
interface __declspec (uuid(IMONITOR_IID)) IMonitorManager : public IUnknown, public IMonitorExtension
{
	virtual HRESULT			Start				(IMonitorCallback* Callback) = 0;
	virtual HRESULT			Control				(PVOID Data, ULONG Length, PVOID OutData = nullptr, ULONG OutLength = 0, PULONG ReturnLength = nullptr) = 0;
	virtual HRESULT			Stop				(void) = 0;
	virtual HRESULT			UnloadDriver		(void) = 0;
	virtual HRESULT			SendCustomEvent		(ULONG Type, PVOID Context) = 0;
};
//******************************************************************************
//
//	helper
//
//******************************************************************************
// clang-format on
//******************************************************************************
class MonitorManager
{
public:
	MonitorManager(void)
		: m_MonitorModule(NULL)
	{
	}

	~MonitorManager(void)
	{
		Stop();

		m_Monitor.Detach();
	}

	HRESULT Start(IMonitorCallback* Callback, LPCTSTR Path = IMONITOR_MODULE_NAME)
	{
		HRESULT hr = LoadMonitor(Path);

		if (hr != S_OK && hr != S_FALSE)
			return hr;

		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Start(Callback);
	}

	HRESULT Stop(void)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Stop();
	}

	HRESULT UnloadDriver(LPCTSTR Path = IMONITOR_MODULE_NAME)
	{
		HRESULT hr = LoadMonitor(Path);

		if (hr != S_OK && hr != S_FALSE)
			return hr;

		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->UnloadDriver();
	}

	HRESULT SendCustomEvent(ULONG Type, PVOID Context)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->SendCustomEvent(Type, Context);
	}

	HRESULT FindProcess(ULONG ProcessId, IMonitorProcess** Process)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->FindProcess(ProcessId, Process);
	}

	CString GetDomainFromIP(ULONG IP)
	{
		if (!m_Monitor)
			return CString();

		return m_Monitor->GetDomainFromIP(IP);
	}

	CString GetDomainFromIP(cxMSGDataIPRef IP)
	{
		if (!m_Monitor)
			return CString();

		return m_Monitor->GetDomainFromIP(IP);
	}

public:
	template<typename T>
	HRESULT InControl(const T& config)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Control((PVOID)&config, sizeof(config));
	}

	HRESULT Control(PVOID Data, ULONG Length, PVOID OutData = nullptr, ULONG OutLength = 0, PULONG ReturnLength = nullptr)
	{
		if (!m_Monitor)
			return E_UNEXPECTED;

		return m_Monitor->Control(Data, Length, OutData, OutLength, ReturnLength);
	}

	CComPtr<IMonitorRuleEngine> CreateRuleEngine(LPCWSTR Path)
	{
		if (!m_Monitor)
			return NULL;

		CComPtr<IMonitorRuleEngine> engine;
		HRESULT hr = m_Monitor->CreateRuleEngine(Path, &engine);

		if (hr != S_OK)
			return NULL;

		return engine;
	}

	CComPtr<IMonitorAgentEngine> CreateAgentEngine(ULONG MaxThread = 1)
	{
		if (!m_Monitor)
			return NULL;

		CComPtr<IMonitorAgentEngine> engine;
		HRESULT hr = m_Monitor->CreateAgentEngine(MaxThread, &engine);

		if (hr != S_OK)
			return NULL;

		return engine;
	}

protected:
	HRESULT LoadMonitor(LPCTSTR Path)
	{
		if (m_Monitor)
			return S_FALSE;

		if (!Path)
			Path = IMONITOR_MODULE_NAME;

		if (!m_MonitorModule) {
			m_MonitorModule = LoadLibraryEx(Path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

			if (!m_MonitorModule)
				return HRESULT_FROM_WIN32(GetLastError());
		}

		typedef HRESULT(STDAPICALLTYPE * PFN_DllGetClassObject)(REFCLSID, REFIID, PVOID*);

		PFN_DllGetClassObject pfn = (PFN_DllGetClassObject)GetProcAddress(m_MonitorModule, "DllGetClassObject");

		if (!pfn)
			return E_FAIL;

		return pfn(CLSID_NULL, __uuidof(IMonitorManager), (PVOID*)&m_Monitor);
	}

protected:
	HMODULE m_MonitorModule;
	CComPtr<IMonitorManager> m_Monitor;
};
//******************************************************************************
#endif
