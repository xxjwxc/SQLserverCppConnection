#include "stdafx.h"
#include "MyRegistry.h"
#include "MyObjectFactory.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

HMODULE g_hModule = NULL;
ULONG    g_LockNumber = 0;
EXTERN_C const CLSID IID_DATABASEMODULE;
EXTERN_C const CLSID CLSID_DATABASEMODULE;


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
	return RegisterServer(CLSID_DATABASEMODULE, szFileName, L"dataBaseCom.Object", L"dataBase Componet", NULL);
}


STDAPI DllUnregisterServer()
{
	//return AMovieDllRegisterServer2(FALSE);
	return UnregisterServer(CLSID_DATABASEMODULE, L"dataBaseCom.Object", NULL);

}

BOOL MyDllMain(HMODULE hModule)
{
	if (!g_hModule)
		g_hModule = hModule;

	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif