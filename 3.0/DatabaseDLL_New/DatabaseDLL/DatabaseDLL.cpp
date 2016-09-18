// DatabaseDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "DatabaseDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//dll export
#include "../src/include/MyRegistry.h"
#include "../src/include/MyObjectFactory.h"
#include "../src/include/IDatabaseIO.h"

HMODULE g_hModule = NULL;
//ULONG    g_LockNumber;
// EXTERN_C const CLSID IID_DATABASEMODULE;
// EXTERN_C const CLSID CLSID_DATABASEMODULE;


STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void **ppv)
{
	TRACE(L"DllGetClassObject...");
	if (clsid == CLSID_DATABASEMODULE) {

		CObjectFactory *pFactory = new CObjectFactory;

		if (pFactory == NULL) {
			return E_OUTOFMEMORY;
		}

		HRESULT result = pFactory->QueryInterface(iid, ppv);

		return result;
	}
	else
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

STDAPI DllCanUnloadNow(void)
{
	if (g_LockNumber == 0)
		return S_OK;
	else
		return S_FALSE;
}

STDAPI DllRegisterServer()
{
	TCHAR szFileName[MAX_PATH];
	::GetModuleFileName((HMODULE)g_hModule, szFileName, sizeof(szFileName));
	TRACE(szFileName);
	return RegisterServer(CLSID_DATABASEMODULE, szFileName, "dataBaseCom.Object", "dataBase Componet", NULL);
}


STDAPI DllUnregisterServer()
{
	//return AMovieDllRegisterServer2(FALSE);
	return UnregisterServer(CLSID_DATABASEMODULE, "dataBaseCom.Object", NULL);

}

BOOL MyDllMain(HMODULE hModule)
{
	if (!g_hModule)
		g_hModule = hModule;

	return TRUE;
}
//------------------------------------end



// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  更改错误代码以符合您的需要
			_tprintf(_T("错误:  MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  在此处为应用程序的行为编写代码。
			MyDllMain(hModule);
		}
	}
	else
	{
		// TODO:  更改错误代码以符合您的需要
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
