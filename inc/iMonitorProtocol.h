//******************************************************************************
/*++
	FileName:		iMonitorProtocol.h
	Description:

--*/
//******************************************************************************
#ifndef __iMonitorProtocol_FE59B1CD_4EA9_4705_963C_DED434EF01BD__
#define __iMonitorProtocol_FE59B1CD_4EA9_4705_963C_DED434EF01BD__
//******************************************************************************
class MonitorMessage : public IMonitorMessage
{
public:
	auto CurrentProcessCreateTime() { return GetTime(emMSGFieldCurrentProcessCreateTime); };
	auto CurrentProcessName() { return GetString(emMSGFieldCurrentProcessName); };
	auto CurrentProcessPath() { return GetString(emMSGFieldCurrentProcessPath); };
	auto CurrentProcessCommandline() { return GetString(emMSGFieldCurrentProcessCommandline); };
	
	bool IsMatchCurrentProcessName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCurrentProcessName, Pattern, IgnoreCase); }
	bool IsMatchCurrentProcessPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCurrentProcessPath, Pattern, IgnoreCase); }
	bool IsMatchCurrentProcessCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCurrentProcessCommandline, Pattern, IgnoreCase); }

protected:
	LPCWSTR GetPath(ULONG Index) { return GetString(Index); }
	bool GetBool(ULONG Index) { return GetULONG(Index) == TRUE; }
	ULONG GetHex(ULONG Index) { return GetULONG(Index); }
	ULONG GetProcessAccess(ULONG Index) { return GetULONG(Index); }
	ULONG GetThreadAccess(ULONG Index) { return GetULONG(Index); }
	ULONG GetFileAccess(ULONG Index) { return GetULONG(Index); }
	ULONG GetFileShareAccess(ULONG Index) { return GetULONG(Index); }
	ULONG GetFileAttributes(ULONG Index) { return GetULONG(Index); }
	ULONG GetFileDisposition(ULONG Index) { return GetULONG(Index); }
	ULONG GetFileOptions(ULONG Index) { return GetULONG(Index); }
	ULONG GetFilePageProtection(ULONG Index) { return GetULONG(Index); }
	ULONG GetRegAccess(ULONG Index) { return GetULONG(Index); }
	ULONG GetRegOptions(ULONG Index) { return GetULONG(Index); }
	ULONG GetRegType(ULONG Index) { return GetULONG(Index); }
	cxMSGDataIP GetSocketIP(ULONG Index) { return GetIP(Index); }
	USHORT GetSocketPort(ULONG Index) { return (SHORT)GetULONG(Index); }
	ULONGLONG GetTime(ULONG Index) { return GetULONGLONG(Index); }
};
//******************************************************************************
class cxMSGProcessCreate : public MonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCommandline, Pattern, IgnoreCase); }
	bool IsMatchParentPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldParentPath, Pattern, IgnoreCase); }
	bool IsMatchParentCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldParentCommandline, Pattern, IgnoreCase); }
};
class cxMSGProcessExit : public MonitorMessage
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
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGProcessOpen : public MonitorMessage
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
		emMSGFieldParentProcessId,
		emMSGFieldDesiredAccess,
		emMSGFieldDuplicate,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ParentProcessId() { return GetULONG(emMSGFieldParentProcessId); }
	auto DesiredAccess() { return GetProcessAccess(emMSGFieldDesiredAccess); }
	auto Duplicate() { return GetBool(emMSGFieldDuplicate); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGThreadCreate : public MonitorMessage
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
		emMSGFieldThreadId,
		emMSGFieldStartAddress,
		emMSGFieldRemoteThread,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ThreadId() { return GetULONG(emMSGFieldThreadId); }
	auto StartAddress() { return GetULONGLONG(emMSGFieldStartAddress); }
	auto RemoteThread() { return GetBool(emMSGFieldRemoteThread); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGThreadExit : public MonitorMessage
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
		emMSGFieldThreadId,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ThreadId() { return GetULONG(emMSGFieldThreadId); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGThreadOpen : public MonitorMessage
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
		emMSGFieldParentProcessId,
		emMSGFieldDesiredAccess,
		emMSGFieldDuplicate,
		emMSGFieldThreadId,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ParentProcessId() { return GetULONG(emMSGFieldParentProcessId); }
	auto DesiredAccess() { return GetThreadAccess(emMSGFieldDesiredAccess); }
	auto Duplicate() { return GetBool(emMSGFieldDuplicate); }
	auto ThreadId() { return GetULONG(emMSGFieldThreadId); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGImageLoad : public MonitorMessage
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
		emMSGFieldImageBase,
		emMSGFieldImageSize,
		emMSGFieldIsKernelImage,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ImageBase() { return GetULONGLONG(emMSGFieldImageBase); }
	auto ImageSize() { return GetULONGLONG(emMSGFieldImageSize); }
	auto IsKernelImage() { return GetBool(emMSGFieldIsKernelImage); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGDriverLoad : public MonitorMessage
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
		emMSGFieldImageBase,
		emMSGFieldImageSize,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ImageBase() { return GetULONGLONG(emMSGFieldImageBase); }
	auto ImageSize() { return GetULONGLONG(emMSGFieldImageSize); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGProcessStart : public MonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCommandline, Pattern, IgnoreCase); }
	bool IsMatchParentPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldParentPath, Pattern, IgnoreCase); }
	bool IsMatchParentCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldParentCommandline, Pattern, IgnoreCase); }
};
class cxMSGThreadStart : public MonitorMessage
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
		emMSGFieldThreadId,
		emMSGFieldStartAddress,
		emMSGFieldRemoteThread,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ThreadId() { return GetULONG(emMSGFieldThreadId); }
	auto StartAddress() { return GetULONGLONG(emMSGFieldStartAddress); }
	auto RemoteThread() { return GetBool(emMSGFieldRemoteThread); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileCreate : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldAttributes,
		emMSGFieldAccess,
		emMSGFieldShareAccess,
		emMSGFieldCreateDisposition,
		emMSGFieldCreateOptions,
		emMSGFieldExistsFileAttributes,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Attributes() { return GetFileAttributes(emMSGFieldAttributes); }
	auto Access() { return GetFileAccess(emMSGFieldAccess); }
	auto ShareAccess() { return GetFileShareAccess(emMSGFieldShareAccess); }
	auto CreateDisposition() { return GetFileDisposition(emMSGFieldCreateDisposition); }
	auto CreateOptions() { return GetFileOptions(emMSGFieldCreateOptions); }
	auto ExistsFileAttributes() { return GetFileAttributes(emMSGFieldExistsFileAttributes); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostCreate : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldAttributes,
		emMSGFieldAccess,
		emMSGFieldShareAccess,
		emMSGFieldCreateDisposition,
		emMSGFieldCreateOptions,
		emMSGFieldInformation,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Attributes() { return GetFileAttributes(emMSGFieldAttributes); }
	auto Access() { return GetFileAccess(emMSGFieldAccess); }
	auto ShareAccess() { return GetFileShareAccess(emMSGFieldShareAccess); }
	auto CreateDisposition() { return GetFileDisposition(emMSGFieldCreateDisposition); }
	auto CreateOptions() { return GetFileOptions(emMSGFieldCreateOptions); }
	auto Information() { return GetULONG(emMSGFieldInformation); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileQueryOpen : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostQueryOpen : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldCreationTime,
		emMSGFieldLastAccessTime,
		emMSGFieldLastWriteTime,
		emMSGFieldChangeTime,
		emMSGFieldFileSize,
		emMSGFieldFileAttributes,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto CreationTime() { return GetTime(emMSGFieldCreationTime); }
	auto LastAccessTime() { return GetTime(emMSGFieldLastAccessTime); }
	auto LastWriteTime() { return GetTime(emMSGFieldLastWriteTime); }
	auto ChangeTime() { return GetTime(emMSGFieldChangeTime); }
	auto FileSize() { return GetULONGLONG(emMSGFieldFileSize); }
	auto FileAttributes() { return GetFileAttributes(emMSGFieldFileAttributes); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileCleanup : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldInformation,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Information() { return GetULONG(emMSGFieldInformation); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileCreateSection : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldPageProtection,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto PageProtection() { return GetFilePageProtection(emMSGFieldPageProtection); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostCreateSection : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldPageProtection,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto PageProtection() { return GetFilePageProtection(emMSGFieldPageProtection); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileRead : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldReadLength,
		emMSGFieldOffset,
		emMSGFieldBuffer,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ReadLength() { return GetULONG(emMSGFieldReadLength); }
	auto Offset() { return GetULONGLONG(emMSGFieldOffset); }
	auto Buffer() { return GetULONGLONG(emMSGFieldBuffer); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostRead : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldReadLength,
		emMSGFieldOffset,
		emMSGFieldBuffer,
		emMSGFieldReturnLength,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ReadLength() { return GetULONG(emMSGFieldReadLength); }
	auto Offset() { return GetULONGLONG(emMSGFieldOffset); }
	auto Buffer() { return GetULONGLONG(emMSGFieldBuffer); }
	auto ReturnLength() { return GetULONG(emMSGFieldReturnLength); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileWrite : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldWriteLength,
		emMSGFieldOffset,
		emMSGFieldBuffer,
		emMSGFieldData,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto WriteLength() { return GetULONG(emMSGFieldWriteLength); }
	auto Offset() { return GetULONGLONG(emMSGFieldOffset); }
	auto Buffer() { return GetULONGLONG(emMSGFieldBuffer); }
	auto Data() { return GetBinary(emMSGFieldData); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostWrite : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldWriteLength,
		emMSGFieldOffset,
		emMSGFieldBuffer,
		emMSGFieldData,
		emMSGFieldReturnLength,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto WriteLength() { return GetULONG(emMSGFieldWriteLength); }
	auto Offset() { return GetULONGLONG(emMSGFieldOffset); }
	auto Buffer() { return GetULONGLONG(emMSGFieldBuffer); }
	auto Data() { return GetBinary(emMSGFieldData); }
	auto ReturnLength() { return GetULONG(emMSGFieldReturnLength); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileCreateHardLink : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldLinkPath,
		emMSGFieldReplaceIfExists,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto LinkPath() { return GetPath(emMSGFieldLinkPath); }
	auto ReplaceIfExists() { return GetBool(emMSGFieldReplaceIfExists); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchLinkPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldLinkPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostCreateHardLink : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldLinkPath,
		emMSGFieldReplaceIfExists,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto LinkPath() { return GetPath(emMSGFieldLinkPath); }
	auto ReplaceIfExists() { return GetBool(emMSGFieldReplaceIfExists); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchLinkPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldLinkPath, Pattern, IgnoreCase); }
};
class cxMSGFileRename : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldNewPath,
		emMSGFieldReplaceIfExists,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto NewPath() { return GetPath(emMSGFieldNewPath); }
	auto ReplaceIfExists() { return GetBool(emMSGFieldReplaceIfExists); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchNewPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldNewPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostRename : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldNewPath,
		emMSGFieldReplaceIfExists,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto NewPath() { return GetPath(emMSGFieldNewPath); }
	auto ReplaceIfExists() { return GetBool(emMSGFieldReplaceIfExists); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchNewPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldNewPath, Pattern, IgnoreCase); }
};
class cxMSGFileDelete : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostDelete : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileSetSize : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldSize,
		emMSGFieldSizeType,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Size() { return GetULONGLONG(emMSGFieldSize); }
	auto SizeType() { return GetULONG(emMSGFieldSizeType); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostSetSize : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldSize,
		emMSGFieldSizeType,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Size() { return GetULONGLONG(emMSGFieldSize); }
	auto SizeType() { return GetULONG(emMSGFieldSizeType); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileSetBasicInfo : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldCreationTime,
		emMSGFieldLastAccessTime,
		emMSGFieldLastWriteTime,
		emMSGFieldChangeTime,
		emMSGFieldFileAttributes,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto CreationTime() { return GetTime(emMSGFieldCreationTime); }
	auto LastAccessTime() { return GetTime(emMSGFieldLastAccessTime); }
	auto LastWriteTime() { return GetTime(emMSGFieldLastWriteTime); }
	auto ChangeTime() { return GetTime(emMSGFieldChangeTime); }
	auto FileAttributes() { return GetFileAttributes(emMSGFieldFileAttributes); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFilePostSetBasicInfo : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldCreationTime,
		emMSGFieldLastAccessTime,
		emMSGFieldLastWriteTime,
		emMSGFieldChangeTime,
		emMSGFieldFileAttributes,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto CreationTime() { return GetTime(emMSGFieldCreationTime); }
	auto LastAccessTime() { return GetTime(emMSGFieldLastAccessTime); }
	auto LastWriteTime() { return GetTime(emMSGFieldLastWriteTime); }
	auto ChangeTime() { return GetTime(emMSGFieldChangeTime); }
	auto FileAttributes() { return GetFileAttributes(emMSGFieldFileAttributes); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGFileFindFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldFindName,
		emMSGFieldRestartScan,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto FindName() { return GetPath(emMSGFieldFindName); }
	auto RestartScan() { return GetBool(emMSGFieldRestartScan); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchFindName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldFindName, Pattern, IgnoreCase); }
};
class cxMSGFilePostFindFile : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldFindName,
		emMSGFieldRestartScan,
		emMSGFieldFileName,
		emMSGFieldCreationTime,
		emMSGFieldLastAccessTime,
		emMSGFieldLastWriteTime,
		emMSGFieldChangeTime,
		emMSGFieldFileSize,
		emMSGFieldFileAttributes,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto FindName() { return GetPath(emMSGFieldFindName); }
	auto RestartScan() { return GetBool(emMSGFieldRestartScan); }
	auto FileName() { return GetPath(emMSGFieldFileName); }
	auto CreationTime() { return GetTime(emMSGFieldCreationTime); }
	auto LastAccessTime() { return GetTime(emMSGFieldLastAccessTime); }
	auto LastWriteTime() { return GetTime(emMSGFieldLastWriteTime); }
	auto ChangeTime() { return GetTime(emMSGFieldChangeTime); }
	auto FileSize() { return GetULONGLONG(emMSGFieldFileSize); }
	auto FileAttributes() { return GetFileAttributes(emMSGFieldFileAttributes); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchFindName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldFindName, Pattern, IgnoreCase); }
	bool IsMatchFileName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldFileName, Pattern, IgnoreCase); }
};
class cxMSGRegCreateKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldOptions,
		emMSGFieldDesiredAccess,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Options() { return GetRegOptions(emMSGFieldOptions); }
	auto DesiredAccess() { return GetRegAccess(emMSGFieldDesiredAccess); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegPostCreateKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldOptions,
		emMSGFieldDesiredAccess,
		emMSGFieldDisposition,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Options() { return GetRegOptions(emMSGFieldOptions); }
	auto DesiredAccess() { return GetRegAccess(emMSGFieldDesiredAccess); }
	auto Disposition() { return GetULONG(emMSGFieldDisposition); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegOpenKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldOptions,
		emMSGFieldDesiredAccess,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Options() { return GetRegOptions(emMSGFieldOptions); }
	auto DesiredAccess() { return GetRegAccess(emMSGFieldDesiredAccess); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegPostOpenKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldOptions,
		emMSGFieldDesiredAccess,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Options() { return GetRegOptions(emMSGFieldOptions); }
	auto DesiredAccess() { return GetRegAccess(emMSGFieldDesiredAccess); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegDeleteKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegPostDeleteKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegRenameKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldNewName,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto NewName() { return GetString(emMSGFieldNewName); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchNewName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldNewName, Pattern, IgnoreCase); }
};
class cxMSGRegPostRenameKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldNewName,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto NewName() { return GetString(emMSGFieldNewName); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchNewName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldNewName, Pattern, IgnoreCase); }
};
class cxMSGRegEnumKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldIndex,
		emMSGFieldInformationClass,
		emMSGFieldInformationLength,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Index() { return GetULONG(emMSGFieldIndex); }
	auto InformationClass() { return GetULONG(emMSGFieldInformationClass); }
	auto InformationLength() { return GetULONG(emMSGFieldInformationLength); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegPostEnumKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldIndex,
		emMSGFieldInformationClass,
		emMSGFieldInformationLength,
		emMSGFieldResultLength,
		emMSGFieldInformation,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Index() { return GetULONG(emMSGFieldIndex); }
	auto InformationClass() { return GetULONG(emMSGFieldInformationClass); }
	auto InformationLength() { return GetULONG(emMSGFieldInformationLength); }
	auto ResultLength() { return GetULONG(emMSGFieldResultLength); }
	auto Information() { return GetBinary(emMSGFieldInformation); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGRegLoadKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldFilePath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto FilePath() { return GetString(emMSGFieldFilePath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchFilePath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldFilePath, Pattern, IgnoreCase); }
};
class cxMSGRegPostLoadKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldFilePath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto FilePath() { return GetString(emMSGFieldFilePath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchFilePath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldFilePath, Pattern, IgnoreCase); }
};
class cxMSGRegReplaceKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldOldFilePath,
		emMSGFieldNewFilePath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto OldFilePath() { return GetString(emMSGFieldOldFilePath); }
	auto NewFilePath() { return GetString(emMSGFieldNewFilePath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchOldFilePath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldOldFilePath, Pattern, IgnoreCase); }
	bool IsMatchNewFilePath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldNewFilePath, Pattern, IgnoreCase); }
};
class cxMSGRegPostReplaceKey : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldOldFilePath,
		emMSGFieldNewFilePath,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto OldFilePath() { return GetString(emMSGFieldOldFilePath); }
	auto NewFilePath() { return GetString(emMSGFieldNewFilePath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchOldFilePath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldOldFilePath, Pattern, IgnoreCase); }
	bool IsMatchNewFilePath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldNewFilePath, Pattern, IgnoreCase); }
};
class cxMSGRegDeleteValue : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldValueName,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ValueName() { return GetString(emMSGFieldValueName); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchValueName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldValueName, Pattern, IgnoreCase); }
};
class cxMSGRegPostDeleteValue : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldValueName,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ValueName() { return GetString(emMSGFieldValueName); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchValueName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldValueName, Pattern, IgnoreCase); }
};
class cxMSGRegSetValue : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldValueName,
		emMSGFieldDataType,
		emMSGFieldData,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ValueName() { return GetString(emMSGFieldValueName); }
	auto DataType() { return GetRegType(emMSGFieldDataType); }
	auto Data() { return GetBinary(emMSGFieldData); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchValueName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldValueName, Pattern, IgnoreCase); }
};
class cxMSGRegPostSetValue : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldValueName,
		emMSGFieldDataType,
		emMSGFieldData,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ValueName() { return GetString(emMSGFieldValueName); }
	auto DataType() { return GetRegType(emMSGFieldDataType); }
	auto Data() { return GetBinary(emMSGFieldData); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchValueName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldValueName, Pattern, IgnoreCase); }
};
class cxMSGRegQueryValue : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldValueName,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ValueName() { return GetString(emMSGFieldValueName); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchValueName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldValueName, Pattern, IgnoreCase); }
};
class cxMSGRegPostQueryValue : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldValueName,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto ValueName() { return GetString(emMSGFieldValueName); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchValueName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldValueName, Pattern, IgnoreCase); }
};
class cxMSGSocketCreate : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }

};
class cxMSGSocketControl : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldCode,
		emMSGFieldInputLength,
		emMSGFieldOutputLength,
		emMSGFieldInputData,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto Code() { return GetULONG(emMSGFieldCode); }
	auto InputLength() { return GetULONG(emMSGFieldInputLength); }
	auto OutputLength() { return GetULONG(emMSGFieldOutputLength); }
	auto InputData() { return GetBinary(emMSGFieldInputData); }

};
class cxMSGSocketPostControl : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldCode,
		emMSGFieldInputLength,
		emMSGFieldOutputLength,
		emMSGFieldInputData,
		emMSGFieldOutputData,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto Code() { return GetULONG(emMSGFieldCode); }
	auto InputLength() { return GetULONG(emMSGFieldInputLength); }
	auto OutputLength() { return GetULONG(emMSGFieldOutputLength); }
	auto InputData() { return GetBinary(emMSGFieldInputData); }
	auto OutputData() { return GetBinary(emMSGFieldOutputData); }

};
class cxMSGSocketConnect : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldSuperConnect,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto SuperConnect() { return GetBool(emMSGFieldSuperConnect); }

};
class cxMSGSocketPostConnect : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldSuperConnect,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto SuperConnect() { return GetBool(emMSGFieldSuperConnect); }

};
class cxMSGSocketSend : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGSocketRecv : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGSocketPostRecv : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGSocketSendTo : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGSocketRecvFrom : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGSocketPostRecvFrom : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGSocketListen : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }

};
class cxMSGSocketPostListen : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }

};
class cxMSGSocketAccept : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGSocketPostAccept : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldSocketObject,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto SocketObject() { return GetULONGLONG(emMSGFieldSocketObject); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPTcpConnect : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPUdpConnect : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPICMPConnect : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPTcpAccept : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPUdpAccept : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPICMPAccept : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPSend : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGWFPRecv : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGWFPSendTo : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGWFPRecvFrom : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGWFPICMPSendTo : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGWFPICMPRecvFrom : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }

};
class cxMSGWFPTcpBind : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGWFPUdpBind : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
	};

