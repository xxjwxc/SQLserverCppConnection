#include "StdAfx.h"

#include <objbase.h>
#include <assert.h>
#include "MyRegistry.h"

////////////////////////////////////////////////////////
//
// Internal helper functions prototypes
//
//   - These helper functions were borrowed and modifed from
//     Dale Rogerson's book Inside COM.

// Set the given key and its value.
BOOL SetKeyAndValue(const TCHAR* pszPath,
	const TCHAR* szSubkey,
	const TCHAR* szValue);

// Convert a CLSID into a char string.
void CLSIDtoString(const CLSID& clsid,
	TCHAR* szCLSID,
	int length);

// Delete szKeyChild and all of its descendents.
LONG DeleteKey(HKEY hKeyParent, const TCHAR* szKeyString);

////////////////////////////////////////////////////////
//
// Constants
//

// Size of a CLSID as a string
const int CLSID_STRING_SIZE = 39;

/////////////////////////////////////////////////////////
//
// Public function implementation
//

//
// Register the component in the registry.
//
HRESULT RegisterServer(const CLSID& clsid,         // Class ID
	const TCHAR *szFileName,     // DLL module handle
	const TCHAR* szProgID,       //   IDs
	const TCHAR* szDescription,  // Description String
	const TCHAR* szVerIndProgID) // optional

{
	TRACE(szFileName);
	TRACE(szProgID);
	// Convert the CLSID into a char.
	TCHAR szCLSID[CLSID_STRING_SIZE];
	CLSIDtoString(clsid, szCLSID, sizeof(szCLSID));
	//StringFromCLSID(clsid,szCLSID);
	// Build the key CLSID//{...}
	TCHAR szKey[64];
	lstrcpy(szKey, "CLSID//");
	lstrcat(szKey, szCLSID);
	TRACE(szKey);
	// Add the CLSID to the registry.
	SetKeyAndValue(szKey, NULL, szDescription);

	// Add the server filename subkey under the CLSID key.
	SetKeyAndValue(szKey, "InprocServer32", szFileName);

	// Add the ProgID subkey under the CLSID key.
	if (szProgID != NULL) {
		SetKeyAndValue(szKey, "ProgID", szProgID);
		SetKeyAndValue(szProgID, "CLSID", szCLSID);
	}

	if (szVerIndProgID) {
		// Add the version-independent ProgID subkey under CLSID key.
		SetKeyAndValue(szKey, "VersionIndependentProgID",
			szVerIndProgID);

		// Add the version-independent ProgID subkey under HKEY_CLASSES_ROOT.
		SetKeyAndValue(szVerIndProgID, NULL, szDescription);
		SetKeyAndValue(szVerIndProgID, "CLSID", szCLSID);
		SetKeyAndValue(szVerIndProgID, "CurVer", szProgID);

		// Add the versioned ProgID subkey under HKEY_CLASSES_ROOT.
		SetKeyAndValue(szProgID, NULL, szDescription);
		SetKeyAndValue(szProgID, "CLSID", szCLSID);
	}

	return S_OK;
}

//
// Remove the component from the registry.
//
HRESULT UnregisterServer(const CLSID& clsid,      // Class ID
	const TCHAR* szProgID,       //   IDs
	const TCHAR* szVerIndProgID) // Programmatic
{
	// Convert the CLSID into a char.
	TCHAR szCLSID[CLSID_STRING_SIZE];
	CLSIDtoString(clsid, szCLSID, sizeof(szCLSID));
	//StringFromCLSID(clsid,szCLSID);
	// Build the key CLSID//{...}
	TCHAR szKey[64];
	lstrcpy(szKey, "CLSID//");
	lstrcat(szKey, szCLSID);

	// Delete the CLSID Key - CLSID/{...}
	LONG lResult = DeleteKey(HKEY_CLASSES_ROOT, szKey);

	// Delete the version-independent ProgID Key.
	if (szVerIndProgID != NULL)
		lResult = DeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID);

	// Delete the ProgID key.
	if (szProgID != NULL)
		lResult = DeleteKey(HKEY_CLASSES_ROOT, szProgID);

	return S_OK;
}

///////////////////////////////////////////////////////////
//
// Internal helper functions
//

// Convert a CLSID to a char string.
void CLSIDtoString(const CLSID& clsid,
	TCHAR* szCLSID,
	int length)
{
	assert(length >= CLSID_STRING_SIZE);
	// Get CLSID
	LPOLESTR wszCLSID = NULL;
	HRESULT hr = StringFromCLSID(clsid, &wszCLSID);
	assert(SUCCEEDED(hr));
// 	lstrcpy(szCLSID, wszCLSID);
// 	TRACE(szCLSID);

	// Free memory.
	CoTaskMemFree(wszCLSID);
}

//
// Delete a key and all of its descendents.
//
LONG DeleteKey(HKEY hKeyParent,           // Parent of key to delete
	const TCHAR* lpszKeyChild)  // Key to delete
{
	// Open the child.
	HKEY hKeyChild;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0,
		KEY_ALL_ACCESS, &hKeyChild);
	if (lRes != ERROR_SUCCESS)
	{
		return lRes;
	}

	// Enumerate all of the decendents of this child.
	FILETIME time;
	TCHAR szBuffer[256];
	DWORD dwSize = 256;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL,
		NULL, NULL, &time) == S_OK)
	{
		// Delete the decendents of this child.
		lRes = DeleteKey(hKeyChild, szBuffer);
		if (lRes != ERROR_SUCCESS)
		{
			// Cleanup before exiting.
			RegCloseKey(hKeyChild);
			return lRes;
		}
		dwSize = 256;
	}

	// Close the child.
	RegCloseKey(hKeyChild);

	// Delete this child.
	return RegDeleteKey(hKeyParent, lpszKeyChild);
}

// Create a key and set its value.
//
BOOL SetKeyAndValue(const TCHAR* szKey,
	const TCHAR* szSubkey,
	const TCHAR* szValue)
{
	HKEY hKey;
	TCHAR szKeyBuf[1024];

	// Copy keyname into buffer.
	lstrcpy(szKeyBuf, szKey);

	// Add subkey name to buffer.
	if (szSubkey != NULL)
	{
		lstrcat(szKeyBuf, "//");
		lstrcat(szKeyBuf, szSubkey);
	}

	// Create and open key and subkey.
	long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT,
		szKeyBuf,
		0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL,
		&hKey, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		TRACE(L"SetKeyAndValue Failed!");
		return FALSE;
	}

	// Set the Value.
	if (szValue != NULL)
	{
		RegSetValueEx(hKey, NULL, 0, REG_SZ,
			(BYTE *)szValue,
			2 * lstrlen(szValue) + 1);
	}

	RegCloseKey(hKey);
	TRACE(L"SetKeyAndValue Succeed!");
	return TRUE;
}
