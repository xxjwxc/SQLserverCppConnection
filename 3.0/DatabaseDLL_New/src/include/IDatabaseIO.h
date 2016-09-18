#ifndef __IDATABASE_IO_H_
#define __IDATABASE_IO_H_
#include <Unknwn.h>
#include <map>
#include <string>
#define SAFE_RELEASE(p)	{ if ( p ) { p->Release(); p = NULL; } }

using namespace std;

// 数据库类型
typedef enum enumDATABASE_TYPE : UINT
{
	SQLSERVER = 0,	// SQL Server 数据库
	ORACLE = 1,	// Oracle 数据库
	ACCESS = 2,	// ACCESS 数据库
	MYSQL = 3,	// MySQL  数据库
	EXCEL = 4,    // Excel  数据库
	//	FOXPRO		= 5,    // FoxPro 数据库
}DATABASE_TYPE;

DECLARE_INTERFACE_(IDataBaseModule, IUnknown)
// MIDL_INTERFACE("91DFCEFA-6B46-468f-BCE4-E85322ECA0CF")
// IDataBaseModule :public IUnknown
{
public:
	virtual ~IDataBaseModule(){};
	STDMETHOD_(long, OnInit)(std::wstring ServerName, std::wstring DatabaseName, DATABASE_TYPE enumData_type = DATABASE_TYPE::SQLSERVER, std::wstring UserName = L"", std::wstring UserPassword = L"", std::wstring strConnectionStringOut = L"", void /*IDataBase*/ * pIDataBase = NULL) PURE;
	STDMETHOD_(long, MyExecute)(TCHAR * SQL) PURE;
	STDMETHOD_(long, MyExecute)(CString & SQL) PURE;

	STDMETHOD_(long, MyQuarty)(TCHAR * SQL, _RecordsetPtr & m_RecordSetPtr) PURE;
	STDMETHOD_(long, MyQuarty)(CString &, _RecordsetPtr & m_RecordSetPtr) PURE;

	STDMETHOD_(long, GetCount)(TCHAR * SQL) PURE;
	STDMETHOD_(long, GetCount)(CString & SQL) PURE;
	STDMETHOD_(long, GetCount)(_RecordsetPtr & record) PURE;

	STDMETHOD_(long, GetTableCount)(TCHAR * TableName) PURE;
	STDMETHOD_(long, GetTableCount)(CString & TableName) PURE;

	STDMETHOD_(long, GetExist)(TCHAR * SQL) PURE;
	STDMETHOD_(long, GetExist)(CString & SQL) PURE;
	STDMETHOD_(long, GetExist)(_RecordsetPtr & record) PURE;

	STDMETHOD_(long, GetTableData)(TCHAR * TableName, _RecordsetPtr & record) PURE;
	STDMETHOD_(long, GetTableData)(CString & TableName, _RecordsetPtr & record) PURE;

	STDMETHOD_(long, GetColumnCount)(TCHAR * TableName) PURE;
	STDMETHOD_(long, GetColumnCount)(_RecordsetPtr & record) PURE;
	STDMETHOD_(long, GetColumnCount)(CString & Tablename) PURE;

	STDMETHOD_(long, GetColumnName)(TCHAR * TableName, int & ColumnNum, TCHAR * ColumnName) PURE;
	STDMETHOD_(long, GetColumnName)(CString & Tablename, int & ColumnNum, CString &  ColumnName) PURE;
	STDMETHOD_(long, GetColumnName)(_RecordsetPtr & m_record, int & ColumnNum, TCHAR * ColumnName) PURE;
	STDMETHOD_(long, GetColumnName)(_RecordsetPtr & m_record, int & ColumnNum, CString & ColumnName) PURE;

	STDMETHOD_(long, GetColumnNameList)(TCHAR * TableName, map<int, string> & ColumnName) PURE;
	STDMETHOD_(long, GetColumnNameList)(CString & Tablename, map<int, CString> ColumnName) PURE;
	STDMETHOD_(long, GetColumnNameList)(_RecordsetPtr & m_record, map<int, string> & ColumnName) PURE;
	STDMETHOD_(long, GetColumnNameList)(_RecordsetPtr & m_record, map<int, CString> ColumnName) PURE;

	STDMETHOD_(void, CloseConnect)()PURE;
	STDMETHOD_(void, SetConnectionState)(BOOL bState) PURE;
	STDMETHOD_(BOOL, GetConnectionState)() PURE;
	STDMETHOD_(_RecordsetPtr &, GetRecordSet)() PURE;
	STDMETHOD_(_ConnectionPtr &, GetConnectionPtr)() PURE;

	STDMETHOD_(long, SetServerInfo)(TCHAR * ServerName, TCHAR * DatabaseName) PURE;
	STDMETHOD_(long, SetServerInfo)(CString &  ServerName, CString &  DatabaseName) PURE;
	STDMETHOD_(long, SetServerInfo)(TCHAR * ServerName, TCHAR * DatabaseName, TCHAR * UserName, TCHAR * UserPassword) PURE;
	STDMETHOD_(long, SetServerInfo)(CString &  ServerName, CString &  DatabaseName, CString &  UserName, CString &  UserPassword) PURE;

	STDMETHOD_(long, CreateConnect)() PURE;

	STDMETHOD_(std::wstring, GetServerName)() const PURE;
	STDMETHOD_(std::wstring, GetServerUsr)() const PURE;
	STDMETHOD_(std::wstring, GetServerPsd)() const PURE;
	STDMETHOD_(std::wstring, GetDatabaseName)() const PURE;
	STDMETHOD_(std::wstring, GetConnectionStr)() const PURE;

};

