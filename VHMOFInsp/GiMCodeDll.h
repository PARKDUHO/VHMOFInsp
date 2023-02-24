#pragma once

extern "C" __declspec(dllexport) void ShowDefectCodeSet(CWnd* hParent);
extern "C" __declspec(dllexport) void ShowDefectCodeSetFTP(CWnd* hParent);
extern "C" __declspec(dllexport) void FtpFileDownload();
extern "C" __declspec(dllexport) void ReadCombiFile();
extern "C" __declspec(dllexport) void ShowCoordinateChase(CWnd* hParent);
extern "C" __declspec(dllexport) void SetCoordinateChase(int nVtgHandle, LPCSTR lpPID, LPCSTR lpPtnName, int nHorizontal, int nVertical);
extern "C" __declspec(dllexport) int ShowBarCodeInput(CWnd* hParent);
extern "C" __declspec(dllexport) int ShowDefectResult(CWnd* hParent);
extern __declspec(dllexport) CString GetRWK_CD();
extern __declspec(dllexport) CString GetRWK_Name();
extern __declspec(dllexport) BOOL	 GetScraFlag();
extern __declspec(dllexport) CString ConvertFullReasion(CString reasion);
extern __declspec(dllexport) CString GetExpected_RWK();
extern __declspec(dllexport) int     GetCombinationCodeIndex();
extern __declspec(dllexport) CString FtpDownDefectCode();
extern __declspec(dllexport) CString FtpDownDefectCodeFull();
extern __declspec(dllexport) CString FtpDownRepairCode();
extern __declspec(dllexport) CString FtpDownRepairCodeFull();
extern __declspec(dllexport) CString FtpDownCombiCode();
extern __declspec(dllexport) CString FtpDownCombiCodeAssy();
extern __declspec(dllexport) CString FtpDownCombiCodeTab();
extern __declspec(dllexport) CString GetFtpEventLog();
extern __declspec(dllexport) bool GetShowDlgStatus();

extern "C" __declspec(dllexport) void SetDefectInputType(int nType);