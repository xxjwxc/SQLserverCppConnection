#pragma once
#include "DefineFile.h"
#include "IDatabaseIO.h"
#include "MyTools.h"

class CriticalSection;

class CSQLServerIO : public IDataBaseModule
{
public:
	STDMETHOD_(long, MyExecute)(TCHAR * SQL);
	STDMETHOD_(long, MyExecute)(CString & SQL);

	STDMETHOD_(long,  MyQuarty)(TCHAR * SQL , _RecordsetPtr & m_RecordSetPtr);
	STDMETHOD_(long,  MyQuarty)(CString & , _RecordsetPtr & m_RecordSetPtr);

	STDMETHOD_(long,  GetCount)(TCHAR * SQL);
	STDMETHOD_(long,  GetCount)(CString & SQL);
	STDMETHOD_(long,  GetCount)(_RecordsetPtr & record);

	STDMETHOD_(long,  GetTableCount)(TCHAR * TableName);
	STDMETHOD_(long,  GetTableCount)(CString & TableName);

	STDMETHOD_(long,  GetExist)(TCHAR * SQL);
	STDMETHOD_(long,  GetExist)(CString & SQL);
	STDMETHOD_(long,  GetExist)(_RecordsetPtr & record);

	STDMETHOD_(long,  GetTableData)(TCHAR * TableName , _RecordsetPtr & record);
	STDMETHOD_(long,  GetTableData)(CString & TableName , _RecordsetPtr & record);

	STDMETHOD_(long,  GetColumnCount)(TCHAR * TableName);
	STDMETHOD_(long,  GetColumnCount)(_RecordsetPtr & record);
	STDMETHOD_(long,  GetColumnCount)(CString & Tablename);

	STDMETHOD_(long,  GetColumnName)(TCHAR * TableName , int & ColumnNum ,TCHAR * ColumnName);
	STDMETHOD_(long,  GetColumnName)(CString & Tablename ,int & ColumnNum ,CString &  ColumnName);
	STDMETHOD_(long,  GetColumnName)(_RecordsetPtr & m_record , int & ColumnNum ,TCHAR * ColumnName);
	STDMETHOD_(long,  GetColumnName)(_RecordsetPtr & m_record , int & ColumnNum ,CString & ColumnName);

	STDMETHOD_(long,  GetColumnNameList)(TCHAR * TableName ,map<int,string> & ColumnName);
	STDMETHOD_(long,  GetColumnNameList)(CString & Tablename ,map<int,CString> ColumnName) ;
	STDMETHOD_(long,  GetColumnNameList)(_RecordsetPtr & m_record , map<int,string> & ColumnName) ;
	STDMETHOD_(long,  GetColumnNameList)(_RecordsetPtr & m_record ,map<int,CString> ColumnName);

	STDMETHOD_(void,  CloseConnect)();
	STDMETHOD_(void,  SetConnectionState)(BOOL bState){m_ConnectionState=bState;}
	STDMETHOD_(BOOL,  GetConnectionState)(){return m_ConnectionState;}
 	STDMETHOD_(_RecordsetPtr & , GetRecordSet)(){return m_RecordSet;}
 	STDMETHOD_(_ConnectionPtr &,  GetConnectionPtr)(){return m_ConnectPtr;}

protected:
	_RecordsetPtr m_RecordSet;
	_ConnectionPtr m_ConnectPtr;
	std::tr1::shared_ptr<CriticalSection>  m_RecordSetCriticalSection;
	std::tr1::shared_ptr<CriticalSection> m_ConnectPtrCriticalSection;

	BOOL m_ConnectionState;

public:
	CSQLServerIO(){};
	virtual ~CSQLServerIO();

	STDMETHOD_(long, OnInit)(std::wstring ServerName ,std::wstring DatabaseName ,DATABASE_TYPE enumData_type = DATABASE_TYPE::SQLSERVER ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ,/*IDataBase*/void * pIDataBase = NULL);
	STDMETHOD_(long,  SetServerInfo)(TCHAR * ServerName ,TCHAR * DatabaseName);
	STDMETHOD_(long,  SetServerInfo)(CString &  ServerName ,CString &  DatabaseName);
	STDMETHOD_(long,  SetServerInfo)(TCHAR * ServerName ,TCHAR * DatabaseName ,TCHAR * UserName ,TCHAR * UserPassword) ;
	STDMETHOD_(long,  SetServerInfo)(CString &  ServerName ,CString &  DatabaseName ,CString &  UserName ,CString &  UserPassword);

	STDMETHOD_(long,  CreateConnect)();

	STDMETHOD_(std::wstring, GetServerName)() const;
	STDMETHOD_(std::wstring, GetServerUsr)() const ;
	STDMETHOD_(std::wstring, GetServerPsd)() const ;
	STDMETHOD_(std::wstring, GetDatabaseName)() const ;
	STDMETHOD_(std::wstring, GetConnectionStr)() const ;


private:
	//IDataBase * m_pIDataBase;
	//BOOL m_isInternalBuild;//是否内部构建
	std::tr1::shared_ptr<IDataBase> m_pIDataBase;
};

// LC_DECLARE_CLASS(CSQLServerIO)//导出类
//LC_DECLARE_EXP