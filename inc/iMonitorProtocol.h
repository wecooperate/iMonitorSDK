//******************************************************************************
/*++
	FileName:		iMonitorProtocol.h
	Description:

--*/
//******************************************************************************
#ifndef __iMonitorProtocol_FE59B1CD_4EA9_4705_963C_DED434EF01BD__
#define __iMonitorProtocol_FE59B1CD_4EA9_4705_963C_DED434EF01BD__
//******************************************************************************
class cxMonitorMessage : public IMonitorMessage
{
public:
	auto CurrentProcessCreateTime() { return GetTime(emMSGFieldCurrentProcessCreateTime); };
	auto CurrentProcessName() { return GetString(emMSGFieldCurrentProcessName); };
	auto CurrentProcessPath() { return GetString(emMSGFieldCurrentProcessPath); };
	auto CurrentProcessCommandline() { return GetString(emMSGFieldCurrentProcessCommandline); };
	
	bool IsMatchCurrentProcessName(LPCWSTR Pattern) { return IsMatch(emMSGFieldCurrentProcessName, Pattern); }
	bool IsMatchCurrentProcessPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldCurrentProcessPath, Pattern); }
	bool IsMatchCurrentProcessCommandline(LPCWSTR Pattern) { return IsMatch(emMSGFieldCurrentProcessCommandline, Pattern); }

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
	ULONG GetSocketIP(ULONG Index) { return GetULONG(Index); }
	USHORT GetSocketPort(ULONG Index) { return (SHORT)GetULONG(Index); }
	ULONGLONG GetTime(ULONG Index) { return GetULONGLONG(Index); }
};
//******************************************************************************
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
class cxMSGProcessExit : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGProcessOpen : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGThreadCreate : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGThreadExit : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGThreadOpen : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGImageLoad : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGProcessStart : public cxMonitorMessage
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
class cxMSGThreadStart : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileCreate : public cxMonitorMessage
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
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Attributes() { return GetFileAttributes(emMSGFieldAttributes); }
	auto Access() { return GetFileAccess(emMSGFieldAccess); }
	auto ShareAccess() { return GetFileShareAccess(emMSGFieldShareAccess); }
	auto CreateDisposition() { return GetFileDisposition(emMSGFieldCreateDisposition); }
	auto CreateOptions() { return GetFileOptions(emMSGFieldCreateOptions); }

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostCreate : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileQueryOpen : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostQueryOpen : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileCleanup : public cxMonitorMessage
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
		emMSGFieldModify,
	};

public:
	auto Path() { return GetPath(emMSGFieldPath); }
	auto Information() { return GetULONG(emMSGFieldInformation); }
	auto Modify() { return GetULONG(emMSGFieldModify); }

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileCreateSection : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostCreateSection : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileRead : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostRead : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileWrite : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostWrite : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileCreateHardLink : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchLinkPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldLinkPath, Pattern); }
};
class cxMSGFilePostCreateHardLink : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchLinkPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldLinkPath, Pattern); }
};
class cxMSGFileRename : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchNewPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldNewPath, Pattern); }
};
class cxMSGFilePostRename : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchNewPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldNewPath, Pattern); }
};
class cxMSGFileDelete : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostDelete : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileSetSize : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostSetSize : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileSetBasicInfo : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFilePostSetBasicInfo : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGFileFindFile : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchFindName(LPCWSTR Pattern) { return IsMatch(emMSGFieldFindName, Pattern); }
};
class cxMSGFilePostFindFile : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchFindName(LPCWSTR Pattern) { return IsMatch(emMSGFieldFindName, Pattern); }
	bool IsMatchFileName(LPCWSTR Pattern) { return IsMatch(emMSGFieldFileName, Pattern); }
};
class cxMSGRegCreateKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegPostCreateKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegOpenKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegPostOpenKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegDeleteKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegPostDeleteKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegRenameKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchNewName(LPCWSTR Pattern) { return IsMatch(emMSGFieldNewName, Pattern); }
};
class cxMSGRegPostRenameKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchNewName(LPCWSTR Pattern) { return IsMatch(emMSGFieldNewName, Pattern); }
};
class cxMSGRegEnumKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegPostEnumKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
};
class cxMSGRegLoadKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchFilePath(LPCWSTR Pattern) { return IsMatch(emMSGFieldFilePath, Pattern); }
};
class cxMSGRegPostLoadKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchFilePath(LPCWSTR Pattern) { return IsMatch(emMSGFieldFilePath, Pattern); }
};
class cxMSGRegReplaceKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchOldFilePath(LPCWSTR Pattern) { return IsMatch(emMSGFieldOldFilePath, Pattern); }
	bool IsMatchNewFilePath(LPCWSTR Pattern) { return IsMatch(emMSGFieldNewFilePath, Pattern); }
};
class cxMSGRegPostReplaceKey : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchOldFilePath(LPCWSTR Pattern) { return IsMatch(emMSGFieldOldFilePath, Pattern); }
	bool IsMatchNewFilePath(LPCWSTR Pattern) { return IsMatch(emMSGFieldNewFilePath, Pattern); }
};
class cxMSGRegDeleteValue : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchValueName(LPCWSTR Pattern) { return IsMatch(emMSGFieldValueName, Pattern); }
};
class cxMSGRegPostDeleteValue : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchValueName(LPCWSTR Pattern) { return IsMatch(emMSGFieldValueName, Pattern); }
};
class cxMSGRegSetValue : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchValueName(LPCWSTR Pattern) { return IsMatch(emMSGFieldValueName, Pattern); }
};
class cxMSGRegPostSetValue : public cxMonitorMessage
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

	bool IsMatchPath(LPCWSTR Pattern) { return IsMatch(emMSGFieldPath, Pattern); }
	bool IsMatchValueName(LPCWSTR Pattern) { return IsMatch(emMSGFieldValueName, Pattern); }
};
class cxMSGSocketCreate : public cxMonitorMessage
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
class cxMSGSocketControl : public cxMonitorMessage
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
class cxMSGSocketPostControl : public cxMonitorMessage
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
class cxMSGSocketConnect : public cxMonitorMessage
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
class cxMSGSocketPostConnect : public cxMonitorMessage
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
class cxMSGSocketSend : public cxMonitorMessage
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
class cxMSGSocketRecv : public cxMonitorMessage
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
class cxMSGSocketPostRecv : public cxMonitorMessage
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
class cxMSGSocketSendTo : public cxMonitorMessage
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
class cxMSGSocketRecvFrom : public cxMonitorMessage
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
class cxMSGSocketPostRecvFrom : public cxMonitorMessage
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
class cxMSGSocketListen : public cxMonitorMessage
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
class cxMSGSocketPostListen : public cxMonitorMessage
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
class cxMSGSocketAccept : public cxMonitorMessage
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
class cxMSGSocketPostAccept : public cxMonitorMessage
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
class cxMSGWFPTcpConnect : public cxMonitorMessage
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
class cxMSGWFPUdpConnect : public cxMonitorMessage
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
//******************************************************************************
#endif

