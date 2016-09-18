#include "stdAfx.h"
#include "LightCom.h"
#include "TypShell.h"

// #ifdef _DEBUG
// #pragma comment(lib, "TypShellD.lib")
// #else
// #pragma comment(lib, "TypShell.lib")
// #endif

HRESULT __stdcall LC_SelfReg(LC_MODULE_INFO &info)
{

	HRESULT hr = S_OK;
	HKEY hKeySub = 0;
	CString strKey, str;

	GuidToStr(info.ClassId, str);

	strKey.Format("%s\\%s\\%s", SZ_KEY_LIGHTCOM, SZ_KEY_CLASS, str);
	
	if (RegCreateKey(HKEY_CLASSES_ROOT, strKey, &hKeySub) == ERROR_SUCCESS)
	{
		
		GuidToStr(info.ClassId, str);
		RegSetValueEx(hKeySub, SZ_VALUE_CLSID, 0, REG_SZ, (unsigned char *)(LPCSTR)str, str.GetLength());
		
		str = info.szPath;
		RegSetValueEx(hKeySub, SZ_VALUE_PATH, 0, REG_SZ, (unsigned char *)(LPCSTR)str, str.GetLength());
		
		RegSetValueEx(hKeySub, SZ_VALUE_VER, 0, REG_DWORD, (unsigned char *)&info.dwVersion, sizeof(DWORD));
		
		str = info.szName;
		RegSetValueEx(hKeySub, SZ_VALUE_NAME, 0, REG_SZ, (unsigned char *)(LPCSTR)str, str.GetLength());
		
		str = info.szDescript;
		RegSetValueEx(hKeySub, SZ_VALUE_DESCRIPT, 0, REG_SZ, (unsigned char *)(LPCSTR)str, str.GetLength());
		
		str = info.szFile;
		RegSetValueEx(hKeySub, SZ_VALUE_FILE, 0, REG_SZ, (unsigned char *)(LPCSTR)str, str.GetLength());
		
		str = info.szAuthor;
		RegSetValueEx(hKeySub, SZ_VALUE_AUTHOR, 0, REG_SZ, (unsigned char *)(LPCSTR)str, str.GetLength());
		
		RegCloseKey(hKeySub);
	}
	else
		hr = E_FAIL;

	return hr;
}

HRESULT __stdcall LC_FindClass(REFCLSID rclsid, PLC_MODULE_INFO pInfo, DWORD *pdwSize)
{
	if (!pdwSize)
		return E_INVALIDARG;

	if (!pInfo)
	{
		*pdwSize = sizeof(LC_MODULE_INFO);
		return S_OK;
	}
	else
	{
		if (*pdwSize < sizeof(LC_MODULE_INFO))
			return E_INVALIDARG;
	}

	HKEY hKeySub = 0;
	CString strKey, str;
	char sz[INFO_TEXT_LEN];
	BOOL bReadReg = FALSE;
	LONG lr = 0;
	DWORD dwByteCount = INFO_TEXT_LEN, dwType = REG_SZ;
	
	pInfo->dwSize = sizeof(LC_MODULE_INFO);

	ZeroMemory(sz, 200);
	GuidToStr((GUID)rclsid, str);
	strKey.Format("%s\\%s\\%s", SZ_KEY_LIGHTCOM, SZ_KEY_CLASS, str);

	if (RegOpenKey(HKEY_CLASSES_ROOT, strKey, &hKeySub) == ERROR_SUCCESS)
	{
		if ((lr = RegQueryValueEx(hKeySub, SZ_VALUE_CLSID, 0, &dwType, (unsigned char *)sz, &dwByteCount)) == ERROR_SUCCESS)
		{
			if (strncmp(str, sz, str.GetLength()) == 0)
			{
				pInfo->ClassId = rclsid;

				dwByteCount = INFO_TEXT_LEN;
				ZeroMemory(pInfo->szPath, INFO_TEXT_LEN);
				if ((lr = RegQueryValueEx(hKeySub, SZ_VALUE_PATH, 0, &dwType, (unsigned char *)pInfo->szPath, &dwByteCount)) == ERROR_SUCCESS)
				{	
					dwByteCount = INFO_TEXT_LEN;
					ZeroMemory(pInfo->szAuthor, INFO_TEXT_LEN);
					if ((lr = RegQueryValueEx(hKeySub, SZ_VALUE_AUTHOR, 0, &dwType, (unsigned char *)pInfo->szAuthor, &dwByteCount)) == ERROR_SUCCESS)
					{
						dwByteCount = INFO_TEXT_LEN;
						ZeroMemory(pInfo->szDescript, INFO_TEXT_LEN);
						if ((lr = RegQueryValueEx(hKeySub, SZ_VALUE_DESCRIPT, 0, &dwType, (unsigned char *)pInfo->szDescript, &dwByteCount))== ERROR_SUCCESS)
						{
							dwByteCount = INFO_TEXT_LEN;
							ZeroMemory(pInfo->szFile, INFO_TEXT_LEN);
							if ((lr = RegQueryValueEx(hKeySub, SZ_VALUE_FILE, 0, &dwType, (unsigned char *)pInfo->szFile, &dwByteCount)) == ERROR_SUCCESS)
							{
								dwByteCount = INFO_TEXT_LEN;
								ZeroMemory(pInfo->szName, INFO_TEXT_LEN);
								if ((lr = RegQueryValueEx(hKeySub, SZ_VALUE_NAME, 0, &dwType, (unsigned char *)pInfo->szName, &dwByteCount)) == ERROR_SUCCESS)
								{
									dwType = REG_DWORD;
									dwByteCount = 4;
									if ((lr = RegQueryValueEx(hKeySub, SZ_VALUE_VER, 0, &dwType, (unsigned char *)&pInfo->dwVersion, &dwByteCount)) == ERROR_SUCCESS)
									{	
										return S_OK;	
									}
								}	
							}	
						}	
					}
				}
			}
		}
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, lr, 0, sz, 200, NULL);
		AfxMessageBox(sz);
		RegCloseKey(hKeySub);
	}
	
	return E_FAIL;
}

