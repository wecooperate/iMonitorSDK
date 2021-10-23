

[TOC]

## 头文件说明

-   iMonitor.h 驱动、应用层共用的定义
-   iMonitorSDK.h SDK接口定义
-   iMonitorProtocol.h idl自动生成的协议辅助类

## 接口说明

### IMonitorManager

>   SDK的使用入口

```
interface IMonitorManager : public IUnknown
{
	virtual HRESULT			Start				(IMonitorCallbackInternal* Callback) = 0;
	virtual HRESULT			Start				(IMonitorCallback* Callback) = 0;
	virtual HRESULT			Control				(PVOID Data, ULONG Length, PVOID OutData, ULONG OutLength, PULONG ReturnLength) = 0;
	virtual HRESULT			Stop				(void) = 0;
	
	virtual	HRESULT			CreateRuleService	(LPCWSTR Path, IRuleService** Service) = 0;
	virtual	HRESULT			CreateAgentService	(ULONG MaxThread, IAgentService** Service) = 0;
};
```

| 函数               | 说明                                                  |
| ------------------ | ----------------------------------------------------- |
| Start              | 设置驱动回调、安装并启动驱动                          |
| Control            | 跟驱动通讯的入口，详细参考cxMSGUserXxxx结构体         |
| CreateRuleService  | 加载基于jsonlogic的规则引擎，详细参考**规则引擎**部分 |
| CreateAgentService | 创建网络中间人服务器，详细参考**网络代理**部分        |

支持的Control操作：

| 类型                          | 说明                                           |
| ----------------------------- | ---------------------------------------------- |
| cxMSGUserSetGlobalConfig      | 设置全局配置                                   |
| cxMSGUserGetGlobalConfig      | 获取全局配置                                   |
| **cxMSGUserSetMSGConfig**     | 设置监控消息配置，开启监控都通过这个命令字设置 |
| cxMSGUserGetMSGConfig         | 获取监控消息配置                               |
| cxMSGUserEnableProtect        | 开启自保护                                     |
| cxMSGUserDisableProtect       | 关闭自保护                                     |
| cxMSGUserAddProtectRule       | 添加保护规则                                   |
| cxMSGUserRemoveProtectRule    | 删除保护规则                                   |
| cxMSGUserRemoveAllProtectRule | 清空保护规则                                   |

### IMonitorCallback

### IMonitorCallbackInternal

>   事件接受回调，逻辑都是在事件回调里面处理，IMonitorCallbackInternal内部的接口，有特殊需求才使用

```c++
interface IMonitorCallbackInternal
{
	virtual void			OnCallback			(cxMSGHeader* Header, cxMSGAction* Action) = 0;
};

interface IMonitorCallback
{
	virtual void			OnCallback			(IMonitorMessage* Message) = 0;
};
```

### IMonitorMessage

>   驱动事件消息，包括公共字段（当前进程信息等）、私有字段（具体参考附录的协议字段）

```
interface IMonitorMessage
{
    struct Binary {
        PVOID Data;
        ULONG Length;
    };

    virtual cxMSGHeader*    GetHeader           (void) = 0;
    inline  ULONG           GetType             (void) { return GetHeader()->Type; }
    inline  ULONG           GetStatus           (void) { return GetHeader()->Status; }
    inline  ULONG           GetCurrentProcessId (void) { return GetHeader()->CurrentProcessId; }
    inline  ULONG           GetCurrentThreadId  (void) { return GetHeader()->CurrentThreadId; }

    virtual LPCWSTR         GetTypeName         (void) = 0;
    virtual ULONG           GetFieldCount       (void) = 0;
    virtual emMSGDataType   GetFieldType        (ULONG Index) = 0;
    virtual LPCWSTR         GetFieldName        (ULONG Index) = 0;
    virtual ULONG           GetFieldIndex       (LPCWSTR Name) = 0;

    virtual ULONG           GetULONG            (ULONG Index) = 0;
    virtual ULONGLONG       GetULONGLONG        (ULONG Index) = 0;
    virtual LPCWSTR         GetString           (ULONG Index) = 0;
    virtual LPCWSTR         GetFormatedString   (ULONG Index) = 0;
    virtual Binary          GetBinary           (ULONG Index) = 0;

    virtual bool            IsMatch             (ULONG Index, LPCWSTR Pattern) = 0;

    virtual bool            IsWaiting           (void) = 0;
    virtual bool            SetAction           (const cxMSGAction& Action) = 0;
    virtual bool            SetBlock            (void) = 0;
    virtual bool            SetGrantedAccess    (ULONG Access) = 0;
    virtual bool            SetIPRedirect       (ULONG IP, USHORT Port, ULONG ProcessId = ::GetCurrentProcessId()) = 0;
    virtual bool            SetFileRedirect     (LPCWSTR Path) = 0;
};
```

