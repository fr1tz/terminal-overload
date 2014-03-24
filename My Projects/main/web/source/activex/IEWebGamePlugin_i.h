

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Mar 13 22:22:10 2014
 */
/* Compiler settings for ..\..\..\web\source\activex\IEWebGamePlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __IEWebGamePlugin_i_h__
#define __IEWebGamePlugin_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIEWebGameCtrl_FWD_DEFINED__
#define __IIEWebGameCtrl_FWD_DEFINED__
typedef interface IIEWebGameCtrl IIEWebGameCtrl;
#endif 	/* __IIEWebGameCtrl_FWD_DEFINED__ */


#ifndef __IEWebGameCtrl_FWD_DEFINED__
#define __IEWebGameCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class IEWebGameCtrl IEWebGameCtrl;
#else
typedef struct IEWebGameCtrl IEWebGameCtrl;
#endif /* __cplusplus */

#endif 	/* __IEWebGameCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IIEWebGameCtrl_INTERFACE_DEFINED__
#define __IIEWebGameCtrl_INTERFACE_DEFINED__

/* interface IIEWebGameCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IIEWebGameCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5240D24D-FBCE-4AF2-99FC-4C7AD4318E91")
    IIEWebGameCtrl : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_HWND( 
            /* [retval][out] */ LONG_PTR *pHWND) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVariable( 
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setVariable( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE exportFunction( 
            /* [in] */ BSTR callback,
            /* [in] */ LONG numArguments) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE callScript( 
            /* [in] */ BSTR code,
            /* [retval][out] */ BSTR *retValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE startup( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIEWebGameCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIEWebGameCtrl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIEWebGameCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIEWebGameCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIEWebGameCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIEWebGameCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIEWebGameCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIEWebGameCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HWND )( 
            IIEWebGameCtrl * This,
            /* [retval][out] */ LONG_PTR *pHWND);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getVariable )( 
            IIEWebGameCtrl * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ BSTR *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setVariable )( 
            IIEWebGameCtrl * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *exportFunction )( 
            IIEWebGameCtrl * This,
            /* [in] */ BSTR callback,
            /* [in] */ LONG numArguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *callScript )( 
            IIEWebGameCtrl * This,
            /* [in] */ BSTR code,
            /* [retval][out] */ BSTR *retValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *startup )( 
            IIEWebGameCtrl * This);
        
        END_INTERFACE
    } IIEWebGameCtrlVtbl;

    interface IIEWebGameCtrl
    {
        CONST_VTBL struct IIEWebGameCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIEWebGameCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIEWebGameCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIEWebGameCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIEWebGameCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIEWebGameCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIEWebGameCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIEWebGameCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIEWebGameCtrl_get_HWND(This,pHWND)	\
    ( (This)->lpVtbl -> get_HWND(This,pHWND) ) 

#define IIEWebGameCtrl_getVariable(This,name,value)	\
    ( (This)->lpVtbl -> getVariable(This,name,value) ) 

#define IIEWebGameCtrl_setVariable(This,name,value)	\
    ( (This)->lpVtbl -> setVariable(This,name,value) ) 

#define IIEWebGameCtrl_exportFunction(This,callback,numArguments)	\
    ( (This)->lpVtbl -> exportFunction(This,callback,numArguments) ) 

#define IIEWebGameCtrl_callScript(This,code,retValue)	\
    ( (This)->lpVtbl -> callScript(This,code,retValue) ) 

#define IIEWebGameCtrl_startup(This)	\
    ( (This)->lpVtbl -> startup(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIEWebGameCtrl_INTERFACE_DEFINED__ */



#ifndef __IEnotcPluginLib_LIBRARY_DEFINED__
#define __IEnotcPluginLib_LIBRARY_DEFINED__

/* library IEnotcPluginLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IEnotcPluginLib;

EXTERN_C const CLSID CLSID_IEWebGameCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("D62D1B36-253D-4218-B033-5ACE0B42B8BF")
IEWebGameCtrl;
#endif
#endif /* __IEnotcPluginLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


