//******************************************************************************
/*++
    FileName:        iMonitor.h
    Description:

--*/
//******************************************************************************
#ifndef __iMonitor_H__
#define __iMonitor_H__
//******************************************************************************
// clang-format off
//******************************************************************************
#define MONITOR_VERSION                       4800
#define MONITOR_LICENSE_VERSION               1
#define MONITOR_MAX_BUFFER                    260
#define MONITOR_MAX_QUICK_FILTER_COUNT        100
//******************************************************************************
#ifndef BIT
#define BIT(n) (1 << n)
#endif
//******************************************************************************
#ifndef FlagOn
#define FlagOn(n, x) ((n) & (x))
#endif
//******************************************************************************
enum emMSGType
{
    emMSGInternal                             = 0,
    emMSGProcess                              = 100,
    emMSGFile                                 = 200,
    emMSGRegistry                             = 300,
    emMSGSocket                               = 400,
    emMSGWFP                                  = 500,
    emMSGHTTP                                 = 600,
    emMSGHook                                 = 700,
    emMSGExtension                            = 800,
    emMSGETW                                  = 900,
    emMSGMax                                  = 1000,
};
//******************************************************************************
#define MSG_GET_GROUP(type) (type / 100)
//******************************************************************************
enum emMSGGroup {
	emMSGGroupInternal                        = 0,
	emMSGGroupProcess                         = 1,
	emMSGGroupFile                            = 2,
	emMSGGroupRegistry                        = 3,
	emMSGGroupSocket                          = 4,
	emMSGGroupWFP                             = 5,
    emMSGGroupHTTP                            = 6,
    emMSGGroupHook                            = 7,
    emMSGGroupExtension                       = 8,
	emMSGGroupMax,
};
//******************************************************************************
enum emMSGTypeInternal
{
    emMSGInternalEnumProcess = emMSGInternal + 1,
    emMSGInternalEnumProtectRule,
    emMSGInternalEnd,
};
//******************************************************************************
enum emMSGGlobalFlagIndex {
    emMSGGlobalFlagBegin = emMSGGroupMax,
    emMSGGlobalFlagDisableNamedPipeAndMailsolt,
    emMSGGlobalFlagDisableRedirector,
    emMSGGlobalFlagEnableSelfProtect,
};
//******************************************************************************
enum emMSGTypeProcess
{
    emMSGProcessCreate = emMSGProcess + 1,
    emMSGProcessExit,
    emMSGProcessOpen,
    emMSGThreadCreate,
    emMSGThreadExit,
    emMSGThreadOpen,
    emMSGImageLoad,
    emMSGDriverLoad,
    emMSGProcessStart,
    emMSGThreadStart,
};
//******************************************************************************
enum emMSGTypeFile
{
    emMSGFileCreate = emMSGFile + 1,
    emMSGFilePostCreate,
    emMSGFileQueryOpen,
    emMSGFilePostQueryOpen,
    emMSGFileCleanup,
    emMSGFilePostCleanup_nosupport,
    emMSGFileCreateSection,
    emMSGFilePostCreateSection,
    emMSGFileRead,
    emMSGFilePostRead,
    emMSGFileWrite,
    emMSGFilePostWrite,
    emMSGFileCreateHardLink,
    emMSGFilePostCreateHardLink,
    emMSGFileRename,
    emMSGFilePostRename,
    emMSGFileDelete,
    emMSGFilePostDelete,
    emMSGFileSetSize,
    emMSGFilePostSetSize,
    emMSGFileSetBasicInfo,
    emMSGFilePostSetBasicInfo,
    emMSGFileFindFile,
    emMSGFilePostFindFile,
};
//******************************************************************************
enum emMSGTypeRegistry
{
    emMSGRegCreateKey = emMSGRegistry + 1,
    emMSGRegPostCreateKey,
    emMSGRegOpenKey,
    emMSGRegPostOpenKey,
    emMSGRegDeleteKey,
    emMSGRegPostDeleteKey,
    emMSGRegRenameKey,
    emMSGRegPostRenameKey,
    emMSGRegEnumKey,
    emMSGRegPostEnumKey,
    emMSGRegLoadKey,
    emMSGRegPostLoadKey,
    emMSGRegReplaceKey,
    emMSGRegPostReplaceKey,
    emMSGRegDeleteValue,
    emMSGRegPostDeleteValue,
    emMSGRegSetValue,
    emMSGRegPostSetValue,
    emMSGRegQueryValue,
    emMSGRegPostQueryValue,
};
//******************************************************************************
enum emMSGTypeSocket
{
    emMSGSocketCreate = emMSGSocket + 1,
    emMSGSocketPostCreate_nosupport,
    emMSGSocketControl,
    emMSGSocketPostControl,
    emMSGSocketConnect,
    emMSGSocketPostConnect,
    emMSGSocketSend,
    emMSGSocketPostSend_nosupport,
    emMSGSocketRecv,
    emMSGSocketPostRecv,
    emMSGSocketSendTo,
    emMSGSocketPostSendTo,
    emMSGSocketRecvFrom,
    emMSGSocketPostRecvFrom,
    emMSGSocketListen,
    emMSGSocketPostListen,
    emMSGSocketAccept,
    emMSGSocketPostAccept,
};
//******************************************************************************
enum emMSGTypeWFP
{
    emMSGWFPTcpConnect = emMSGWFP + 1,
    emMSGWFPUdpConnect,
    emMSGWFPTcpAccept,
    emMSGWFPUdpAccept,
	emMSGWFPICMPConnect,
    emMSGWFPICMPAccept,
    emMSGWFPSend,
    emMSGWFPRecv,
    emMSGWFPSendTo,
    emMSGWFPRecvFrom,
    emMSGWFPICMPSendTo,
    emMSGWFPICMPRecvFrom,
    emMSGWFPTcpBind,
    emMSGWFPUdpBind,
};
//******************************************************************************
enum emMSGTypeHTTP
{
    emMSGHTTPRequest = emMSGHTTP + 1,
    emMSGHTTPRequestEnd = emMSGHTTPRequest + 100,
};
//******************************************************************************
enum emMSGTypeHook
{
    emMSGHookWriteProcessMemory = emMSGHook + 1,
    emMSGHookRpcCreateProcess,
    emMSGHookSetWindowsHookEx,
    emMSGHookCreateService,
    emMSGHookStartService,
    emMSGHookChangeServiceConfig,
    emMSGHookCoCreateInstance,
    emMSGHookSetContextThread,
    emMSGHookQueueApcThread,
    emMSGHookMapViewOfSection,
    emMSGHookReadProcessMemory,
    emMSGHookDuplicateHandle,
    emMSGHookSendInput,
    emMSGHookShutdownSystem,
    emMSGHookSetSystemTime,
    emMSGHookGetClipboardData,
    emMSGHookSetDeskWallpaper,
    emMSGHookUseCamera,
    emMSGHookKeyLogger,
	emMSGHookPowerShell,
};
//******************************************************************************
enum emMSGTypeExtension
{
    emMSGExtensionDevicePassThroughDirect = emMSGExtension + 1,
    emMSGExtensionTaskScheduler,
    emMSGExtensionShellMonitor,
    emMSGExtensionHarddiskDeviceControl,
    emMSGExtensionDnsQuery,
};
//******************************************************************************
enum emMSGConfig
{
    emMSGConfigDefault                         = 0,
    emMSGConfigPost                            = BIT(0),
    emMSGConfigSend                            = BIT(1),
    emMSGConfigRule                            = BIT(2),
    emMSGConfigEnable                          = emMSGConfigPost | emMSGConfigSend | emMSGConfigRule,
    emMSGConfigIncludeKernelEvent              = BIT(10),
    emMSGConfigFetchRpcCaller                  = BIT(11),
    emMSGConfigFetchSystemRpcCaller            = BIT(12),
};
//******************************************************************************
enum emMSGAction
{
    emMSGActionDefault                         = 0,
    emMSGActionPass                            = 0,
    emMSGActionBlock                           = BIT(0),
    emMSGActionRedirect                        = BIT(1),
    emMSGActionGrantedAccess                   = BIT(2),
    emMSGActionTerminateProcess                = BIT(3),
    emMSGActionTerminateThread                 = BIT(4),
    emMSGActionLoadLibrary                     = BIT(5),
    emMSGActionLoadLibraryNoAlert              = BIT(6),
    emMSGActionLoadLibraryByCreateThread       = BIT(7),
    emMSGActionExecuteShellCode                = BIT(8),
    emMSGActionInjectInboundPacket             = BIT(9),
    emMSGActionInjectOutboundPacket            = BIT(10),
    emMSGActionIgnore                          = BIT(19),
    emMSGActionRecord                          = BIT(20),
};
//******************************************************************************
enum emMSGDataType
{
    //
    //    基本类型
    //
    emMSGDataUnknown                           = 0,
    emMSGDataULONG                             = 0x10000,
    emMSGDataULONGLONG                         = 0x20000,
    emMSGDataString                            = 0x30000,
    emMSGDataPath                              = 0x40000,
    emMSGDataBinary                            = 0x50000,
    emMSGDataCallstack                         = 0x60000,
    emMSGDataSocketIP                          = 0x70000,

#define MSG_GET_BASE_TYPE(type)                (type & 0xFFFF0000)