// 创建接口需要的IID
// {91DFCEFA-6B46-468f-BCE4-E85322ECA0CF}
DEFINE_GUID(IID_DATABASEMODULE, 
			0x91dfcefa, 0x6b46, 0x468f, 0xbc, 0xe4, 0xe8, 0x53, 0x22, 0xec, 0xa0, 0xcf);


// 创建接口需要的GUID
// {CCBD9AF6-AB5D-4d70-B2BD-CC868CC21E57}
DEFINE_GUID(CLSID_DATABASEMODULE, 
			0xccbd9af6, 0xab5d, 0x4d70, 0xb2, 0xbd, 0xcc, 0x86, 0x8c, 0xc2, 0x1e, 0x57);

//用于创建数据库入口函数
//注意：此函数是使用注册表里面来创建，故如要成功，需要先注册dll
//请不要忘记用完后使用下面Release函数释放com接口
inline bool CreatIDataBaseSql(IDataBaseModule * & lpiDataBaseSql)
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_DATABASEMODULE,  // 组件对象类的CLSID
		NULL,                // 非聚合
		CLSCTX_INPROC_SERVER,  // 只使用进程内服务器
		IID_DATABASEMODULE, // 所请求接口的IID
		(void**)&lpiDataBaseSql);   // 容纳接口指针的缓冲

	if (FAILED(hr))
		return false;
}

//用于创建数据库入口函数
//注意：此函数通过dll路径来创建函数
//请不要忘记用完后使用下面Release函数释放com接口
static int __reff = 0;
static HINSTANCE __hdllInst = NULL;
inline bool CreatIDataBaseSql(LPCSTR lpszDll, IDataBaseModule * & lpiDataBaseSql)
{
	bool bResult = false;
	HRESULT hr;
	typedef HRESULT(__stdcall * pfnGCO) (REFCLSID, REFIID, void**);
	pfnGCO fnGCO = NULL;
	if (!__hdllInst)
	 __hdllInst = LoadLibrary(lpszDll); //加载dll  
	fnGCO = (pfnGCO)GetProcAddress(__hdllInst, "DllGetClassObject"); //从dll中得到DllGetClassObject
	if (fnGCO != NULL)
	{
		IClassFactory* pcf = NULL;
		HRESULT hr = (fnGCO)(CLSID_DATABASEMODULE, IID_IClassFactory, (void**)&pcf); //创建工厂  
		if (SUCCEEDED(hr) && (pcf != NULL))
		{
			lpiDataBaseSql = NULL;
			hr = pcf->CreateInstance(NULL, IID_DATABASEMODULE, (void**)&lpiDataBaseSql); //通过工厂创建dll接口  
			//调用IiTrusPTA具体的业务操作  
			if (SUCCEEDED(hr) && (lpiDataBaseSql != NULL))
			{
				__reff++;
				bResult = true;
				pcf->Release();
			}
		}
	}

	//FreeLibrary(__hdllInst);//释放dll资源
	return bResult;
}

inline bool ReleaseIDataBaseSql(IDataBaseModule * & lpiDataBaseSql)
{
	SAFE_RELEASE(lpiDataBaseSql);
	__reff--;

	if (__reff == 0)
	{
		FreeLibrary(__hdllInst);//释放dll资源
		__hdllInst = NULL;
	}
	return true;
}

#endif