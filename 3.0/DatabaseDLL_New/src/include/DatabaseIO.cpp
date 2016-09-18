/*
*Copyright(c) 2012，Alac Stratos
*All rights reserved.
*
*文件名称：	DatabaseIO.h
*包 含 类：	CSQLServerIO，CSQLServerIO
*摘    要：		使用ADO对数据库进行输入输出。CSQLServerIO为抽象类。
*			CSQLServer为CSQLServerIO的子类，并实现了对SQL Server
*			数据库的常用操作。
*
*当前版本：	6.0.1
*作    者：	
*完成日期：	11-4-2012
*
*取代版本：	5.0.3
*作    者：	Alac Stratos
*完成日期：	7-8-2012
*
*备    注：		此代码是开源代码，允许用户基于GNU通用公共许可证或者
*			第二版本的许可证或者其他你选择的任何许可证进行修改，
*			重构以及使用。
*				此代码的公开是为了进步，但是其发布没有任何的担保，暗
*			示保证，适售性，或者任何特定用途。你需要查阅GNU通用公共
*			许可证以获取更多的信息。
*				任何有关本代码的其它信息，请咨询
*				wangbeeking@yahoo.com.cn
*/

#include "StdAfx.h"
#include "DatabaseIO.h"
// 
// // 创建接口需要的IID
// // {91DFCEFA-6B46-468f-BCE4-E85322ECA0CF}
// DEFINE_GUID(IID_DATABASEMODULE,
// 	0x91dfcefa, 0x6b46, 0x468f, 0xbc, 0xe4, 0xe8, 0x53, 0x22, 0xec, 0xa0, 0xcf);
// 
// 
// // 创建接口需要的GUID
// // {CCBD9AF6-AB5D-4d70-B2BD-CC868CC21E57}
// DEFINE_GUID(CLSID_DATABASEMODULE,
// 	0xccbd9af6, 0xab5d, 0x4d70, 0xb2, 0xbd, 0xcc, 0x86, 0x8c, 0xc2, 0x1e, 0x57);

void  CSQLServerIO::CloseConnect()
{
	Lock lock1(m_RecordSetCriticalSection);
	Lock lock2(m_ConnectPtrCriticalSection);

	if (m_ConnectPtr && m_ConnectPtr->State)
		m_ConnectPtr->Close();
	if (m_RecordSet && m_RecordSet->State)
		m_RecordSet->Close();

	SetConnectionState(CONNECTION_OFF);
}


STDMETHODIMP_(long) CSQLServerIO::MyExecute( CString & SQL )
{
	DO_EXCUTE_FUN1(MyExecute);
}

STDMETHODIMP_(long) CSQLServerIO::MyExecute( TCHAR * SQL )
{
	Lock lock(m_ConnectPtrCriticalSection);

	if (!SQL) return SQL_SENTENCE_ERROR;

	try
	{
		m_ConnectPtr->Execute((_bstr_t)SQL,NULL,adCmdText);
		return EXECUTE_SUCCESS;
	}
	catch (_com_error& e)
	{
		#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
 		return EXECUTE_FAIL;
	}
}


STDMETHODIMP_(long) CSQLServerIO::MyQuarty( TCHAR * SQL , _RecordsetPtr & rRecordSetPtr )
{
	Lock lock(m_ConnectPtrCriticalSection);

	if (!SQL) return SQL_SENTENCE_ERROR;

	rRecordSetPtr.CreateInstance("ADODB.Recordset");

	if (!rRecordSetPtr) 
		return RECORDSETPTR_ERROR;
	if (rRecordSetPtr->State)	
		rRecordSetPtr->Close();
	
	try
	{
		rRecordSetPtr->Open((_bstr_t)SQL,(IDispatch*)m_ConnectPtr,adOpenStatic,adLockOptimistic,adCmdText);
		return SEARCH_SUCCESS;
	}
	catch (_com_error& e)
	{
#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
		return SEARCH_FAIL;
	}	
}

STDMETHODIMP_(long) CSQLServerIO::MyQuarty( CString & SQL, _RecordsetPtr & rRecordSetPtr )
{
	DO_EXCUTE_FUN2(MyQuarty , rRecordSetPtr);
}



STDMETHODIMP_(long) CSQLServerIO::GetCount( TCHAR * SQL )
{
	Lock lock(m_RecordSetCriticalSection);

	if (!SQL)
		return SQL_SENTENCE_ERROR;
	long err = MyQuarty(SQL,m_RecordSet);
	if (err == SEARCH_SUCCESS)
		return m_RecordSet->GetRecordCount();
	return err;
}


STDMETHODIMP_(long) CSQLServerIO::GetCount( CString & SQL )
{
	DO_EXCUTE_FUN1(GetCount);
}


STDMETHODIMP_(long) CSQLServerIO::GetCount( _RecordsetPtr & record )
{
	if (!record) 
		return RECORDSETPTR_ERROR;
	else if (!record->State)
		return RECORDSETPTR_ERROR;

	return record->GetRecordCount();
}


STDMETHODIMP_(long) CSQLServerIO::GetTableCount( TCHAR * TableName )
{
	if(!TableName)
		return TABLE_NAME_ERROR;
	TCHAR sql[50];
	wsprintf(sql,_T("SELECT * FROM %s"),TableName);
	return GetCount(sql);
}

STDMETHODIMP_(long) CSQLServerIO::GetTableCount( CString & SQL )
{
	DO_EXCUTE_FUN1(GetTableCount);
}


STDMETHODIMP_(long) CSQLServerIO::GetExist( TCHAR * SQL )
{
	Lock lock(m_RecordSetCriticalSection);

	long err = MyQuarty(SQL,m_RecordSet);

	if(err == SEARCH_SUCCESS)
	{
		if (!m_RecordSet->adoEOF)
			return DATA_EXIST;
		else
			return DATA_NULL;
	}
	return err;
}


STDMETHODIMP_(long) CSQLServerIO::GetExist( CString & SQL )
{
	DO_EXCUTE_FUN1(GetExist);
}


STDMETHODIMP_(long) CSQLServerIO::GetExist( _RecordsetPtr & m_record )
{
	if (!m_record || !m_record->State) 
		return RECORDSETPTR_ERROR;

	if (!m_record->adoEOF)//此处将m_RecordSet修改为m_record
		return DATA_EXIST;

	return DATA_NULL;
}


STDMETHODIMP_(long) CSQLServerIO::GetTableData( TCHAR * TableName , _RecordsetPtr & record )
{
	if (!TableName)
		return TABLE_NAME_ERROR;
	TCHAR sql[50];
	wsprintf(sql,_T("SELECT * FROM %s"),TableName);
	return MyQuarty(sql,record);
}


STDMETHODIMP_(long) CSQLServerIO::GetTableData( CString & SQL , _RecordsetPtr & record )
{
	DO_EXCUTE_FUN2(GetTableData,record);
}


STDMETHODIMP_(long) CSQLServerIO::GetColumnCount( TCHAR * SQL )
{
	Lock lock(m_RecordSetCriticalSection);

	long err = MyQuarty(SQL,m_RecordSet);

	if(err ==SEARCH_SUCCESS)
		return m_RecordSet-> GetFields()-> GetCount(); 
	else
		return err;
}

STDMETHODIMP_(long) CSQLServerIO::GetColumnCount(CString & SQL)
{
	DO_EXCUTE_FUN1(GetColumnCount);
}