public:
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }

};
class cxMSGHTTPRequest : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldMethod,
		emMSGFieldHost,
		emMSGFieldUri,
		emMSGFieldUrl,
		emMSGFieldHeader,
		emMSGFieldData,
		emMSGFieldStatus,
		emMSGFieldResponseHeader,
		emMSGFieldResponseData,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto Method() { return GetString(emMSGFieldMethod); }
	auto Host() { return GetString(emMSGFieldHost); }
	auto Uri() { return GetString(emMSGFieldUri); }
	auto Url() { return GetString(emMSGFieldUrl); }
	auto Header() { return GetString(emMSGFieldHeader); }
	auto Data() { return GetBinary(emMSGFieldData); }
	auto Status() { return GetULONG(emMSGFieldStatus); }
	auto ResponseHeader() { return GetString(emMSGFieldResponseHeader); }
	auto ResponseData() { return GetBinary(emMSGFieldResponseData); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchMethod(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldMethod, Pattern, IgnoreCase); }
	bool IsMatchHost(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldHost, Pattern, IgnoreCase); }
	bool IsMatchUri(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldUri, Pattern, IgnoreCase); }
	bool IsMatchUrl(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldUrl, Pattern, IgnoreCase); }
	bool IsMatchHeader(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldHeader, Pattern, IgnoreCase); }
	bool IsMatchResponseHeader(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldResponseHeader, Pattern, IgnoreCase); }
};
class cxMSGExtensionDevicePassThroughDirect : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGExtensionTaskScheduler : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldName,
		emMSGFieldCommandline,
		emMSGFieldUser,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto Name() { return GetString(emMSGFieldName); }
	auto Commandline() { return GetString(emMSGFieldCommandline); }
	auto User() { return GetString(emMSGFieldUser); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldName, Pattern, IgnoreCase); }
	bool IsMatchCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCommandline, Pattern, IgnoreCase); }
	bool IsMatchUser(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldUser, Pattern, IgnoreCase); }
};
class cxMSGExtensionShellMonitor : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldReserved,
		emMSGFieldWindowClassName,
		emMSGFieldWindowName,
		emMSGFieldEvent,
	};