    //
    //    扩展类型
    //
    emMSGDataBool = emMSGDataULONG + 1,
    emMSGDataHex,
    emMSGDataProcessAccess,
    emMSGDataThreadAccess,
    emMSGDataFileAccess,
    emMSGDataFileShareAccess,
    emMSGDataFileAttributes,
    emMSGDataFileDisposition,
    emMSGDataFileOptions,
    emMSGDataFilePageProtection,
    emMSGDataRegAccess,
    emMSGDataRegOptions,
    emMSGDataRegType,
    emMSGDataSocketPort,

    emMSGDataTime = emMSGDataULONGLONG + 1,
};
//******************************************************************************
enum emMSGField
{
    //
    //    基本字段
    //
    emMSGFieldInvalid = -1,
    emMSGFieldCallstack = 0,
    emMSGFieldCurrentProcessCreateTime,
    emMSGFieldCurrentProcessName,
    emMSGFieldCurrentProcessPath,
    emMSGFieldCurrentProcessCommandline,
    emMSGFieldPrivateBegin,
    emMSGFieldPath = emMSGFieldPrivateBegin,

    //
    // 基本字段默认配置
    //
    emMSGFieldDefault = ~BIT(emMSGFieldCallstack),
    emMSGFieldInternal = -1 << emMSGFieldPrivateBegin,

