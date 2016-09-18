// stdafx.cpp : source file that includes just the standard includes
//	TypGuid.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <AFXDISP.H>
#include <INITGUID.H>

// 创建接口需要的IID
// {91DFCEFA-6B46-468f-BCE4-E85322ECA0CF}
DEFINE_GUID(IID_DATABASEMODULE, 
			0x91dfcefa, 0x6b46, 0x468f, 0xbc, 0xe4, 0xe8, 0x53, 0x22, 0xec, 0xa0, 0xcf);


// 创建接口需要的GUID
// {CCBD9AF6-AB5D-4d70-B2BD-CC868CC21E57}
DEFINE_GUID(CLSID_DATABASEMODULE, 
			0xccbd9af6, 0xab5d, 0x4d70, 0xb2, 0xbd, 0xcc, 0x86, 0x8c, 0xc2, 0x1e, 0x57);