| 函数              | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| GetString         | 要求字段必须是字符串，如果对应的字段不是字符串，则返回空字符串 |
| GetFormatedString | 如果对应的字段是字符串，同GetString，否则将强制转换成字符串  |
| IsWaiting         | 驱动是否阻塞事件执行，如果是可以通过SetXxx来响应事件（阻止、重定向等） |
| SetBlock          | 阻止当前的操作                                               |
| SetGrantedAccess  | 对于打开进程、打开线程操作，可以设置允许的打开权限           |
| SetIPRedirect     | 对于Tcp连接，可以设置IP、Port重定向到新的地址                |
| IsMatch           | 内置通配符字符串匹配，支持 * ？ >  （> 表示目录，dir>  等同于 dir + dir\\\\*） |

## 驱动配置

iMonitorSDK必须带签名过的配置文件（iMonitor.scer）才能正常加载。

### 支持的配置参数：

| 字段                     | 类型   | 描述                                                         |
| ------------------------ | ------ | ------------------------------------------------------------ |
| driver_name              | string | 驱动的服务名字                                               |
| driver_port_name         | string | 应用层跟驱动通讯的名字                                       |
| max_session              | int    | 允许多少个客户端同时打开驱动，填0为默认值4个，最多不超过4    |
| enable_unload_driver     | bool   | 是否允许驱动卸载                                             |
| enable_file_monitor      | bool   | 是否允许开启文件监控                                         |
| enable_process_monitor   | bool   | 是否允许开启进程开启                                         |
| enable_reg_monitor       | bool   | 是否允许开启注册表监控                                       |
| enable_socket_monitor    | bool   | 是否允许开启socket监控                                       |
| enable_wfp_monitor       | bool   | 是否允许开启wfp监控                                          |
| enable_self_protect      | bool   | 是否开启子保护（开启了驱动所在目录的进程、文件都会被保护）   |
| enable_self_open_protect | bool   | 是否开启驱动打开自保护（开启了只允许驱动所在目录打开驱动通讯端口） |
| trust_open_path_list     | array  | 字符串数组，允许打开驱动通讯端口的进程路径列表               |
| protect_list             | array  | 对象数组，其他被保护的路径列表（包括进程、文件、注册表）     |
| black_process_name_list  | array  | 禁止启动进程名黑名单                                         |
| black_process_path_list  | array  | 禁止启动进程路径黑名单                                       |
| black_file_name_list     | array  | 禁止创建文件名黑名单                                         |
| black_file_path_list     | array  | 禁止创建文件路径黑名单                                       |
| auto_inject              | object | 是否开启自动注入dll                                          |

### SDK带的默认配置如下

```json
{
  "driver_name": "iMonitorSDKDemo",
  "driver_port_name": "iMonitorSDKDemoPort",

  "max_session": 0,
  "enable_unload_driver": true,

  "enable_file_monitor": true,
  "enable_process_monitor": true,
  "enable_reg_monitor": true,
  "enable_socket_monitor": true,
  "enable_wfp_monitor": true,

  "enable_self_protect": false,
  "enable_self_open_protect": false,
  "trust_open_path_list": [],

  "protect_list": [],

  "black_process_name_list": [],
  "black_process_path_list": [],
  "black_file_name_list": [],
  "black_file_path_list": [],

  "auto_inject": {
    "enable": false,
    "wow64": true,
    "dll32": "",
    "dll64": ""
  },

  "end": true
}
```
### 快速使用演示

>   **为了防止驱动被非法使用，SDK默认带的驱动没有数字签名，请自行签名后才能正常加载运行。**