    //
    // 扩展字段
    //
    emMSGFieldExtension = 32,
    emMSGFieldType,
    emMSGFieldSeqId,
    emMSGFieldStatus,
    emMSGFieldCurrentProcessId,
    emMSGFieldCurrentThreadId,
    emMSGFieldTime,
    emMSGFieldDetail,
    emMSGFieldModifiable,
    emMSGFieldModified,

    //
    // 用户扩展字段
    //
    emMSGFieldCustomExtension = 1000,
};
//******************************************************************************
enum emMSGStatus
{
    emMSGStatusEnumBegin = 0x10000000,
    emMSGStatusEnumEnd,
};
//******************************************************************************
#pragma pack(push, 1)
//******************************************************************************
//
//    【驱动 --> 应用层】
//
//******************************************************************************
struct cxMSGHeader
{
    ULONG                Type;
    ULONG                Length;
    ULONG                Status;
    ULONG                Config;
    ULONG                SeqId;
    ULONG                Fields;
    ULONG                CurrentProcessId;
    ULONG                CurrentThreadId;
    ULONG                Modifiable:1;
    ULONG                Modified:1;
    ULONG                FirstEvent:1;
    ULONG                NamedPipe:1;
    ULONG                Suspicious:1;
    ULONG                Reserved0:27;
    ULONG                RpcCallerProcessId;
    ULONGLONG            RuleId;
    ULONGLONG            Time;

    //
    //    后面跟着多个cxMSGDataHeader + Data
    //
};
//******************************************************************************
struct cxMSGDataHeader 
{
    ULONG                Type;
    ULONG                Length;
    
    template<typename T>
    T*      GetData     (void)                { return (T*)(this + 1); }
    PVOID   GetData     (void)                { return (PVOID)(this + 1); }

    cxMSGDataHeader* Next(void)               { return (cxMSGDataHeader*)((ULONG_PTR)this + Length); }
};
//******************************************************************************
struct cxMSGDataIP
{
    enum {
        emIPNone,
        emIPv4,
        emIPv6,
    };

