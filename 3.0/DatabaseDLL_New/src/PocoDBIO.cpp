#include "stdafx.h"
#include "PocoDBIO.h"
#include "include\DatabaseIO.h"

PocoDBIO::PocoDBIO( void )
{
	if(Init())
	{
		wstring driver = MS_SQL_SERVER_ODBC_DRIVER;//未使用
		wstring server = MS_SQL_SERVER_SERVER;
		wstring db = MS_SQL_SERVER_DB;
		wstring uid = MS_SQL_SERVER_UID;
		wstring pwd = MS_SQL_SERVER_PWD;
		if (m_DataBaseSql.OnInit(server,db,DATABASE_TYPE::SQLSERVER,uid,pwd) != CREATE_CONNECT_SUCCESS)//创建成功
		{
			ASSERT(false);//此处应该是创建参数有问题
			Relese();
		}
	}
}

PocoDBIO::PocoDBIO( string DBName )
{
	if(Init())
	{
		wstring driver = MS_SQL_SERVER_ODBC_DRIVER;//未使用
		wstring server = MS_SQL_SERVER_SERVER;
		wstring uid = MS_SQL_SERVER_UID;
		wstring pwd = MS_SQL_SERVER_PWD;
		wstring db = StringToWString(DBName);
		if (m_DataBaseSql.OnInit(server,db,DATABASE_TYPE::SQLSERVER,uid,pwd) != CREATE_CONNECT_SUCCESS)//创建成功
		{
			ASSERT(false);//此处应该是创建参数有问题
			Relese();
		}
	}

}

PocoDBIO::PocoDBIO( string DBName1, string server1, string uId1, string pwd1 )
{
	if(Init())
	{
		wstring db = StringToWString(DBName1);
		wstring server = StringToWString(server1);
		wstring uid = StringToWString(uId1);
		wstring pwd = StringToWString(pwd1);
		if (m_DataBaseSql.OnInit(server,db,DATABASE_TYPE::SQLSERVER,uid,pwd) != CREATE_CONNECT_SUCCESS)//创建成功
		{
			ASSERT(false);//此处应该是创建参数有问题
			Relese();
		}
	}
}

PocoDBIO::~PocoDBIO( void )
{
	Relese();
}

bool PocoDBIO::Init()
{
	return true;
	// 	if (m_lpiDataBaseSql)
	// 		Relese();
	// 
	// 	m_lpiDataBaseSql = (CSQLServerIO *)malloc(sizeof(CSQLServerIO));// new CSQLServerIO();

	//	return true;
	// 	if (CreatIDataBaseSql(__DLL_PATH,m_lpiDataBaseSql))
	// 		return true;
	// 	else
	// 	{
	// 		ASSERT(false);//此处应该是未找到dll位置,请修改__DLL_PATH值
	// 		return false;
	// 	}
}

void PocoDBIO::Relese()
{
	// 	if (m_lpiDataBaseSql)
	// 		free(m_lpiDataBaseSql);
	// 		//delete m_lpiDataBaseSql;
	// 
	// 	m_lpiDataBaseSql = NULL;
	// 	{
	// 		ReleaseIDataBaseSql(m_lpiDataBaseSql);//释放
	// 		m_lpiDataBaseSql = NULL;
	// 	}
}

std::wstring PocoDBIO::StringToWString( const std::string& s )
{
	std::wstring wszStr;
	int nLength = MultiByteToWideChar( CP_ACP, 0, s.c_str(), -1, NULL, NULL );
	wszStr.resize(nLength);
	LPWSTR lpwszStr = new wchar_t[nLength];
	MultiByteToWideChar( CP_ACP, 0, s.c_str(), -1, lpwszStr, nLength );
	wszStr = lpwszStr;
	delete [] lpwszStr;
	return wszStr;
}


int PocoDBIO::GetCount( string &SQL )
{
	if (SQL != "")
	{
		CString cstr( StringToWString(SQL).c_str());
		return m_DataBaseSql.GetCount(cstr);
	}
	return -1;	
}