public:
	auto Reserved() { return GetString(emMSGFieldReserved); }
	auto WindowClassName() { return GetString(emMSGFieldWindowClassName); }
	auto WindowName() { return GetString(emMSGFieldWindowName); }
	auto Event() { return GetULONG(emMSGFieldEvent); }

	bool IsMatchReserved(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldReserved, Pattern, IgnoreCase); }
	bool IsMatchWindowClassName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldWindowClassName, Pattern, IgnoreCase); }
	bool IsMatchWindowName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldWindowName, Pattern, IgnoreCase); }
};
class cxMSGExtensionHarddiskDeviceControl : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldControlCode,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto ControlCode() { return GetULONG(emMSGFieldControlCode); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGExtensionDnsQuery : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldIP,
		emMSGFieldPort,
		emMSGFieldLocalIP,
		emMSGFieldLocalPort,
		emMSGFieldDataLength,
		emMSGFieldData,
		emMSGFieldDomain,
	};

public:
	auto IP() { return GetSocketIP(emMSGFieldIP); }
	auto Port() { return GetSocketPort(emMSGFieldPort); }
	auto LocalIP() { return GetSocketIP(emMSGFieldLocalIP); }
	auto LocalPort() { return GetSocketPort(emMSGFieldLocalPort); }
	auto DataLength() { return GetULONG(emMSGFieldDataLength); }
	auto Data() { return GetBinary(emMSGFieldData); }
	auto Domain() { return GetString(emMSGFieldDomain); }

	bool IsMatchDomain(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldDomain, Pattern, IgnoreCase); }
};
class cxMSGHookWriteProcessMemory : public MonitorMessage
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
		emMSGFieldBaseAddress,
		emMSGFieldSize,
		emMSGFieldBuffer,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto BaseAddress() { return GetULONGLONG(emMSGFieldBaseAddress); }
	auto Size() { return GetULONG(emMSGFieldSize); }
	auto Buffer() { return GetBinary(emMSGFieldBuffer); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGHookRpcCreateProcess : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
		emMSGFieldCommandline,
		emMSGFieldParentProcessId,
		emMSGFieldParentPath,
		emMSGFieldParentCommandline,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Commandline() { return GetString(emMSGFieldCommandline); }
	auto ParentProcessId() { return GetULONG(emMSGFieldParentProcessId); }
	auto ParentPath() { return GetPath(emMSGFieldParentPath); }
	auto ParentCommandline() { return GetString(emMSGFieldParentCommandline); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
	bool IsMatchCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCommandline, Pattern, IgnoreCase); }
	bool IsMatchParentPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldParentPath, Pattern, IgnoreCase); }
	bool IsMatchParentCommandline(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldParentCommandline, Pattern, IgnoreCase); }
};
class cxMSGHookSetWindowsHookEx : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldType,
		emMSGFieldThreadId,
		emMSGFieldHookProc,
		emMSGFieldInstance,
		emMSGFieldInstancePath,
	};

