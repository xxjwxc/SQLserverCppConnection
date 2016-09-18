#include "StdAfx.h"
#include "MyTools.h"

long IDataBase::SetServerInfo( std::wstring ServerName , std::wstring DatabaseName , std::wstring UserName , std::wstring UserPassword, std::wstring strConnectionStringOut )
{
	m_strDataSource = ServerName;
	m_strInitialCatalog = DatabaseName;
	m_strUserID = UserName;
	m_strPassword = UserPassword;
	m_strConnectionStringOut = strConnectionStringOut;

	SetConnectionString();
	return S_OK;

  // return CreateConnect(_connectPtr);
}

long CSQlServer::CreateConnect( _ConnectionPtr & _connectPtr )
{
	if(m_strConnectionString.empty()) 
		SetConnectionString();

	if (_connectPtr==NULL)
		_connectPtr.CreateInstance("ADODB.Connection");
	try
	{
		if(SUCCEEDED(_connectPtr->Open(m_strConnectionString.c_str(), "", "", adConnectUnspecified)))
		{
			return CREATE_CONNECT_SUCCESS;
		}
		//_connectPtr->Open(_bstr_t(sql),_bstr_t(SERVER_USR),_bstr_t(SERVER_PSD),adModeUnknown);
		return CREATE_CONNECT_FAIL;
	}
	catch(_com_error& e)
	{
#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
		return CREATE_CONNECT_FAIL;
	}
}

long CMySQl::CreateConnect( _ConnectionPtr & _connectPtr )
{
	if(m_strConnectionString.empty()) 
		SetConnectionString();

	if (_connectPtr==NULL)
		_connectPtr.CreateInstance("ADODB.Connection");
	try
	{
		if(SUCCEEDED(_connectPtr->Open(m_strConnectionString.c_str(), "", "", adConnectUnspecified)))
		{
			return CREATE_CONNECT_SUCCESS;
		}
		return CREATE_CONNECT_FAIL;
	}
	catch(_com_error& e)
	{
#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
		return CREATE_CONNECT_FAIL;
	}
}

long CACCESS::CreateConnect( _ConnectionPtr & _connectPtr )
{
	if(m_strConnectionString.empty()) 
		SetConnectionString();

	if (_connectPtr==NULL)
		_connectPtr.CreateInstance("ADODB.Connection");
	try
	{
		if(SUCCEEDED(_connectPtr->Open(m_strConnectionString.c_str(), _bstr_t(""), _bstr_t(""), adModeUnknown)))//adConnectUnspecified
		{
			return CREATE_CONNECT_SUCCESS;
		}
		return CREATE_CONNECT_FAIL;
	}
	catch(_com_error& e)
	{
#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
		return CREATE_CONNECT_FAIL;
	}
}

long COracle::CreateConnect( _ConnectionPtr & _connectPtr )
{
	if(m_strConnectionString.empty()) 
		SetConnectionString();

	if (_connectPtr==NULL)
		_connectPtr.CreateInstance("ADODB.Connection");

	_connectPtr->CursorLocation=adUseClient;
	try
	{
		if(SUCCEEDED(_connectPtr->Open(_bstr_t(m_strConnectionString.c_str()),(_bstr_t)_T(""),(_bstr_t)_T(""), adConnectUnspecified)))//adConnectUnspecified
		{
			return CREATE_CONNECT_SUCCESS;
		}
		return CREATE_CONNECT_FAIL;
	}
	catch(_com_error& e)
	{
#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
		return CREATE_CONNECT_FAIL;
	}
}

long CEXCEL::CreateConnect( _ConnectionPtr & _connectPtr )
{
	if(m_strConnectionString.empty()) 
		SetConnectionString();

	if (_connectPtr==NULL)
		_connectPtr.CreateInstance("ADODB.Connection");
	try
	{
		if(SUCCEEDED(_connectPtr->Open(_bstr_t(m_strConnectionString.c_str()), _bstr_t(m_strUserID.c_str()), _bstr_t(m_strPassword.c_str()), adModeUnknown)))//adConnectUnspecified
		{
			return CREATE_CONNECT_SUCCESS;
		}
		return CREATE_CONNECT_FAIL;
	}
	catch(_com_error& e)
	{
#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
		return CREATE_CONNECT_FAIL;
	}
}

/*
long CFoxPro::CreateConnect( _ConnectionPtr & _connectPtr )
{
	if(m_strConnectionString.empty()) 
		SetConnectionString();

	if (_connectPtr==NULL)
		_connectPtr.CreateInstance("ADODB.Connection");
	try
	{
		if(SUCCEEDED(_connectPtr->Open(_bstr_t(m_strConnectionString.c_str()), _bstr_t(m_strUserID.c_str()), _bstr_t(m_strPassword.c_str()), adModeUnknown)))//adConnectUnspecified
		{
			return true;
		}
		return CREATE_CONNECT_SUCCESS;
	}
	catch(_com_error& e)
	{
#pragma message(FILE_LINE_TEXT "数据库失败位置：")
		COM_ERROR_MESSAGE_OUT;
		return CREATE_CONNECT_FAIL;
	}
}
*/