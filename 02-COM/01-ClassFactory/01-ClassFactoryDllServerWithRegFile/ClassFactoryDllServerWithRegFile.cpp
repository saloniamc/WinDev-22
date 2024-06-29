#include <Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//Co-Class com class/ concrete class / final class (cannot be inherited as absence of virtual method)
class CSumSubstract : public ISum, ISubstract
{
private:
	long m_cRef;
public:
	//Constructor
	CSumSubstract(void);

	//Destructor
	~CSumSubstract(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum Method
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	//ISubstract Method
	HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*);

};

//ClassFacotry Class

class CSumSubstractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	//Constructor
	CSumSubstractClassFactory(void);

	//Destructor
	~CSumSubstractClassFactory(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory Methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);

};

//Global Variables
LONG glNumberOfActiveComponents;
LONG glNumberOfServerLocks;

//DLLMain
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	// Code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return (TRUE);
}

//CSumSubstract Implementation
//Constructor 
CSumSubstract::CSumSubstract(void)
{
	//Code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//Destructor
CSumSubstract::~CSumSubstract(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//IUnknown Method Implementations
HRESULT CSumSubstract::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast <ISum*>(this);
	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast <ISum*>(this);
	}
	else if (riid == IID_ISubstract)
	{
		*ppv = static_cast <ISubstract*>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv) -> AddRef();
	return(S_OK);
}

ULONG CSumSubstract::AddRef(void)
{
	//Code
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG CSumSubstract::Release(void)
{
	//Code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete this;
		return(0);
	}
	return(m_cRef);
}

//ISum Implementation
HRESULT CSumSubstract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	//Code 
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubstract::SubstractionOfTwoIntegers(int num1, int num2, int* pSubstract)
{
	//Code
	*pSubstract = num1 - num2;
	return(S_OK);
}

//CSumSubstract ClassFactory Implementation
//Constructor
CSumSubstractClassFactory::CSumSubstractClassFactory(void)
{
	//Code
	m_cRef = 1;
}

//Destructor
CSumSubstractClassFactory::~CSumSubstractClassFactory(void)
{
	//Code
}

//IUknown Method Implementation
HRESULT CSumSubstractClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	//Code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) 
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv) -> AddRef();
	return(S_OK);
}

ULONG CSumSubstractClassFactory::AddRef(void)
{
	//Code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubstractClassFactory::Release(void)
{
	//Code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete this;
		return(0);
	}
	return(m_cRef);
	
}

//IClassFactory's Methods Implementation
HRESULT CSumSubstractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//Variable Declarations
	CSumSubstract* pCSumSubstract = NULL;
	HRESULT hR;

	//Code 
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	pCSumSubstract = new CSumSubstract;
	if (pCSumSubstract == NULL)
		return(E_OUTOFMEMORY);
	hR = pCSumSubstract->QueryInterface(riid, ppv);
	pCSumSubstract->Release();
	return(hR);
}

HRESULT CSumSubstractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

//Exportable COM DLL Methods
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//Variable Declarations
	CSumSubstractClassFactory* pCSumSubstractClassfactory = NULL;
	HRESULT hR;

	if (rclsid != CLSID_SumSubstract)
		return(CLASS_E_CLASSNOTAVAILABLE);
	pCSumSubstractClassfactory = new CSumSubstractClassFactory;
	if (pCSumSubstractClassfactory == NULL)
		return(E_OUTOFMEMORY);
	hR = pCSumSubstractClassfactory->QueryInterface(riid, ppv);
	pCSumSubstractClassfactory->Release();
	return(hR);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//Code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}