public:
	auto Type() { return GetULONG(emMSGFieldType); }
	auto ThreadId() { return GetULONG(emMSGFieldThreadId); }
	auto HookProc() { return GetULONGLONG(emMSGFieldHookProc); }
	auto Instance() { return GetULONGLONG(emMSGFieldInstance); }
	auto InstancePath() { return GetString(emMSGFieldInstancePath); }

	bool IsMatchInstancePath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldInstancePath, Pattern, IgnoreCase); }
};
class cxMSGHookCreateService : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldServiceName,
		emMSGFieldDisplayName,
		emMSGFieldBinPath,
		emMSGFieldServiceType,
		emMSGFieldStartType,
	};

public:
	auto ServiceName() { return GetString(emMSGFieldServiceName); }
	auto DisplayName() { return GetString(emMSGFieldDisplayName); }
	auto BinPath() { return GetString(emMSGFieldBinPath); }
	auto ServiceType() { return GetULONG(emMSGFieldServiceType); }
	auto StartType() { return GetULONG(emMSGFieldStartType); }

	bool IsMatchServiceName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldServiceName, Pattern, IgnoreCase); }
	bool IsMatchDisplayName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldDisplayName, Pattern, IgnoreCase); }
	bool IsMatchBinPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldBinPath, Pattern, IgnoreCase); }
};
class cxMSGHookStartService : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldServiceName,
	};