```c++
#include <iMonitorSDK.h>
#include <iMonitorProtocol.h>

class MonitorCallback : public IMonitorCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		if (Message->GetType() != emMSGProcessCreate)
			return;

		cxMSGProcessCreate* msg = (cxMSGProcessCreate*)Message;

		//
		// 禁止进程名 cmd.exe 的进程启动
		//

		if (msg->IsMatchPath(L"*\\cmd.exe"))
			msg->SetBlock();
	}
};

int main()
{
	MonitorManager manager;
	MonitorCallback callback;

	HRESULT hr = manager.Start(&callback);

	if (hr != S_OK) {
		printf("start failed = %08X\n", hr);
		return 0;
	}

	cxMSGUserSetMSGConfig config;
	config.Config[emMSGProcessCreate] = emMSGConfigSend;
	manager.InControl(config);

	WaitForExit("禁止进程名 cmd.exe 的进程启动");

	return 0;
}
```
## 规则引擎

> iMonitorSDK内置基于jsonlogic的规则引擎，可以用与设计主动防御、审计管控、EDR等业务。

### 接口说明

```c++
interface IRuleCallback
{
	enum emMatchStatus {
		emMatchStatusBreak,
		emMatchStatusContinue,
	};

	virtual void			OnBeginMatch		(IMonitorMessage* Message) {}
	virtual void			OnFinishMatch		(IMonitorMessage* Message) {}
	virtual emMatchStatus	OnMatch				(IMonitorMessage* Message, const char* GroupName, const char* RuleName, ULONG Action, const char* ActionParam) = 0;
};

interface IRuleService : public IUnknown
{
	virtual void			Match				(IMonitorMessage* Message, IRuleCallback* Callback) = 0;
};
```

### 使用说明

```c++
class MonitorCallback
	: public IMonitorCallback
	, public IRuleCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		m_RuleService->Match(Message, this);
	}

	emMatchStatus OnMatch(IMonitorMessage* Message, const char* GroupName, const char* RuleName, ULONG Action, const char* ActionParam) override
	{
		if (Action & emMSGActionBlock) {
			Message->SetBlock();
			printf("match block rule %s.%s\n", GroupName, RuleName);
			return emMatchStatusBreak;
		}

		return emMatchStatusContinue;
	}

public:
	CComPtr<IRuleService> m_RuleService;
};
```

### 规则文件说明

> 通过CreateRuleEngine传递规则文件路径创建规则引擎接口，路径格式支持全路径、带通配符的模糊匹配。
>
> 比如： C:\\1.json、C:\\rules\\\*.json

规则文件分为规则组、规则、匹配条件

```json
{
    "name" : "default",
    "description" : "default rule group",
    "rules" : [
		{
			"name" : "block notepad",
			"action" : 1,
			"action_param" : "",
			"message" : ["ProcessCreate", "ProcessOpen"],
			"matcher" : {
				"or" : [
					{"match" : ["Path", "*notepad.exe"]  }
				]
			}
		}
    ]
}
```

#### 规则组

| 字段        | 说明     |
| ----------- | -------- |
| name        | 规则组名 |
| description | 描述     |
| rules       | 规则列表 |

#### 规则

| 字段         | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| name         | 规则名                                                       |
| action       | 匹配后的动作，在回调里面使用                                 |
| action_param | 匹配后的动作参数                                             |
| message      | 数组，表示当前规则针对哪些消息类型有效，如果是 * 表示所有类型 |
| matcher      | 匹配条件                                                     |

#### 规则匹配条件

> 匹配条件的格式统一为  { operator:  [field, value] } 的格式
>
> 比如 { "==" { "CurrentProcessName", "cmd.exe"}} 表示 CurrentProcessName == "cmd.exe"
>
> operator表示匹配类型，见下面列表。
>
> field表示匹配的字段，详细参考协议字段。
>
> value表示匹配的值，具体类型参考operator

| operator | value类型 | 说明                                 |
| -------- | --------- | ------------------------------------ |
| or       | array     | 表示数组下任意规则匹配               |
| and      | array     | 表示数组下全部规则匹配               |
| bool     | bool      | 直接返回value的值                    |
| match    | string    | 表示通配符的字符串匹配，忽略大小写   |
| !match   | string    | match的相反                          |
| MATCH    | string    | 表示通配符的字符串匹配，忽略大小敏感 |
| !MATCH   | string    | MATCH的相反                          |
| ==       | number    | 等于                                 |
| !=       | number    | 不等于                               |
| >        | number    | 大于                                 |
| <        | number    | 小于                                 |
| >=       | number    | 大于等于                             |
| <=       | number    | 小于等于                             |
| &        | number    | 包含                                 |
| !&       | number    | 不包含                               |