    ULONG               Type;
    union {
	    UCHAR           IPv6[16];
	    struct {
		    UCHAR       Zero[10];
		    USHORT      FFFF;
		    ULONG       IP;
	    }               IPv4;
    };

    cxMSGDataIP(void)
    {
        Type = emIPNone;
        memset(IPv6, 0, sizeof(IPv6));
    }

    bool IsIPv4() const
    {
        if (Type != emIPv6)
            return true;

        UCHAR Zero[16] = {};

        if (0 == memcmp(IPv6, Zero, 16))
            return true;
   
        if (0 == memcmp(IPv4.Zero, Zero, 10) && IPv4.FFFF == 0xFFFF)
            return true;

        return false;
    }
};

typedef const cxMSGDataIP& cxMSGDataIPRef;
//******************************************************************************
struct cxMSGAction
{
    ULONG                Action;
    union {
        ULONG            Params[3];
        ULONG            Access;
        struct {
            ULONG        ProcessId;
            ULONG        IP;
            ULONG        Port;
        };
    };
};
//******************************************************************************
//
//    【用户层 --> 驱动层】
//
//******************************************************************************
struct cxMSGUserHeader 
{
    ULONG                Type;
    ULONG                LicenseVersion                = MONITOR_LICENSE_VERSION;
};
//******************************************************************************
template<ULONG TYPE, typename T = void>
struct cxMSGUser : public cxMSGUserHeader, public T
{
    static constexpr auto TYPE = TYPE;

    cxMSGUser            (void)                { Type = TYPE; }
    T*                   GetData(void)         { return this; }
};
//******************************************************************************
template<ULONG TYPE>
struct cxMSGUser<TYPE, void> : public cxMSGUserHeader
{
    static constexpr auto TYPE = TYPE;

    cxMSGUser            (void)                { Type = TYPE; }
};
//******************************************************************************
enum emMSGUser
{
    emMSGUserBase                              = 0,
    emMSGUserControl                           = 1234,
    emMSGUserConnect                           = emMSGUserBase + 1,
};
//******************************************************************************
struct cxMSGUserConnect : public cxMSGUser<emMSGUserConnect> 
{
    ULONG                Version               = MONITOR_VERSION;
};
//******************************************************************************
enum
{
    emUserSetGlobalConfig = emMSGUserControl + 1,
    emUserGetGlobalConfig,
    emUserSetSessionConfig,
    emUserGetSessionConfig,
    emUserSetMSGConfig,
    emUserGetMSGConfig,
    emUserEnableProtect,
    emUserDisableProtect,
    emUserAddProtectRule,
    emUserRemoveProtectRule,
    emUserRemoveAllProtectRule,
    emUserEnumProtectRule,
    emUserSetGlobalFilter,
    emUserGetGlobalFilter,
    emUserSetRedirectorRules,
    emUserRemoveRedirectorRules,
    emUserSetHiddenRules,
    emUserRemoveHiddenRules,
    emUserSetMSGRules,
    emUserRemoveMSGRules,
    emUserSetSandboxRules,
    emUserRemoveSandboxRules,

    emAPIBegin = emMSGUserControl + 100,
    emAPIOpenProcess,
    emAPIDeleteFile,
    emAPITerminateProcess,
    emAPIEnd,
};
//******************************************************************************
struct cxUserGlobalConfig
{
    union {
        struct {
            ULONG        SwitchIncludeVS:1;
            ULONG        SwitchIncludeSelf:1;
            ULONG        SwitchQueryCreateFileAttributes:1;
            ULONG        SwitchOther:29;
            ULONG        LogLevel;
            ULONG        MaxCallstack;
            ULONG        MaxBinaryData;
        };

        ULONG            Data[32];
    };

