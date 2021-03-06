#include "stdafx.h"

#define REG_BACKGROUND L"Software\\Classes\\directory\\Background\\shell\\xCopy as path\\command"
#define REG_DIR L"Software\\Classes\\directory\\shell\\xCopy as path\\command"
#define REG_FILE L"Software\\Classes\\*\\shell\\xCopy as path\\command"


BOOL addRegister(const TCHAR* key, const TCHAR* pathExe) {
	HKEY hKey{};
	if (RegCreateKey(HKEY_CURRENT_USER, key, &hKey)) {
		RegCloseKey(hKey);
		return FALSE;
	}
	LSTATUS st;
	st = RegSetValueEx(hKey, NULL, 0, REG_EXPAND_SZ, LPBYTE(pathExe), MAX_PATH + 2);
	if (st) {
		RegCloseKey(hKey);
		return FALSE;
	}

	RegCloseKey(hKey);
	return TRUE;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	TCHAR cDir[MAX_PATH + 2]{};
	GetCurrentDirectory(MAX_PATH + 2, cDir);
	_tcsncat_s(cDir, L"\\x64\\CopyPath.exe", _tcslen(L"\\x64\\CopyPath.exe"));
	TCHAR cDirPath[MAX_PATH + 2]{};
	_stprintf_s(cDirPath, MAX_PATH + 2, L"\"%s\"", cDir);

	// Dir background
	_tcsncat_s(cDirPath, L" \"%V\"", _tcslen(L" \"%V\""));

	if (!addRegister(REG_BACKGROUND, cDirPath))
		return 1;

	if (!addRegister(REG_DIR, cDirPath))
		return 1;
	
	// File
	if (!addRegister(REG_FILE, cDirPath))
		return 1;

	MessageBox(NULL, L"Done.", L"It's okay...", MB_ICONINFORMATION);

	return 0;
}

