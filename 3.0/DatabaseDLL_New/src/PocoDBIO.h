#ifndef __POCODBIO_H_
#define __POCODBIO_H_
#include <string>
#include <vector>
using namespace std;
#include "include\DefineFile.h"
#include "include\DatabaseIO.h"

//com 接口 路径，相对于程序路径
#ifdef _DEBUG
#define __DLL_PATH "./DatabaseDLLD.dll"
#else
#define __DLL_PATH "./DatabaseDLL.dll"
#endif

#define MS_SQL_SERVER_ODBC_DRIVER L"SQL Server"
#define MS_SQL_SERVER_SERVER L"192.168.1.133"
#define MS_SQL_SERVER_DB L"OATransTool"
#define MS_SQL_SERVER_UID L"st"
#define MS_SQL_SERVER_PWD L"123456" 

class S
{
public:
	vector<string> m_menberData;
	int m_menberCount;
	S(){};
	~S(){};
};

// 此类是从 PocoDBIO.dll 导出的
class PocoDBIO {
public:
	PocoDBIO(void);
	PocoDBIO(string DBName);
	PocoDBIO(string DBName, string server, string uId, string pwd);
	~PocoDBIO(void);
	int GetCount(string &SQL);//获取行数
	//int GetColumn(string &SQL);//获取列数
 	void GetOneData(const string &SQL, string &result);
 	void GetData(const string &SQL, vector<S> &result);
 	bool GetExist(const string &SQL);//执行指定的sql语句。返回该语句是否能查询出结果。
 	int GetColumnCount(string &Tablename);//获取表列数
 	
 	int GetTableCount(string &tableName);//获取表行数
 	void GetFields(string &tableName, string &columName, vector<string> &result);
 	void GetFields(string &tableName, int &columNum, vector<string> &result);

private:
	bool Init();//供构造函数调用的初始化函数
	void Relese();//释放
	string m_connectString;
	CSQLServerIO m_DataBaseSql;//
	std::wstring StringToWString(const std::string& s);//string 转wstring
};

#endif