/********************************************************************
	创建时间：	2014/10/08  11:55:38 
	文件名：    	MyRegistry.h
	作者：		谢小军
	
	功能：		1.主要实现DllRegisterServer，用于注册表注册使用
				2.
				
	说明：	    1. 
				2. 
*********************************************************************/
#ifndef __MYREGISTRY_H_
#define __MYREGISTRY_H_

HRESULT RegisterServer(const CLSID& clsid,         // Class ID
	const TCHAR *szFileName,     // DLL module handle
	const TCHAR* szProgID,       //   IDs
	const TCHAR* szDescription,  // Description String
	const TCHAR* szVerIndProgID); // optional

HRESULT UnregisterServer(const CLSID& clsid,      // Class ID
	const TCHAR* szProgID,       //   IDs
	const TCHAR* szVerIndProgID); // Programmatic
#endif