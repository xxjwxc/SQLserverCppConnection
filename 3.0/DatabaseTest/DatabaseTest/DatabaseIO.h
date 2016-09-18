#pragma once
#include "DefineFile.h"
interface IDataBase;
class CriticalSection;

/*
	客户端开发需导入DatabaseIO.h DefineFile.h 这两个文件
*/

//客户程序请注释掉此宏
//#define DLL_BUILD

#ifdef DLL_BUILD
#define DLLIMPORT __declspec(dllexport)
#else
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#define DLLIMPORT __declspec(dllimport)
#endif

// 数据库类型
typedef enum enumDATABASE_TYPE : UINT
{
	SQLSERVER	= 0,	// SQL Server 数据库
	ORACLE		= 1,	// Oracle 数据库
	ACCESS		= 2,	// ACCESS 数据库
	MYSQL		= 3,	// MySQL  数据库
	EXCEL		= 4,    // Excel  数据库
//	FOXPRO		= 5,    // FoxPro 数据库
}DATABASE_TYPE;

interface DLLIMPORT IDatabaseIO
{
public:
	IDatabaseIO(void);
	virtual ~IDatabaseIO(void);

	long MyExecute(TCHAR * SQL);
	long MyExecute(CString & SQL);

	long  MyQuarty(TCHAR * SQL , _RecordsetPtr & m_RecordSetPtr);
	long  MyQuarty(CString & , _RecordsetPtr & m_RecordSetPtr);

	long  GetCount(TCHAR * SQL);
	long  GetCount(CString & SQL);
	long  GetCount(_RecordsetPtr & record);

	long  GetTableCount(TCHAR * TableName);
	long  GetTableCount(CString & TableName);

	long  GetExist(TCHAR * SQL);
	long  GetExist(CString & SQL);
	long  GetExist(_RecordsetPtr & record);

	long  GetTableData(TCHAR * TableName , _RecordsetPtr & record);
	long  GetTableData(CString & TableName , _RecordsetPtr & record);

	long  GetColumnCount(TCHAR * TableName);
	long  GetColumnCount(_RecordsetPtr & record);
	long  GetColumnCount(CString & Tablename);

	long  GetColumnName(TCHAR * TableName , int & ColumnNum ,TCHAR * ColumnName);
	long  GetColumnName(CString & Tablename ,int & ColumnNum ,CString &  ColumnName);
	long  GetColumnName(_RecordsetPtr & m_record , int & ColumnNum ,TCHAR * ColumnName);
	long  GetColumnName(_RecordsetPtr & m_record , int & ColumnNum ,CString & ColumnName);

	long  GetColumnNameList(TCHAR * TableName ,map<int,string> & ColumnName);
	long  GetColumnNameList(CString & Tablename ,map<int,CString> ColumnName);
	long  GetColumnNameList(_RecordsetPtr & m_record , map<int,string> & ColumnName);
	long  GetColumnNameList(_RecordsetPtr & m_record ,map<int,CString> ColumnName);


	virtual long  CreateConnect()=0;
	void  CloseConnect();
	inline void  SetConnectionState(BOOL bState){m_ConnectionState=bState;}
	inline BOOL  GetConnectionState(){return m_ConnectionState;}
 	inline _RecordsetPtr &  GetRecordSet(){return m_RecordSet;}
 	inline _ConnectionPtr &  GetConnectionPtr(){return m_ConnectPtr;}

protected:
	_RecordsetPtr m_RecordSet;
	_ConnectionPtr m_ConnectPtr;
	std::tr1::shared_ptr<CriticalSection>  m_RecordSetCriticalSection;
	std::tr1::shared_ptr<CriticalSection> m_ConnectPtrCriticalSection;

	BOOL m_ConnectionState;
};


class DLLIMPORT CSQLServerIO:public IDatabaseIO
{
public:

	explicit CSQLServerIO(std::wstring ServerName ,std::wstring DatabaseName ,DATABASE_TYPE enumData_type = DATABASE_TYPE::SQLSERVER ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ,IDataBase * pIDataBase = NULL);
	~CSQLServerIO();

	long  SetServerInfo(TCHAR * ServerName ,TCHAR * DatabaseName);
	long  SetServerInfo(CString &  ServerName ,CString &  DatabaseName);
	long  SetServerInfo(TCHAR * ServerName ,TCHAR * DatabaseName ,TCHAR * UserName ,TCHAR * UserPassword);
	long  SetServerInfo(CString &  ServerName ,CString &  DatabaseName ,CString &  UserName ,CString &  UserPassword);

	long  CreateConnect();

	std::wstring GetServerName() const;
	std::wstring GetServerUsr() const;
	std::wstring GetServerPsd() const;
	std::wstring GetDatabaseName() const;
	std::wstring GetConnectionStr() const;

private:
	//IDataBase * m_pIDataBase;
	//BOOL m_isInternalBuild;//是否内部构建
	std::tr1::shared_ptr<IDataBase> m_pIDataBase;
};

#ifndef DLL_BUILD
class  _declspec(dllimport) CSQLServerIO;
#endif 