public:
	auto ServiceName() { return GetString(emMSGFieldServiceName); }

	bool IsMatchServiceName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldServiceName, Pattern, IgnoreCase); }
};
class cxMSGHookChangeServiceConfig : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldServiceName,
		emMSGFieldServiceType,
		emMSGFieldStartType,
	};

public:
	auto ServiceName() { return GetString(emMSGFieldServiceName); }
	auto ServiceType() { return GetULONG(emMSGFieldServiceType); }
	auto StartType() { return GetULONG(emMSGFieldStartType); }

	bool IsMatchServiceName(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldServiceName, Pattern, IgnoreCase); }
};
class cxMSGHookCoCreateInstance : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldContext,
		emMSGFieldClassId,
		emMSGFieldInterfaceId,
	};

public:
	auto Context() { return GetULONG(emMSGFieldContext); }
	auto ClassId() { return GetString(emMSGFieldClassId); }
	auto InterfaceId() { return GetString(emMSGFieldInterfaceId); }

	bool IsMatchClassId(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldClassId, Pattern, IgnoreCase); }
	bool IsMatchInterfaceId(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldInterfaceId, Pattern, IgnoreCase); }
};
class cxMSGHookSetContextThread : public MonitorMessage
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
		emMSGFieldThreadId,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ThreadId() { return GetULONG(emMSGFieldThreadId); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGHookQueueApcThread : public MonitorMessage
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
		emMSGFieldThreadId,
		emMSGFieldApcRoutine,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto ThreadId() { return GetULONG(emMSGFieldThreadId); }
	auto ApcRoutine() { return GetULONGLONG(emMSGFieldApcRoutine); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGHookMapViewOfSection : public MonitorMessage
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
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGHookReadProcessMemory : public MonitorMessage
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
		emMSGFieldBaseAddress,
		emMSGFieldSize,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto BaseAddress() { return GetULONGLONG(emMSGFieldBaseAddress); }
	auto Size() { return GetULONG(emMSGFieldSize); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGHookDuplicateHandle : public MonitorMessage
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
		emMSGFieldHandle,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }
	auto ProcessId() { return GetULONG(emMSGFieldProcessId); }
	auto Handle() { return GetULONG(emMSGFieldHandle); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGHookSendInput : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldType,
	};

public:
	auto Type() { return GetULONG(emMSGFieldType); }

};
class cxMSGHookShutdownSystem : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldRestart,
	};

