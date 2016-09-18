#include "StdAfx.h"
#include "MyObjectFactory.h"
#include "DatabaseIO.h"
extern ULONG    g_LockNumber = 0;

CObjectFactory::CObjectFactory(void)
	:m_nRef(0)
{
}

CObjectFactory::~CObjectFactory(void)
{
}

HRESULT  CObjectFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	if (riid == __uuidof(IUnknown))
	{
		*ppvObject = (IUnknown*)this;
		((IUnknown*)*ppvObject)->AddRef();
		return S_OK;
	}
	else if (riid == __uuidof(IClassFactory))
	{
		*ppvObject = (IClassFactory*)this;
		((IClassFactory*)*ppvObject)->AddRef();
		return S_OK;
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
}
ULONG CObjectFactory::AddRef(void)
{
	m_nRef++;
	return m_nRef;
}
ULONG CObjectFactory::Release(void)
{
	m_nRef--;
	if (m_nRef == 0)
	{
		delete this;
	}
	return m_nRef;
}
HRESULT CObjectFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
{
	if (NULL != pUnkOuter)
		return CLASS_E_NOAGGREGATION;
	TRACE(L"Enter CreateInstance...");
	CSQLServerIO *pObj = NULL;
	pObj = new CSQLServerIO();
	if (pObj == NULL)
	{
		*ppvObject = NULL;
		return E_OUTOFMEMORY;
	}
	HRESULT hr = pObj->QueryInterface(riid, ppvObject);
	if (FAILED(hr))
	{
		TRACE(L"Failed to Create TestObj!");
		delete pObj;
	}
	return hr;
}
HRESULT CObjectFactory::LockServer(BOOL fLock)
{
	if (fLock)
	{
		g_LockNumber++;
	}
	else
		g_LockNumber--;
	return NOERROR;
}