void __stdcall LC_UnReg(REFCLSID rclsid)
{

	HKEY hKeySub = 0;
	CString strKey, str;

	BOOL bReadReg = FALSE;
	LONG lr = 0;
	DWORD dwByteCount = INFO_TEXT_LEN, dwType = REG_SZ;

	GuidToStr((GUID)rclsid, str);
	strKey.Format("%s\\%s", SZ_KEY_LIGHTCOM, SZ_KEY_CLASS);

	if (RegOpenKey(HKEY_CLASSES_ROOT, strKey, &hKeySub) == ERROR_SUCCESS)
	{
		RegDeleteKey(hKeySub, str);
		
		RegCloseKey(hKeySub);
	}
	
}

CObjList g_Module;
HINSTANCE g_hLastInstance;
HRESULT __stdcall lcCreateInstanceEx(LPCSTR lpszDll, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown)
{
	return g_Module.CreateObjEx(lpszDll, rclsid, riid, ppv, pUnknown);
}

HRESULT __stdcall lcCreateInstance(REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown)
{
	return g_Module.CreateObj(rclsid, riid, ppv, pUnknown);
}

HRESULT __stdcall lcCreateInstanceInternal(HINSTANCE hInstance, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown)
{
	return g_Module.CreateObjInternal(hInstance, rclsid, riid, ppv, pUnknown);
}

HINSTANCE __stdcall lcGetLastInstance()
{
	return g_hLastInstance;
}

void __stdcall lcFreeInstanceLibrary(HINSTANCE hInstance)
{
	g_Module.ObjFreeLibrary(hInstance);
}
//////////////////////////////////////////////////////////////////////////

CObjList::CObjList()
{
	m_aObjList.RemoveAll();
}

CObjList::~CObjList()
{
	ClearAll();
}

void CObjList::ClearAll()
{
	while (m_aObjList.GetSize() > 0) 
	{
		LIGHTCOMMODULE Module = m_aObjList.GetAt(0);
		m_aObjList.RemoveAt(0);

		if (Module.hModule)
			::FreeLibrary(Module.hModule);
	}

	g_hLastInstance = 0;
}

HMODULE CObjList::AutoLoadModule(LPCSTR lpsz, BOOL *pbLoadNewModule)
{
	if (*pbLoadNewModule)
		*pbLoadNewModule = FALSE;

	LIGHTCOMMODULE Module;

	for (int i = 0; i < m_aObjList.GetSize(); i++)
	{
		Module = m_aObjList.GetAt(i);

		if (!strncmp(lpsz, Module.szPath, MAX_PATH))
			return Module.hModule;
	}

	TRACE("AutoLoadModule: %s\n", lpsz);
	HMODULE hModule = ::LoadLibrary(lpsz);	

	if (hModule)
	{
		//if (*pbLoadNewModule)
		if (pbLoadNewModule)
			*pbLoadNewModule = TRUE;

		//LIGHTCOMMODULE Module;
		Module.hModule = hModule;
		memset(Module.szPath, 0, MAX_PATH);
		strncpy(Module.szPath, lpsz, MAX_PATH);
		m_aObjList.Add(Module);
	}

	return hModule;
}

