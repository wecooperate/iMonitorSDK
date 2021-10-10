

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
	
	virtual	HRESULT			CreateRuleEngine	(LPCWSTR Path, IMonitorRuleEngine** Engine) = 0;

};
```

| 函数             | 说明                                                  |
| ---------------- | ----------------------------------------------------- |
| Start            | 设置驱动回调、安装并启动驱动                          |
| Control          | 跟驱动通讯的入口，详细参考cxMSGUserXxxx结构体         |
| CreateRuleEngine | 加载基于jsonlogic的规则引擎，详细参考**规则引擎**部分 |

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

> iMonitorSDK内置基于jsonlogic的规则引擎

### 接口说明

```c++
interface IMonitorRuleCallback
{
	enum emMatchStatus {
		emMatchStatusBreak,
		emMatchStatusContinue,
	};

	virtual void			OnBeginMatch		(IMonitorMessage* Message) {}
	virtual void			OnFinishMatch		(IMonitorMessage* Message) {}
	virtual emMatchStatus	OnMatch				(IMonitorMessage* Message, const char* GroupName, const char* RuleName, ULONG Action, const char* ActionParam) = 0;
};

interface IMonitorRuleEngine : public IUnknown
{
	virtual void			Match				(IMonitorMessage* Message, IMonitorRuleCallback* Callback) = 0;
};
```

### 使用说明

```c++
class MonitorCallback
	: public IMonitorCallback
	, public IMonitorRuleCallback
{
public:
	void OnCallback(IMonitorMessage* Message) override
	{
		m_RuleEngine->Match(Message, this);
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
	CComPtr<IMonitorRuleEngine> m_RuleEngine;
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

