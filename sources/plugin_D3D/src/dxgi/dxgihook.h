#include <dxgi.h>

#include "../hooktools.h"

#pragma once

#undef THIS_
#define THIS_                   INTERFACE * This,
#undef THIS
#define THIS                    INTERFACE * This
#undef STDMETHOD
#define STDMETHOD(method)       DECLARE_FUNCTION_PTR(method)
#undef STDMETHOD_
#define STDMETHOD_(type,method) DECLARE_FUNCTION_PTR_(type,method)

// Create function pointer types
#undef INTERFACE
#define INTERFACE IDXGISwapChain

STDMETHOD( QueryInterface )DECLARE_PARAMS(
    THIS,
    /* [in] */ REFIID riid,
    /* [annotation][iid_is][out] */
    __RPC__deref_out  void** ppvObject );

STDMETHOD_( ULONG, AddRef )DECLARE_PARAMS(
    THIS );

STDMETHOD_( ULONG, Release )DECLARE_PARAMS(
    THIS );

STDMETHOD( SetPrivateData )DECLARE_PARAMS(
    THIS,
    /* [in] */ REFGUID Name,
    /* [in] */ UINT DataSize,
    /* [in] */ const void* pData );

STDMETHOD( SetPrivateDataInterface )DECLARE_PARAMS(
    THIS,
    /* [in] */ REFGUID Name,
    /* [in] */ const IUnknown* pUnknown );

STDMETHOD( GetPrivateData )DECLARE_PARAMS(
    THIS,
    /* [in] */ REFGUID Name,
    /* [out][in] */ UINT* pDataSize,
    /* [out] */ void* pData );

STDMETHOD( GetParent )DECLARE_PARAMS(
    THIS,
    /* [in] */ REFIID riid,
    /* [retval][out] */ void** ppParent );

STDMETHOD( GetDevice )DECLARE_PARAMS(
    THIS,
    /* [in] */ REFIID riid,
    /* [retval][out] */ void** ppDevice );

STDMETHOD( Present )DECLARE_PARAMS(
    THIS,
    /* [in] */ UINT SyncInterval,
    /* [in] */ UINT Flags );

STDMETHOD( GetBuffer )DECLARE_PARAMS(
    THIS,
    /* [in] */ UINT Buffer,
    /* [in] */ REFIID riid,
    /* [out][in] */ void** ppSurface );

STDMETHOD( SetFullscreenState )DECLARE_PARAMS(
    THIS,
    /* [in] */ BOOL Fullscreen,
    /* [in] */ IDXGIOutput* pTarget );

STDMETHOD( GetFullscreenState )DECLARE_PARAMS(
    THIS,
    /* [out] */ BOOL* pFullscreen,
    /* [out] */ IDXGIOutput** ppTarget );

STDMETHOD( GetDesc )DECLARE_PARAMS(
    THIS,
    /* [out] */ DXGI_SWAP_CHAIN_DESC* pDesc );

STDMETHOD( ResizeBuffers )DECLARE_PARAMS(
    THIS,
    /* [in] */ UINT BufferCount,
    /* [in] */ UINT Width,
    /* [in] */ UINT Height,
    /* [in] */ DXGI_FORMAT NewFormat,
    /* [in] */ UINT SwapChainFlags );

STDMETHOD( ResizeTarget )DECLARE_PARAMS(
    THIS,
    /* [in] */ const DXGI_MODE_DESC* pNewTargetParameters );

STDMETHOD( GetContainingOutput )DECLARE_PARAMS(
    THIS,
    IDXGIOutput** ppOutput );

STDMETHOD( GetFrameStatistics )DECLARE_PARAMS(
    THIS,
    /* [out] */ DXGI_FRAME_STATISTICS* pStats );

STDMETHOD( GetLastPresentCount )DECLARE_PARAMS(
    THIS,
    /* [out] */ UINT* pLastPresentCount );

// Create vtable offsets
#undef STDMETHOD
#define STDMETHOD(method) PPCAT(PPCAT(PPCAT(vt, INTERFACE),_), method),
#undef STDMETHOD_
#define STDMETHOD_(type,method) PPCAT(PPCAT(PPCAT(vt, INTERFACE),_), method),

enum PPCAT( vt, INTERFACE )
{
    STDMETHOD( QueryInterface )
    STDMETHOD_( ULONG, AddRef )
    STDMETHOD_( ULONG, Release )
    STDMETHOD( SetPrivateData )
    STDMETHOD( SetPrivateDataInterface )
    STDMETHOD( GetPrivateData )
    STDMETHOD( GetParent )
    STDMETHOD( GetDevice )
    STDMETHOD( Present )
    STDMETHOD( GetBuffer )
    STDMETHOD( SetFullscreenState )
    STDMETHOD( GetFullscreenState )
    STDMETHOD( GetDesc )
    STDMETHOD( ResizeBuffers )
    STDMETHOD( ResizeTarget )
    STDMETHOD( GetContainingOutput )
    STDMETHOD( GetFrameStatistics )
    STDMETHOD( GetLastPresentCount )
};