    cxUserGlobalConfig()
    {
        memset(Data, 0, sizeof(Data));

        MaxCallstack = 64;
        MaxBinaryData = 4096;
        SwitchIncludeVS = TRUE;
        SwitchIncludeSelf = FALSE;
        SwitchQueryCreateFileAttributes = FALSE;
    }
};
//******************************************************************************
struct cxUserSessionConfig
{
    union {
		struct {
           ULONG        MSGTimeoutMS;
           ULONG        MSGTimeoutProtectCount;
           ULONG        MSGTimeoutProtectTimeMS;
           ULONG        MSGPostTimeoutMS;
           ULONG        FilterProcessOpenOnlyModifiable:1;
           ULONG        FilterThreadOpenOnlyModifiable:1;
           ULONG        FilterFileCreateOnlyModifiable:1;
           ULONG        FilterFileCloseOnlyModified:1;
           ULONG        FilterRegOpenOnlyModifiable:1;
           ULONG        FilterFileWriteOnlyFirstEvent:1;
           ULONG        FilterFileReadOnlyFirstEvent:1;
           ULONG        FilterFileWriteIgnoreNamedPipe:1;
           ULONG        FilterFileReadIgnoreNamedPipe:1;
           ULONG        FilterFileFindOnlyFirstEvent:1;
           ULONG        FilterOther:22;
        };

        ULONG           Data[32];
	};

    cxUserSessionConfig()
    {
        memset(Data, 0, sizeof(Data));
        
        MSGTimeoutMS = 5000;
        MSGPostTimeoutMS = 50000;
    }
};
//******************************************************************************
struct cxUserMSGConfig
{
    ULONG        Config[emMSGMax];
    ULONG        Fields[emMSGMax];

    cxUserMSGConfig()
    {
        for (int i = 0; i < emMSGMax; i++)
            Config[i] = (ULONG)emMSGConfigDefault;

        for (int i = 0; i < emMSGMax; i++)
            Fields[i] = (ULONG)emMSGFieldDefault;
    }
};
//******************************************************************************
enum emUserProtectType
{
    emProtectTypeTrustedProcess = BIT(0),
    emProtectTypeProcessPath = BIT(1),
    emProtectTypeFilePath = BIT(2),
    emProtectTypeRegPath = BIT(3),
    emProtectTypeIgnoredProcess = BIT(11),
    emProtectTypeValidWhenSessionConnected = BIT(12),
};
//******************************************************************************
struct cxUserProtectItem
{
    ULONG        ProtectType;
    WCHAR        Path[MONITOR_MAX_BUFFER];
};
//******************************************************************************
struct cxUserGlobalFilter
{
    struct PortFilter
    {
        ULONG   Count;
        USHORT  Port[MONITOR_MAX_QUICK_FILTER_COUNT];
    };

    PortFilter  SendPorts;
    PortFilter  RecvPorts;
    PortFilter  SendToPorts;
    PortFilter  RecvFromPorts;

    cxUserGlobalFilter()
    {
        memset(&SendPorts, 0, sizeof(SendPorts));
        memset(&RecvPorts, 0, sizeof(RecvPorts));
        memset(&SendToPorts, 0, sizeof(SendToPorts));
        memset(&RecvFromPorts, 0, sizeof(RecvFromPorts));
    }
};
//******************************************************************************
struct cxUserStringData
{
    CHAR        Data[1];
};
//******************************************************************************
struct cxUserStringRedirectorRules : public cxUserStringData
{
    // 
    // processes空表示所有进程， files不能为空
    //
	// 	[
	// 		{
	// 			"processes": [],
	// 			"files": [
	// 				{ "source": "", "target": "" }
	// 			],
	// 		}
	// 	]
};
//******************************************************************************
struct cxUserStringHiddenRules : public cxUserStringData
{
    //
    // processes空表示所有进程， files不能为空
    //
	// 	[
	// 		{
	// 			"processes": [ ],
	// 			"files": [ ],
    //          "ignore_files": []
	// 		}
	// 	]
};
//******************************************************************************
struct cxUserStringMSGRules : public cxUserStringData
{
	// 	{
    //      "rules": [
    //      {
    //         "action": 1,
    //         "event": "ProcessCreate",
    //         "matcher": {
    //             "and": [
    //                 { "match": [ "CurrentProcessPath", "*\\cmd.exe" ] },
    //                 { "match": [ "Path", "*\\notepad.exe" ] },
    //                 { "end": 0 }
    //             ]
    //         }
    //     }
    //     ]
	// 	}
};
//******************************************************************************
struct cxUserStringSandboxRules : public cxUserStringData
{
    //
    // processes不能为空， files空表示所有的文件
    //
    // [
    //     {
    //         "processes": [],
    //         "files": [],
    //         "ignore_files": [],
    //         "forbid_files": [],
    //         "sandbox_name": "test",
    //         "sandbox_root": "C:\\sandbox",
    //         "include_child_processes": true,
    //         "include_exist_processes": false
    //     }
    // ]
};
//******************************************************************************
struct cxAPIOpenProcess
{
    ULONG       ProcessId;
    ULONG       DesiredAccess;

