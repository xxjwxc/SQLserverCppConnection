/********************************************************************
	创建时间：	2014/10/08  11:42:49 
	文件名：    	MyObjectFactory.h
	作者：		谢小军
	
	功能：		1.用于com工厂类创建
				2.
				
	说明：	    1. 当我们调用CoCreateInstance函数创建com对象的时候，com标准库会调用DllGetClassObject获取工厂对象，再由工厂对象调用其成员函数CreateInstance来创建我们需要的com对象。
				2. 
*********************************************************************/
#ifndef __MYOBJECTFACTORY_H_
#define __MYOBJECTFACTORY_H_
#include <Unknwn.h>

extern ULONG    g_LockNumber;
class CObjectFactory :public IClassFactory
{
protected:
	int m_nRef;
public:
	CObjectFactory(void);
public:
	~CObjectFactory(void);
public:
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);
public:
	HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject);
	HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);
};

#endif