STDMETHODIMP_(long) CSQLServerIO::GetColumnCount(_RecordsetPtr & m_record)
{
	if(!m_record || !m_record->State)
		return RECORDSETPTR_ERROR;
	else
		return m_record-> GetFields()-> GetCount(); 
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnName(TCHAR * SQL , int & ColumnNum ,TCHAR * ColumnName)
{
	Lock lock(m_RecordSetCriticalSection);

	if (SQL==NULL||ColumnNum<0)
		return TABLE_NAME_ERROR;
	if (MyQuarty(SQL,m_RecordSet)==SEARCH_SUCCESS)
	{
		long AllColumnNum=GetColumnCount(m_RecordSet);
		if (ColumnNum!=GET_COLUMN_SUM_FAIL && ColumnNum<=AllColumnNum)
		{
			wsprintf(ColumnName,_T("%s"),m_RecordSet->GetFields()->GetItem((long)ColumnNum)->GetName());
			return GET_COLUMN_NAME_SUCESS;
		}
	}
	return GET_COLUMN_NAME_FAIL;
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnName(CString & Tablename ,int & ColumnNum ,CString &  ColumnName)
{
	if (Tablename.IsEmpty()||ColumnNum<0|| ColumnName.IsEmpty())
		return TABLE_NAME_ERROR;
	TCHAR tempName[100];
	long err=GetColumnName(Tablename.GetBuffer(),ColumnNum,tempName);
	Tablename.ReleaseBuffer();

	if (err!=GET_COLUMN_NAME_FAIL)
		ColumnName.Format(_T("%s"),tempName);
	return err;
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnName(_RecordsetPtr & m_record , int & ColumnNum ,TCHAR * ColumnName)
{
	Lock lock(m_RecordSetCriticalSection);

	 if (!m_record || !m_record->State)
		return RECORDSETPTR_ERROR;
	else if (!ColumnName)
		return COLUMN_NAME_ERROR;
	else if (ColumnNum >= m_record->GetFields()-> GetCount())
		return GET_COLUMN_NAME_FAIL;
	else if (!m_RecordSet)
		return RECORDSETPTR_ERROR;
	else
	{
		wsprintf(ColumnName,_T("%s\0"),(LPCTSTR)m_RecordSet->GetFields()->GetItem((long)ColumnNum)->GetName());
		return GET_COLUMN_NAME_SUCESS;
	}
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnName(_RecordsetPtr & m_record , int & ColumnNum ,CString & ColumnName)
{
	TCHAR tempColumnName[100];
	long err=GetColumnName(m_record,ColumnNum,tempColumnName);
	if (err!=GET_COLUMN_NAME_FAIL)
		ColumnName.Format(_T("%s"),tempColumnName);
	return err;
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnNameList( TCHAR * TableName ,map<int,string> & ColumnName )
{
	Lock lock(m_RecordSetCriticalSection);

	if (!TableName)
		return TABLE_NAME_ERROR;
	TCHAR SQL[50];
	wsprintf(SQL,_T("SELECT * FROM %s"),TableName);
	if (MyQuarty(SQL,m_RecordSet)==SEARCH_SUCCESS)
	{
		ColumnName.empty();
		int AllColumnNum=GetColumnCount(m_RecordSet);
		for(int i=0;i<AllColumnNum;i++)
		{
			_bstr_t bsCloumnName=(m_RecordSet->GetFields()->GetItem((long)i)->GetName());
			string sTemp = (char *)(bsCloumnName);
			ColumnName.insert(map<int , string>::value_type(i,sTemp));
		}
		return GET_COLUMN_NAME_SUCESS;
	}
	return GET_COLUMN_NAME_FAIL;
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnNameList(CString & TableName ,map<int,CString> ColumnName)
{
	if (TableName.IsEmpty())
		return TABLE_NAME_ERROR;

	CString SQL=(_T("SELECT * FROM ")+TableName);
	_RecordsetPtr Rec;
	if (MyQuarty(SQL,Rec)==SEARCH_SUCCESS)
		return GetColumnNameList(Rec,ColumnName);
	return GET_COLUMN_NAME_FAIL;
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnNameList( _RecordsetPtr & m_record , map<int,string> & ColumnName )
{
	if(!m_record || !m_record->State)
		return RECORDSETPTR_ERROR;

	ColumnName.empty();
	int AllColumnNum=GetColumnCount(m_record);
	for(int i=0;i<AllColumnNum;i++)
	{
		_bstr_t bsCloumnName=(m_record->GetFields()->GetItem((long)i)->GetName());
		string sTemp = (char *)bsCloumnName;
		ColumnName.insert(map<int , string>::value_type (i,sTemp));
	}
	return GET_COLUMN_NAME_SUCESS;
}

STDMETHODIMP_(long)  CSQLServerIO::GetColumnNameList(_RecordsetPtr & m_record ,map<int,CString> ColumnName)
{
	Lock lock(m_RecordSetCriticalSection);

	if(!m_record || !m_record->State)
		return RECORDSETPTR_ERROR;

	ColumnName.empty();
	int AllColumnNum=GetColumnCount(m_record);
	for(int i=0;i<AllColumnNum;i++)
	{
		_variant_t vTemp = m_RecordSet->GetFields()->GetItem((long)i)->GetName();
		CString cTemp;
		if (vTemp.vt!=VT_NULL) cTemp=vTemp;
		ColumnName.insert(map<int , CString>::value_type (i,cTemp));
	}
	return GET_COLUMN_NAME_SUCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


STDMETHODIMP_(long) CSQLServerIO::OnInit( std::wstring ServerName ,std::wstring DatabaseName ,DATABASE_TYPE enumData_type /*=SQLSERVER */,std::wstring UserName /*= "" */,std::wstring UserPassword /*= ""*/,std::wstring strConnectionStringOut /*= "sqloledb" */,void /*IDataBase*/ * pIDataBase /*= NULL*/ )
//m_pIDataBase(NULL),m_isInternalBuild(FALSE)
{

#define LAMBDA_FUN(_AUTO) \
	if (strConnectionStringOut.empty())\
	{\
		if (UserName.empty() && UserPassword.empty())\
			m_pIDataBase = std::tr1::shared_ptr <IDataBase> (new _AUTO(ServerName,DatabaseName));\
		else\
			m_pIDataBase = std::tr1::shared_ptr <IDataBase> (new _AUTO(ServerName,DatabaseName,UserName,UserPassword));\
	} \
	else \
		m_pIDataBase = std::tr1::shared_ptr <IDataBase> (new _AUTO(ServerName,DatabaseName,UserName,UserPassword,strConnectionStringOut));

///////////////////////////////////////////////////////////////////////////////////////////////////
//m_isInternalBuild = TRUE;
	switch(enumData_type)
	{
	case SQLSERVER	:	// SQL Server 数据库
		{
			LAMBDA_FUN(CSQlServer);
			break;
		}
	case ORACLE	:	// Oracle 数据库
		{
			LAMBDA_FUN(COracle);
			break;
		}
	case ACCESS :	// ACCESS 数据库
		{
			LAMBDA_FUN(CACCESS);
			break;
		}
	case MYSQL :	// MySQL 数据库
		{
			LAMBDA_FUN(CMySQl);
			break;
		}
	case EXCEL:    // Excel 数据库
		{
			LAMBDA_FUN(CEXCEL);
			break;
		}
// 	case FOXPRO: // FoxPro 数据库
// 		{
// 			LAMBDA_FUN(CFoxPro);
// 			break;
// 		}
	default:
		break;
	}

	if (m_pIDataBase)
		m_pIDataBase->SetConnectionString();

	return CreateConnect();
}

STDMETHODIMP_(long)  CSQLServerIO::SetServerInfo(TCHAR * ServerName ,TCHAR * DatabaseName)
{
	if (!ServerName || !DatabaseName)
		return DATABASE_INFO_ERROR;

	if (m_pIDataBase)
		return m_pIDataBase->SetServerInfo((std::wstring)(_bstr_t)ServerName,(std::wstring)(_bstr_t)DatabaseName,m_pIDataBase->m_strUserID,m_pIDataBase->m_strPassword,m_pIDataBase->m_strConnectionStringOut);
	else
		return DATABASE_INFO_ERROR;
	
}

STDMETHODIMP_(long)  CSQLServerIO::SetServerInfo( CString &  ServerName  ,CString &  DatabaseName )
{
	if (ServerName.IsEmpty() || DatabaseName.IsEmpty())
		return DATABASE_INFO_ERROR;

	long err = CSQLServerIO::SetServerInfo(ServerName.GetBuffer(),DatabaseName.GetBuffer());
	ServerName.ReleaseBuffer();
	DatabaseName.ReleaseBuffer();
	return err;
}

STDMETHODIMP_(long)  CSQLServerIO::SetServerInfo(TCHAR * ServerName ,TCHAR * DatabaseName ,TCHAR * UserName ,TCHAR * UserPassword)
{
	if (!ServerName||!DatabaseName||!UserName||!UserPassword)
		return DATABASE_INFO_ERROR;
	if (m_pIDataBase)
		return m_pIDataBase->SetServerInfo((std::wstring)(_bstr_t)ServerName,(std::wstring)(_bstr_t)DatabaseName,(std::wstring)(_bstr_t)UserName,(std::wstring)(_bstr_t)UserPassword,m_pIDataBase->m_strConnectionStringOut);
	else
		return DATABASE_INFO_ERROR;
}

STDMETHODIMP_(long)  CSQLServerIO::SetServerInfo( CString &  ServerName ,CString &  DatabaseName ,CString &  UserName ,CString & UserPassword )
{
	if (ServerName.IsEmpty()||DatabaseName.IsEmpty()||UserName.IsEmpty() || UserPassword.IsEmpty())
		return DATABASE_INFO_ERROR;
	long err = CSQLServerIO::SetServerInfo(ServerName.GetBuffer(),DatabaseName.GetBuffer(),UserName.GetBuffer(),UserPassword.GetBuffer());
	ServerName.ReleaseBuffer();
	DatabaseName.ReleaseBuffer();
	UserName.ReleaseBuffer();
	UserPassword.ReleaseBuffer();
	return err;
}

STDMETHODIMP_(long)  CSQLServerIO::CreateConnect()
{
	::CoInitialize(0);
	m_RecordSetCriticalSection  = std::tr1::shared_ptr <CriticalSection> (new CriticalSection());
	m_ConnectPtrCriticalSection = std::tr1::shared_ptr <CriticalSection> (new CriticalSection());
	SetConnectionState(CONNECTION_OFF);

	if (GetConnectionState()==CONNECTION_ON) CloseConnect();

	if (m_pIDataBase && m_pIDataBase->CreateConnect(m_ConnectPtr) == CREATE_CONNECT_SUCCESS)
	{
		SetConnectionState(CONNECTION_ON);
		return CREATE_CONNECT_SUCCESS;
	}
	else
	{
		SetConnectionState(CONNECTION_OFF);
		return CREATE_CONNECT_FAIL;
	}

}

CSQLServerIO::~CSQLServerIO()
{
	CloseConnect();
}

STDMETHODIMP_(std::wstring) CSQLServerIO::GetServerName() const
{
	GET_CSTRING(m_strDataSource);
}

STDMETHODIMP_(std::wstring) CSQLServerIO::GetServerUsr() const
{
	GET_CSTRING(m_strUserID);
}

STDMETHODIMP_(std::wstring) CSQLServerIO::GetServerPsd() const
{
	GET_CSTRING(m_strPassword);
}

STDMETHODIMP_(std::wstring) CSQLServerIO::GetDatabaseName() const
{
	GET_CSTRING(m_strInitialCatalog);
}

STDMETHODIMP_(std::wstring) CSQLServerIO::GetConnectionStr() const
{
	m_pIDataBase->SetConnectionString();
	GET_CSTRING(m_strConnectionString);
}

HRESULT __stdcall CSQLServerIO::QueryInterface(REFIID riid, void **ppvObject)
{
	if (IsEqualIID(riid, IID_IUnknown))
	{
		*ppvObject = (IUnknown*)this;
		((IUnknown*)*ppvObject)->AddRef();
		return S_OK;
	}
	else if (riid == IID_DATABASEMODULE)// IsEqualIID(riid, IID_DATABASEMODULE))//__uuidof(IDataBaseModule))
	{
		*ppvObject = (IDataBaseModule*)this;
		((IDataBaseModule*)*ppvObject)->AddRef();
		return S_OK;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
}

ULONG __stdcall CSQLServerIO::AddRef(void)
{
	m_nRef++;
	return m_nRef;
}

ULONG __stdcall CSQLServerIO::Release(void)
{
	m_nRef--;
	if (m_nRef == 0)
		delete this;

	return m_nRef;
}

/*
LC_BEGIN_IMPL_CLASS(CSQLServerIO)
LC_DO_IMPL_CLASS(IID_DATABASEMODULE, IDataBaseModule)
LC_END_IMPL_CLASS

LC_BEGIN_CREATE
LC_DO_CREATE(CSQLServerIO, CLSID_DATABASEMODULE)
LC_END_CREATE

LC_BEGIN_EXP
LC_DO_EXP(CSQLServerIO, CLSID_DATABASEMODULE, "xxj.2014/08/08", 0x10011, "数据库接口")
LC_END_EXP
*/