BOOL CObjList::RemoveModule(HMODULE hModule)
{
	BOOL bResult = FALSE;
	LIGHTCOMMODULE Module;

	if (hModule)
	{
		for (int i = 0; i < m_aObjList.GetSize(); i++)
		{
			Module = m_aObjList.GetAt(i);
			
			if (Module.hModule == hModule)
			{
				m_aObjList.RemoveAt(i);
				::FreeLibrary(hModule);
				bResult = TRUE;
				
				if (hModule == g_hLastInstance)
					g_hLastInstance = 0;
				
				break;
			}
		}
	}

	return bResult;
}

HRESULT CObjList::CreateObjEx(LPCSTR lpszDllFile, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown)
{
	HRESULT hr = E_NOTIMPL;

	BOOL bCreateNewModule = FALSE;
	g_hLastInstance = AutoLoadModule(lpszDllFile, &bCreateNewModule);

	if (g_hLastInstance)
	{
		TRACE("path = %s, instance = %d, breate = %d\n", lpszDllFile, g_hLastInstance, bCreateNewModule);

		if (FAILED(hr = CreateObjInternal(g_hLastInstance, rclsid, riid, ppv, pUnknown)))
		{
			if (bCreateNewModule)
				RemoveModule(g_hLastInstance);

			//g_hLastInstance = 0;
		}
	}

	return hr;
}

HRESULT CObjList::CreateObjInternal(HINSTANCE hInstance, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown)
{
	LIGHTCOMCREATEPROC CoCreate = (LIGHTCOMCREATEPROC)::GetProcAddress(hInstance, LIGHTCOMCREATE_PROCNAME);

	if (!CoCreate)
	{
		return E_FAIL;
	}

	return CoCreate(rclsid, riid, ppv, pUnknown);
}

BOOL CObjList::FindPath(REFCLSID rclsid, CString &str)
{
	LC_MODULE_INFO info;
	DWORD dwSize = sizeof(info);
	
	if (!FAILED(LC_FindClass(rclsid, &info, &dwSize)))
	{
		CString strFolder = GetFolderName(info.szPath);
		CString strPureName = GetPureName(info.szFile);
		CString strExt = GetFileExt(info.szFile);
		CString strPath;
#ifdef _DEBUG
		strPath.Format("%s%sD%s", strFolder, strPureName, strExt);
#else
		strPath.Format("%s", info.szPath);
#endif
		str = strPath;
		return TRUE;
	}
	
	return FALSE;
}

HRESULT CObjList::CreateObj(REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown)
{
	CString strPath;
	if (!FindPath(rclsid, strPath))
		return E_FAIL;
	else
		return CreateObjEx(strPath, rclsid, riid, ppv, pUnknown); 
}

HRESULT CObjList::RegComponent(LPCSTR lpsz)
{
	TRACE("RegComponent: %s\n", lpsz);
	HMODULE hObj = ::LoadLibrary(lpsz);
	
	if (!hObj)
	{
		return E_FAIL;
	}

	LIGHTCOMREGPROC CoReg = (LIGHTCOMREGPROC)::GetProcAddress(hObj, LIGHTCOMREG_PROCNAME);

	if (!CoReg)
	{
		::FreeLibrary(hObj);
		return E_FAIL;
	}

	HRESULT hr = CoReg();
	::FreeLibrary(hObj);
	return hr;
}

HRESULT CObjList::UnRegComponent(REFCLSID rclsid)
{
	CString strPath;
	if (!FindPath(rclsid, strPath))
	{
		return E_FAIL;
	}
	else
	{
		TRACE("UnRegComponent: %s\n", strPath);
		HMODULE hObj = ::LoadLibrary(strPath);
		
		if (!hObj)
		{
			return E_FAIL;
		}
		
		LIGHTCOMUNREGPROC CoUnReg = (LIGHTCOMUNREGPROC)::GetProcAddress(hObj, LIGHTCOMUNREG_PROCNAME);
		
		if (!CoUnReg)
		{
			::FreeLibrary(hObj);
			return E_FAIL;
		}

		HRESULT hr = CoUnReg();
		::FreeLibrary(hObj);
		return hr;
	}

	return E_FAIL;
}

void CObjList::ObjFreeLibrary(HINSTANCE hInstance)
{
	RemoveModule(hInstance);

	//if (hInstance == g_hLastInstance)
	//	g_hLastInstance = 0;
}

HRESULT __stdcall RegComponent(LPCSTR lpsz)
{
	return g_Module.RegComponent(lpsz);
}

HRESULT __stdcall UnRegComponent(REFCLSID rclsid)
{
	return g_Module.UnRegComponent(rclsid);
}