## 网络代理

> 网络代理可以利用重定向中间人技术，接管系统的所有tcp网络连接。适用于：上网行为管理、网络监控审计、零信任的网络准入、广告过滤等。
>
> 支持http、https，支持https的自动识别、回退。支持对http代理下流量的二次监控过滤。

### 上网行为管理示例（sample/http_access_control）

![](./ac.png)

### 接口说明

#### IAgentService

```
interface IAgentService : public IUnknown
{
	virtual bool			Agent				(IMonitorMessage* Message, IAgentCallback* Callback, bool SSL = false) = 0;
};

HRESULT	 CreateAgentService	(ULONG MaxThread, IAgentService** Service);
```

| 函数               | 说明                                                         |
| ------------------ | ------------------------------------------------------------ |
| CreateAgentService | 创建代理服务，MaxThread表示并发的线程数，默认是1，最大是10。SDK会为每一个线程创建一个独立监听端口。同一个连接的回调都是在单线程触发。 |
| Agent              | 建立代理，只支持SocketConnect、WFPTcpConnect的消息类型，并且需要是Wating状态的。 |

代理建立后，所有的事件通过IAgentCallback触发。

#### IAgentCallback

```
interface IAgentCallback
{
	virtual void			OnCreate			(IAgentChannel* Channel) {}

	virtual void			OnLocalConnect		(IAgentChannel* Channel) {}
	virtual bool			OnLocalSSLHello		(IAgentChannel* Channel, const char* ServerName) { return true; }
	virtual void			OnLocalReceive		(IAgentChannel* Channel, const char* Data, size_t Length) {}
	virtual void			OnLocalError		(IAgentChannel* Channel, const char* Error) {}
	virtual void			OnLocalDisconnect	(IAgentChannel* Channel) {}

	virtual bool			OnRemotePreConnect	(IAgentChannel* Channel) { return true; }
	virtual bool			OnRemoteSSLVerify	(IAgentChannel* Channel, bool PreVerified) { return PreVerified; }
	virtual void			OnRemoteConnect		(IAgentChannel* Channel) {}
	virtual void			OnRemoteReceive		(IAgentChannel* Channel, const char* Data, size_t Length) {}
	virtual void			OnRemoteError		(IAgentChannel* Channel, const char* Error) {}
	virtual void			OnRemoteDisconnect	(IAgentChannel* Channel) {}

	virtual void			OnClose				(IAgentChannel* Channel) {}
};
```

| 函数               | 说明                                                         |
| ------------------ | ------------------------------------------------------------ |
| OnCreate           | 代理创建的时候，这时可以通过SetContext设置上下文             |
| OnLocalConnect     | 本地（浏览器连接到Agent）连接建立成功                        |
| OnLocalSSLHello    | 【https】ssl的握手client_hello，这里可以判断是否继续代理，返回false则不会解析https的内容，直接透传原始数据，可以解决双向认证的代理失败问题等。 |
| OnRemotePreConnect | 开始连接远程服务器，可以这里设置IP、Port修改原始的远程地址，适用于网络代理、准入、零信任等需求 |
| OnRemoteSSLVerify  | 【https】证书校验结果，如果返回true的使用有效证书，返回false则保留无效证书（浏览器会变红） |
| OnRemoteConnect    | 双向连接建立成功，可以开始收发包                             |

网络连接如下：

client（本地客户端，比如浏览器） --> Agent --> remote(远程网络)

#### IAgentChannel

```
interface IAgentChannel
{
	struct Address {
		ULONG				IP;
		USHORT				Port;
	};

	virtual ULONG			LocalGetProcessId	(void) = 0;
	virtual Address			LocalGetAddress		(void) = 0;
	virtual void			LocalSetAutoSend	(bool Enable) = 0;
	virtual void			LocalSetAutoReceive	(bool Enable) = 0;
	virtual bool			LocalSend			(const char* Data, size_t Length) = 0;
	virtual void			LocalReceive		(void) = 0;
	virtual void			LocalDisconnect		(void) = 0;

	virtual bool			RemoteSetAddress	(ULONG IP, USHORT Port) = 0;
	virtual Address			RemoteGetAddresss	(void) = 0;
	virtual void			RemoteSetAutoSend	(bool Enable) = 0;
	virtual void			RemoteSetAutoReceive(bool Enable) = 0;
	virtual bool			RemoteSend			(const char* Data, size_t Length) = 0;
	virtual void			RemoteReceive		(void) = 0;
	virtual void			RemoteDisconnect	(void) = 0;

	virtual void			SetContext			(void* Context) = 0;
	virtual void*			GetContext			(void) = 0;
	virtual bool			SSLRestartAgent		(void) = 0;
	virtual bool			SSLIsRestartAgent	(void) = 0;
	virtual bool			SSLIsFallback		(void) = 0;
	virtual void			Close				(void) = 0;
};
```