void PocoDBIO::GetOneData( const string &SQL, string &result )
{
	CString cstr(StringToWString(SQL).c_str());
	_RecordsetPtr _RecordSetPtr;
	m_DataBaseSql.MyQuarty(cstr,_RecordSetPtr);
	int resultRow = _RecordSetPtr->GetRecordCount();//获取行数
	int resultCol = _RecordSetPtr-> GetFields()-> GetCount();//获取列数
	if (resultRow == 1 && resultCol == 1)
	{
		_variant_t bsCloumnName=_RecordSetPtr->GetCollect(_variant_t((long)0));
		if(bsCloumnName.vt!=VT_NULL)
			result = (char *)(_bstr_t)(bsCloumnName);
		else
			result = "";
		return ;
	}
	else if (resultRow > 1 || resultCol > 1)
	{
		result = "please use function GetData(const string &SQ).";
		return;
	}
	else
	{
		result = "error.";
		return;
	}
	_RecordSetPtr->Close();

	return ;
}

void PocoDBIO::GetData( const string &SQL, vector<S> &result )
{
	result.clear();

	CString cstr(StringToWString(SQL).c_str());
	_RecordsetPtr _RecordSetPtr;
	m_DataBaseSql.MyQuarty(cstr,_RecordSetPtr);
	int resultRow = _RecordSetPtr->GetRecordCount();//获取行数
	int resultCol = _RecordSetPtr-> GetFields()-> GetCount();//获取列数
	if (resultRow > 0)
	{
		while(!_RecordSetPtr->adoEOF)
		{
			S stemp;
			stemp.m_menberCount = resultCol;
			for (int col = 0; col < resultCol; ++col)
				stemp.m_menberData.push_back((char *)(_bstr_t)(_RecordSetPtr->GetCollect(_variant_t((long)col))));

			result.push_back(stemp);
			_RecordSetPtr->MoveNext();
		}
	}
	else
	{	//如果查询结果为空，则返回一个空的记录。
		S stemp;
		stemp.m_menberCount = resultCol;
		for (int col = 0; col < resultCol; ++col)
		{
			stemp.m_menberData.push_back("");
		}
		result.push_back(stemp);
	}

	_RecordSetPtr->Close();

}

bool PocoDBIO::GetExist( const string &SQL )
{

	CString cstr( StringToWString(SQL).c_str());
	long err = m_DataBaseSql.GetExist(cstr);
	if (err == DATA_EXIST)
		return true;
	else
		return false;

}

int PocoDBIO::GetColumnCount( string &Tablename )
{
	if (Tablename.length() > 0)
	{
		CString cstr;
		cstr.Format("SELECT * FROM %s",CString(StringToWString(Tablename).c_str()));
		return m_DataBaseSql.GetColumnCount(cstr);
	}

	return -1;
}

int PocoDBIO::GetTableCount( string &tableName )
{
	string temp = "select * from " + tableName + ";";
	return GetCount(temp);
}

void PocoDBIO::GetFields( string &tableName, string &columName, vector<string> &result )
{
	result.clear();
	string SQLtemp = "select " + columName + " from " + tableName + " ;";
	CString cstr( StringToWString(SQLtemp).c_str());
	_RecordsetPtr _RecordSetPtr;
	m_DataBaseSql.MyQuarty(cstr,_RecordSetPtr);

	while(!_RecordSetPtr->adoEOF)
	{
		result.push_back((char *)(_bstr_t)(_RecordSetPtr->GetCollect(_variant_t((long)0))));
		_RecordSetPtr->MoveNext();
	}
	_RecordSetPtr->Close();
}

void PocoDBIO::GetFields( string &tableName, int &columNum, vector<string> &result )
{

	result.clear();
	string SQLtemp = "select * from " + tableName + " ;";
	CString cstr( StringToWString(SQLtemp).c_str());
	_RecordsetPtr _RecordSetPtr;
	m_DataBaseSql.MyQuarty(cstr,_RecordSetPtr);

	while(!_RecordSetPtr->adoEOF)
	{
		result.push_back((char *)(_bstr_t)(_RecordSetPtr->GetCollect(_variant_t((long)columNum))));
		_RecordSetPtr->MoveNext();
	}
	_RecordSetPtr->Close();
}