    struct Result
    {
        ULONG   ProcessHandle;
    };
};
//******************************************************************************
struct cxAPITerminateProcess
{
    ULONG       ProcessId;
};
//******************************************************************************
struct cxAPIDeleteFile
{
    WCHAR       Path[MONITOR_MAX_BUFFER];
    ULONG       CloseAllHandles = TRUE;
};
//******************************************************************************
#pragma pack(pop)
//******************************************************************************
typedef cxMSGUser<emUserSetGlobalConfig, cxUserGlobalConfig> cxMSGUserSetGlobalConfig;
typedef cxMSGUser<emUserGetGlobalConfig, cxUserGlobalConfig> cxMSGUserGetGlobalConfig;
typedef cxMSGUser<emUserSetSessionConfig, cxUserSessionConfig> cxMSGUserSetSessionConfig;
typedef cxMSGUser<emUserGetSessionConfig, cxUserSessionConfig> cxMSGUserGetSessionConfig;
typedef cxMSGUser<emUserSetMSGConfig, cxUserMSGConfig> cxMSGUserSetMSGConfig;
typedef cxMSGUser<emUserGetMSGConfig, cxUserMSGConfig> cxMSGUserGetMSGConfig;
typedef cxMSGUser<emUserEnableProtect> cxMSGUserEnableProtect;
typedef cxMSGUser<emUserDisableProtect> cxMSGUserDisableProtect;
typedef cxMSGUser<emUserAddProtectRule, cxUserProtectItem> cxMSGUserAddProtectRule;
typedef cxMSGUser<emUserRemoveProtectRule, cxUserProtectItem> cxMSGUserRemoveProtectRule;
typedef cxMSGUser<emUserRemoveAllProtectRule> cxMSGUserRemoveAllProtectRule;
typedef cxMSGUser<emUserEnumProtectRule> cxMSGUserEnumProtectRule;
typedef cxMSGUser<emUserRemoveAllProtectRule> cxMSGUserRemoveAllProtectRule;
typedef cxMSGUser<emUserEnumProtectRule> cxMSGUserEnumProtectRule;
typedef cxMSGUser<emUserSetGlobalFilter, cxUserGlobalFilter> cxMSGUserSetGlobalFilter;
typedef cxMSGUser<emUserGetGlobalFilter, cxUserGlobalFilter> cxMSGUserGetGlobalFilter;
typedef cxMSGUser<emUserSetRedirectorRules, cxUserStringRedirectorRules> cxMSGUserSetRedirectorRules;
typedef cxMSGUser<emUserRemoveRedirectorRules> cxMSGUserRemoveRedirectorRules;
typedef cxMSGUser<emUserSetHiddenRules, cxUserStringHiddenRules> cxMSGUserSetHiddenRules;
typedef cxMSGUser<emUserRemoveHiddenRules> cxMSGUserRemoveHiddenRules;
typedef cxMSGUser<emUserSetMSGRules, cxUserStringMSGRules> cxMSGUserSetMSGRules;
typedef cxMSGUser<emUserRemoveMSGRules> cxMSGUserRemoveMSGRules;
typedef cxMSGUser<emUserSetSandboxRules, cxUserStringSandboxRules> cxMSGUserSetSandboxRules;
typedef cxMSGUser<emUserRemoveSandboxRules> cxMSGUserRemoveSandboxRules;
//******************************************************************************
typedef cxMSGUser<emAPIOpenProcess, cxAPIOpenProcess> cxMSGAPIOpenProcess;
typedef cxMSGUser<emAPITerminateProcess, cxAPITerminateProcess> cxMSGAPITerminateProcess;
typedef cxMSGUser<emAPIDeleteFile, cxAPIDeleteFile> cxMSGAPIDeleteFile;
//******************************************************************************
#endif