public:
	auto Restart() { return GetBool(emMSGFieldRestart); }

};
class cxMSGHookSetSystemTime : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldTime,
	};

public:
	auto Time() { return GetULONGLONG(emMSGFieldTime); }

};
class cxMSGHookGetClipboardData : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldFormat,
	};

public:
	auto Format() { return GetULONG(emMSGFieldFormat); }

};
class cxMSGHookSetDeskWallpaper : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldPath,
	};

public:
	auto Path() { return GetString(emMSGFieldPath); }

	bool IsMatchPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldPath, Pattern, IgnoreCase); }
};
class cxMSGHookUseCamera : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldAction,
	};

public:
	auto Action() { return GetULONG(emMSGFieldAction); }

};
class cxMSGHookKeyLogger : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldType,
	};

public:
	auto Type() { return GetULONG(emMSGFieldType); }

};
class cxMSGHookPowerShell : public MonitorMessage
{
public:
	enum {
		emMSGFieldCallstack,
		emMSGFieldCurrentProcessCreateTime,
		emMSGFieldCurrentProcessName,
		emMSGFieldCurrentProcessPath,
		emMSGFieldCurrentProcessCommandline,
		emMSGFieldScriptPath,
		emMSGFieldCommand,
	};

public:
	auto ScriptPath() { return GetString(emMSGFieldScriptPath); }
	auto Command() { return GetString(emMSGFieldCommand); }

	bool IsMatchScriptPath(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldScriptPath, Pattern, IgnoreCase); }
	bool IsMatchCommand(LPCWSTR Pattern, bool IgnoreCase = true) { return IsMatch(emMSGFieldCommand, Pattern, IgnoreCase); }
};
//******************************************************************************
#endif

