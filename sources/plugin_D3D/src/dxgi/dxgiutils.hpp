#include <dxgi.h>
#include <PMUtils.hpp>

#pragma once

static string getOutputName( IDXGISwapChain* pSwapChain )
{
    string sRet = "";

    if ( pSwapChain )
    {
        IDXGIOutput* pOutput = NULL;
        pSwapChain->GetContainingOutput( &pOutput );

        if ( pOutput )
        {
            DXGI_OUTPUT_DESC desc;

            if ( SUCCEEDED( pOutput->GetDesc( &desc ) ) )
            {
                sRet = PluginManager::UTF82ACP( PluginManager::UCS22UTF8( desc.DeviceName ) );
            }

            SAFE_RELEASE( pOutput );
        }
    }

    return sRet;
}

static string getGPUName( IUnknown* pDevice )
{
    string sRet = "";

    IDXGIDevice* pDXGIDevice = NULL;
    pDevice->QueryInterface( __uuidof( IDXGIDevice ), ( void** )&pDXGIDevice );

    if ( pDXGIDevice )
    {
        IDXGIAdapter* pDXGIAdapter = NULL;
        pDXGIDevice->GetAdapter( &pDXGIAdapter );

        if ( pDXGIAdapter )
        {
            DXGI_ADAPTER_DESC adapterDesc;
            pDXGIAdapter->GetDesc( &adapterDesc );
            sRet = PluginManager::UTF82ACP( PluginManager::UCS22UTF8( adapterDesc.Description ) );
            SAFE_RELEASE( pDXGIAdapter );
        }

        SAFE_RELEASE( pDXGIDevice );
    }

    return sRet;
}