| 函数                 | 说明                                                         |
| -------------------- | ------------------------------------------------------------ |
| LocalGetProcessId    | 获取本地（浏览器）的进程id                                   |
| LocalGetAddress      | 获取本地（浏览器）的网络地址                                 |
| LocalSetAutoSend     | 是否自动发包（本地收到包后，自动发给远程），默认为true       |
| LocalSetAutoReceive  | 是否自动收包，默认为true，如果设置false，需要自己通过LocalReceive通知收包，不然不会有OnLocalReceive回调 |
| RemoteSetAddress     | 设置修改远程的服务器地址，一般在OnRemotePreConnect里面设置   |
| RemoteGetAddresss    | 参考LocalXxx                                                 |
| RemoteSetAutoSend    | 参考LocalXxx                                                 |
| RemoteSetAutoReceive | 参考LocalXxx                                                 |
| SetContext           | 设置用户自己的额外数据                                       |
| GetContext           | 返回设置的数据                                               |
| SSLRestartAgent      | 重新启动https解析：在设置了代理的情况下，所有流量都会走代理，为了解析出代理里面的内容，可以在代理连接成功后，设置SSLRestartAgent重新发起https代理，这样就可以监控到代理后的内容。（其他任何ssl前有数据包的协议都适用） |
| SSLIsRestartAgent    | 判断当前是否重新解析的                                       |
| SSLIsFallback        | 如果设置了ssl，但是解析后发现不是ssl的，会回退到原始数据包的状态，这里判断是否回退过。 |

## 版本说明

### 1.0.2.0

添加网络代理支持

### 1.0.1.0

初始化版本

## 附录

### 协议字段

```c++
struct ProcessCreate {
    Path                 : Path;
    ProcessId            : ULONG;
    Commandline          : String;
    CreateTime           : Time;
    ParentPath           : Path;
    ParentProcessId      : ULONG;
    ParentCommandline    : String;
    ParentCreateTime     : Time;
}

struct ProcessExit {
    Path                 : Path;
    ProcessId            : ULONG;
}

struct ProcessOpen {
    Path                 : Path;
    ProcessId            : ULONG;
    ParentProcessId      : ULONG;
    DesiredAccess        : ProcessAccess;
    Duplicate            : Bool;
}

struct ThreadCreate {
    Path                 : Path;
    ProcessId            : ULONG;
    ThreadId             : ULONG;
    StartAddress         : ULONGLONG;
    RemoteThread         : Bool;
}

struct ThreadExit {
    Path                 : Path;
    ProcessId            : ULONG;
    ThreadId             : ULONG;
}

struct ThreadOpen {
    Path                 : Path;
    ProcessId            : ULONG;
    ParentProcessId      : ULONG;
    DesiredAccess        : ThreadAccess;
    Duplicate            : Bool;
    ThreadId             : ULONG;
}

struct ImageLoad {
    Path                 : Path;
    ProcessId            : ULONG;
    ImageBase            : ULONGLONG;
    ImageSize            : ULONGLONG;
    IsKernelImage        : Bool;
}

struct ProcessStart {
    Path                 : Path;
    ProcessId            : ULONG;
    Commandline          : String;
    CreateTime           : Time;
    ParentPath           : Path;
    ParentProcessId      : ULONG;
    ParentCommandline    : String;
    ParentCreateTime     : Time;
}

struct ThreadStart {
    Path                 : Path;
    ProcessId            : ULONG;
    ThreadId             : ULONG;
    StartAddress         : ULONGLONG;
    RemoteThread         : Bool;
}

struct FileCreate {
    Path                 : Path;
    Attributes           : FileAttributes;
    Access               : FileAccess;
    ShareAccess          : FileShareAccess;
    CreateDisposition    : FileDisposition;
    CreateOptions        : FileOptions;
}

struct FilePostCreate {
    Path                 : Path;
    Attributes           : FileAttributes;
    Access               : FileAccess;
    ShareAccess          : FileShareAccess;
    CreateDisposition    : FileDisposition;
    CreateOptions        : FileOptions;
    Information          : ULONG;
}

struct FileQueryOpen {
    Path                 : Path;
}

struct FilePostQueryOpen {
    Path                 : Path;
    CreationTime         : Time;
    LastAccessTime       : Time;
    LastWriteTime        : Time;
    ChangeTime           : Time;
    FileSize             : ULONGLONG;
    FileAttributes       : FileAttributes;
}

struct FileCleanup {
    Path                 : Path;
    Information          : ULONG;
    Modify               : ULONG;
}

struct FileCreateSection {
    Path                 : Path;
    PageProtection       : FilePageProtection;
}

struct FilePostCreateSection {
    Path                 : Path;
    PageProtection       : FilePageProtection;
}

struct FileRead {
    Path                 : Path;
    ReadLength           : ULONG;
    Offset               : ULONGLONG;
    Buffer               : ULONGLONG;
}

struct FilePostRead {
    Path                 : Path;
    ReadLength           : ULONG;
    Offset               : ULONGLONG;
    Buffer               : ULONGLONG;
    ReturnLength         : ULONG;
}

struct FileWrite {
    Path                 : Path;
    WriteLength          : ULONG;
    Offset               : ULONGLONG;
    Buffer               : ULONGLONG;
    Data                 : Binary;
}

struct FilePostWrite {
    Path                 : Path;
    WriteLength          : ULONG;
    Offset               : ULONGLONG;
    Buffer               : ULONGLONG;
    Data                 : Binary;
    ReturnLength         : ULONG;
}

struct FileCreateHardLink {
    Path                 : Path;
    LinkPath             : Path;
    ReplaceIfExists      : Bool;
}

struct FilePostCreateHardLink {
    Path                 : Path;
    LinkPath             : Path;
    ReplaceIfExists      : Bool;
}

struct FileRename {
    Path                 : Path;
    NewPath              : Path;
    ReplaceIfExists      : Bool;
}

struct FilePostRename {
    Path                 : Path;
    NewPath              : Path;
    ReplaceIfExists      : Bool;
}

struct FileDelete {
    Path                 : Path;
}

struct FilePostDelete {
    Path                 : Path;
}

struct FileSetSize {
    Path                 : Path;
    Size                 : ULONGLONG;
    SizeType             : ULONG;
}

struct FilePostSetSize {
    Path                 : Path;
    Size                 : ULONGLONG;
    SizeType             : ULONG;
}

struct FileSetBasicInfo {
    Path                 : Path;
    CreationTime         : Time;
    LastAccessTime       : Time;
    LastWriteTime        : Time;
    ChangeTime           : Time;
    FileAttributes       : FileAttributes;
}

struct FilePostSetBasicInfo {
    Path                 : Path;
    CreationTime         : Time;
    LastAccessTime       : Time;
    LastWriteTime        : Time;
    ChangeTime           : Time;
    FileAttributes       : FileAttributes;
}

struct FileFindFile {
    Path                 : Path;
    FindName             : Path;
    RestartScan          : Bool;
}

struct FilePostFindFile {
    Path                 : Path;
    FindName             : Path;
    RestartScan          : Bool;
    FileName             : Path;
    CreationTime         : Time;
    LastAccessTime       : Time;
    LastWriteTime        : Time;
    ChangeTime           : Time;
    FileSize             : ULONGLONG;
    FileAttributes       : FileAttributes;
}

struct RegCreateKey {
    Path                 : Path;
    Options              : RegOptions;
    DesiredAccess        : RegAccess;
}

struct RegPostCreateKey {
    Path                 : Path;
    Options              : RegOptions;
    DesiredAccess        : RegAccess;
    Disposition          : ULONG;
}

struct RegOpenKey {
    Path                 : Path;
    Options              : RegOptions;
    DesiredAccess        : RegAccess;
}

struct RegPostOpenKey {
    Path                 : Path;
    Options              : RegOptions;
    DesiredAccess        : RegAccess;
}

struct RegDeleteKey {
    Path                 : Path;
}

struct RegPostDeleteKey {
    Path                 : Path;
}

struct RegRenameKey {
    Path                 : Path;
    NewName              : String;
}

struct RegPostRenameKey {
    Path                 : Path;
    NewName              : String;
}

struct RegEnumKey {
    Path                 : Path;
    Index                : ULONG;
    InformationClass     : ULONG;
    InformationLength    : ULONG;
}

struct RegPostEnumKey {
    Path                 : Path;
    Index                : ULONG;
    InformationClass     : ULONG;
    InformationLength    : ULONG;
    ResultLength         : ULONG;
    Information          : Binary;
}

struct RegLoadKey {
    Path                 : Path;
    FilePath             : String;
}

struct RegPostLoadKey {
    Path                 : Path;
    FilePath             : String;
}

struct RegReplaceKey {
    Path                 : Path;
    OldFilePath          : String;
    NewFilePath          : String;
}

struct RegPostReplaceKey {
    Path                 : Path;
    OldFilePath          : String;
    NewFilePath          : String;
}

struct RegDeleteValue {
    Path                 : Path;
    ValueName            : String;
}

struct RegPostDeleteValue {
    Path                 : Path;
    ValueName            : String;
}

struct RegSetValue {
    Path                 : Path;
    ValueName            : String;
    DataType             : RegType;
    Data                 : Binary;
}

struct RegPostSetValue {
    Path                 : Path;
    ValueName            : String;
    DataType             : RegType;
    Data                 : Binary;
}

struct SocketCreate {
    SocketObject         : ULONGLONG;
}

struct SocketControl {
    SocketObject         : ULONGLONG;
    Code                 : ULONG;
    InputLength          : ULONG;
    OutputLength         : ULONG;
    InputData            : Binary;
}

struct SocketPostControl {
    SocketObject         : ULONGLONG;
    Code                 : ULONG;
    InputLength          : ULONG;
    OutputLength         : ULONG;
    InputData            : Binary;
    OutputData           : Binary;
}

struct SocketConnect {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
    SuperConnect         : Bool;
}

struct SocketPostConnect {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
    SuperConnect         : Bool;
}

struct SocketSend {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
    DataLength           : ULONG;
    Data                 : Binary;
}

struct SocketRecv {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
}

struct SocketPostRecv {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
    DataLength           : ULONG;
    Data                 : Binary;
}

struct SocketSendTo {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
    DataLength           : ULONG;
    Data                 : Binary;
}

struct SocketRecvFrom {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
}

struct SocketPostRecvFrom {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
    DataLength           : ULONG;
    Data                 : Binary;
}

struct SocketListen {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
}

struct SocketPostListen {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
}

struct SocketAccept {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
}

struct SocketPostAccept {
    SocketObject         : ULONGLONG;
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
}

struct WFPTcpConnect {
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
}

struct WFPUdpConnect {
    IP                   : SocketIP;
    Port                 : SocketPort;
    LocalIP              : SocketIP;
    LocalPort            : SocketPort;
}
```

### 协议编译

>   上面的IDL协议可以通过IDLTemplate转换成需要的对象，比如内置iMonitorProtocol.h的效果

```c++
class cxMSGProcessCreate : public cxMonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldProcessId,
		emMSGFieldCommandline,
		emMSGFieldCreateTime,
		emMSGFieldParentPath,
		emMSGFieldParentProcessId,
		emMSGFieldParentCommandline,
		emMSGFieldParentCreateTime,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto Commandline() { return GetString(emMSGFieldCommandline); }
	auto CreateTime() { return GetTime(emMSGFieldCreateTime); }
	auto ParentPath() { return GetPath(emMSGFieldParentPath); }
	auto ParentProcessId() { return GetULONG(emMSGFieldParentProcessId); }
	auto ParentCommandline() { return GetString(emMSGFieldParentCommandline); }
	auto ParentCreateTime() { return GetTime(emMSGFieldParentCreateTime); }

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchCommandline(LPCWSTR Pattern) { return IsMatch(emMSGFieldCommandline, Pattern); }
	bool IsMatchParentPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldParentPath, Pattern); }
	bool IsMatchParentCommandline(LPCWSTR Pattern) { return IsMatch(emMSGFieldParentCommandline, Pattern); }
};
```

