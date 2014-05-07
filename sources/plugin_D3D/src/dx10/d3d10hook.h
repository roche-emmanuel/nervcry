#include <d3d10.h>
#include <D3D10SDKLayers.h>

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
#define INTERFACE ID3D10Device

// from d3d10.h vtable:
STDMETHOD( QueryInterface )DECLARE_PARAMS(
    THIS,
    /* [in] */ REFIID riid,
    /* [annotation][iid_is][out] */
    __RPC__deref_out  void** ppvObject );

STDMETHOD_( ULONG, AddRef )DECLARE_PARAMS(
    THIS );

STDMETHOD_( ULONG, Release )DECLARE_PARAMS(
    THIS );

STDMETHOD_( void, VSSetConstantBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __in_ecount( NumBuffers )  ID3D10Buffer* const* ppConstantBuffers );

STDMETHOD_( void, PSSetShaderResources )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
    /* [annotation] */
    __in_ecount( NumViews )  ID3D10ShaderResourceView* const* ppShaderResourceViews );

STDMETHOD_( void, PSSetShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10PixelShader* pPixelShader );

STDMETHOD_( void, PSSetSamplers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
    /* [annotation] */
    __in_ecount( NumSamplers )  ID3D10SamplerState* const* ppSamplers );

STDMETHOD_( void, VSSetShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10VertexShader* pVertexShader );

STDMETHOD_( void, DrawIndexed )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  UINT IndexCount,
    /* [annotation] */
    __in  UINT StartIndexLocation,
    /* [annotation] */
    __in  INT BaseVertexLocation );

STDMETHOD_( void, Draw )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  UINT VertexCount,
    /* [annotation] */
    __in  UINT StartVertexLocation );

STDMETHOD_( void, PSSetConstantBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __in_ecount( NumBuffers )  ID3D10Buffer* const* ppConstantBuffers );

STDMETHOD_( void, IASetInputLayout )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10InputLayout* pInputLayout );

STDMETHOD_( void, IASetVertexBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __in_ecount( NumBuffers )  ID3D10Buffer* const* ppVertexBuffers,
    /* [annotation] */
    __in_ecount( NumBuffers )  const UINT* pStrides,
    /* [annotation] */
    __in_ecount( NumBuffers )  const UINT* pOffsets );

STDMETHOD_( void, IASetIndexBuffer )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10Buffer* pIndexBuffer,
    /* [annotation] */
    __in  DXGI_FORMAT Format,
    /* [annotation] */
    __in  UINT Offset );

STDMETHOD_( void, DrawIndexedInstanced )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  UINT IndexCountPerInstance,
    /* [annotation] */
    __in  UINT InstanceCount,
    /* [annotation] */
    __in  UINT StartIndexLocation,
    /* [annotation] */
    __in  INT BaseVertexLocation,
    /* [annotation] */
    __in  UINT StartInstanceLocation );

STDMETHOD_( void, DrawInstanced )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  UINT VertexCountPerInstance,
    /* [annotation] */
    __in  UINT InstanceCount,
    /* [annotation] */
    __in  UINT StartVertexLocation,
    /* [annotation] */
    __in  UINT StartInstanceLocation );

STDMETHOD_( void, GSSetConstantBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __in_ecount( NumBuffers )  ID3D10Buffer* const* ppConstantBuffers );

STDMETHOD_( void, GSSetShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10GeometryShader* pShader );

STDMETHOD_( void, IASetPrimitiveTopology )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  D3D10_PRIMITIVE_TOPOLOGY Topology );

STDMETHOD_( void, VSSetShaderResources )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
    /* [annotation] */
    __in_ecount( NumViews )  ID3D10ShaderResourceView* const* ppShaderResourceViews );

STDMETHOD_( void, VSSetSamplers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
    /* [annotation] */
    __in_ecount( NumSamplers )  ID3D10SamplerState* const* ppSamplers );

STDMETHOD_( void, SetPredication )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10Predicate* pPredicate,
    /* [annotation] */
    __in  BOOL PredicateValue );

STDMETHOD_( void, GSSetShaderResources )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
    /* [annotation] */
    __in_ecount( NumViews )  ID3D10ShaderResourceView* const* ppShaderResourceViews );

STDMETHOD_( void, GSSetSamplers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
    /* [annotation] */
    __in_ecount( NumSamplers )  ID3D10SamplerState* const* ppSamplers );

STDMETHOD_( void, OMSetRenderTargets )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT )  UINT NumViews,
    /* [annotation] */
    __in_ecount_opt( NumViews )  ID3D10RenderTargetView* const* ppRenderTargetViews,
    /* [annotation] */
    __in_opt  ID3D10DepthStencilView* pDepthStencilView );

STDMETHOD_( void, OMSetBlendState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10BlendState* pBlendState,
    /* [annotation] */
    __in  const FLOAT BlendFactor[ 4 ],
    /* [annotation] */
    __in  UINT SampleMask );

STDMETHOD_( void, OMSetDepthStencilState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10DepthStencilState* pDepthStencilState,
    /* [annotation] */
    __in  UINT StencilRef );

STDMETHOD_( void, SOSetTargets )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_SO_BUFFER_SLOT_COUNT )  UINT NumBuffers,
    /* [annotation] */
    __in_ecount_opt( NumBuffers )  ID3D10Buffer* const* ppSOTargets,
    /* [annotation] */
    __in_ecount_opt( NumBuffers )  const UINT* pOffsets );

STDMETHOD_( void, DrawAuto )DECLARE_PARAMS(
    THIS );

STDMETHOD_( void, RSSetState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_opt  ID3D10RasterizerState* pRasterizerState );

STDMETHOD_( void, RSSetViewports )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )  UINT NumViewports,
    /* [annotation] */
    __in_ecount_opt( NumViewports )  const D3D10_VIEWPORT* pViewports );

STDMETHOD_( void, RSSetScissorRects )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )  UINT NumRects,
    /* [annotation] */
    __in_ecount_opt( NumRects )  const D3D10_RECT* pRects );

STDMETHOD_( void, CopySubresourceRegion )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10Resource* pDstResource,
    /* [annotation] */
    __in  UINT DstSubresource,
    /* [annotation] */
    __in  UINT DstX,
    /* [annotation] */
    __in  UINT DstY,
    /* [annotation] */
    __in  UINT DstZ,
    /* [annotation] */
    __in  ID3D10Resource* pSrcResource,
    /* [annotation] */
    __in  UINT SrcSubresource,
    /* [annotation] */
    __in_opt  const D3D10_BOX* pSrcBox );

STDMETHOD_( void, CopyResource )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10Resource* pDstResource,
    /* [annotation] */
    __in  ID3D10Resource* pSrcResource );

STDMETHOD_( void, UpdateSubresource )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10Resource* pDstResource,
    /* [annotation] */
    __in  UINT DstSubresource,
    /* [annotation] */
    __in_opt  const D3D10_BOX* pDstBox,
    /* [annotation] */
    __in  const void* pSrcData,
    /* [annotation] */
    __in  UINT SrcRowPitch,
    /* [annotation] */
    __in  UINT SrcDepthPitch );

STDMETHOD_( void, ClearRenderTargetView )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10RenderTargetView* pRenderTargetView,
    /* [annotation] */
    __in  const FLOAT ColorRGBA[ 4 ] );

STDMETHOD_( void, ClearDepthStencilView )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10DepthStencilView* pDepthStencilView,
    /* [annotation] */
    __in  UINT ClearFlags,
    /* [annotation] */
    __in  FLOAT Depth,
    /* [annotation] */
    __in  UINT8 Stencil );

STDMETHOD_( void, GenerateMips )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10ShaderResourceView* pShaderResourceView );

STDMETHOD_( void, ResolveSubresource )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10Resource* pDstResource,
    /* [annotation] */
    __in  UINT DstSubresource,
    /* [annotation] */
    __in  ID3D10Resource* pSrcResource,
    /* [annotation] */
    __in  UINT SrcSubresource,
    /* [annotation] */
    __in  DXGI_FORMAT Format );

STDMETHOD_( void, VSGetConstantBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __out_ecount( NumBuffers )  ID3D10Buffer** ppConstantBuffers );

STDMETHOD_( void, PSGetShaderResources )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
    /* [annotation] */
    __out_ecount( NumViews )  ID3D10ShaderResourceView** ppShaderResourceViews );

STDMETHOD_( void, PSGetShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out  ID3D10PixelShader** ppPixelShader );

STDMETHOD_( void, PSGetSamplers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
    /* [annotation] */
    __out_ecount( NumSamplers )  ID3D10SamplerState** ppSamplers );

STDMETHOD_( void, VSGetShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out  ID3D10VertexShader** ppVertexShader );

STDMETHOD_( void, PSGetConstantBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __out_ecount( NumBuffers )  ID3D10Buffer** ppConstantBuffers );

STDMETHOD_( void, IAGetInputLayout )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out  ID3D10InputLayout** ppInputLayout );

STDMETHOD_( void, IAGetVertexBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __out_ecount_opt( NumBuffers )  ID3D10Buffer** ppVertexBuffers,
    /* [annotation] */
    __out_ecount_opt( NumBuffers )  UINT* pStrides,
    /* [annotation] */
    __out_ecount_opt( NumBuffers )  UINT* pOffsets );

STDMETHOD_( void, IAGetIndexBuffer )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out_opt  ID3D10Buffer** pIndexBuffer,
    /* [annotation] */
    __out_opt  DXGI_FORMAT* Format,
    /* [annotation] */
    __out_opt  UINT* Offset );

STDMETHOD_( void, GSGetConstantBuffers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
    /* [annotation] */
    __out_ecount( NumBuffers )  ID3D10Buffer** ppConstantBuffers );

STDMETHOD_( void, GSGetShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out  ID3D10GeometryShader** ppGeometryShader );

STDMETHOD_( void, IAGetPrimitiveTopology )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out  D3D10_PRIMITIVE_TOPOLOGY* pTopology );

STDMETHOD_( void, VSGetShaderResources )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
    /* [annotation] */
    __out_ecount( NumViews )  ID3D10ShaderResourceView** ppShaderResourceViews );

STDMETHOD_( void, VSGetSamplers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
    /* [annotation] */
    __out_ecount( NumSamplers )  ID3D10SamplerState** ppSamplers );

STDMETHOD_( void, GetPredication )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out_opt  ID3D10Predicate** ppPredicate,
    /* [annotation] */
    __out_opt  BOOL* pPredicateValue );

STDMETHOD_( void, GSGetShaderResources )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
    /* [annotation] */
    __out_ecount( NumViews )  ID3D10ShaderResourceView** ppShaderResourceViews );

STDMETHOD_( void, GSGetSamplers )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
    /* [annotation] */
    __in_range( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
    /* [annotation] */
    __out_ecount( NumSamplers )  ID3D10SamplerState** ppSamplers );

STDMETHOD_( void, OMGetRenderTargets )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT )  UINT NumViews,
    /* [annotation] */
    __out_ecount_opt( NumViews )  ID3D10RenderTargetView** ppRenderTargetViews,
    /* [annotation] */
    __out_opt  ID3D10DepthStencilView** ppDepthStencilView );

STDMETHOD_( void, OMGetBlendState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out_opt  ID3D10BlendState** ppBlendState,
    /* [annotation] */
    __out_opt  FLOAT BlendFactor[ 4 ],
    /* [annotation] */
    __out_opt  UINT* pSampleMask );

STDMETHOD_( void, OMGetDepthStencilState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out_opt  ID3D10DepthStencilState** ppDepthStencilState,
    /* [annotation] */
    __out_opt  UINT* pStencilRef );

STDMETHOD_( void, SOGetTargets )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_range( 0, D3D10_SO_BUFFER_SLOT_COUNT )  UINT NumBuffers,
    /* [annotation] */
    __out_ecount_opt( NumBuffers )  ID3D10Buffer** ppSOTargets,
    /* [annotation] */
    __out_ecount_opt( NumBuffers )  UINT* pOffsets );

STDMETHOD_( void, RSGetState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out  ID3D10RasterizerState** ppRasterizerState );

STDMETHOD_( void, RSGetViewports )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __inout /*_range(0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )*/   UINT* NumViewports,
    /* [annotation] */
    __out_ecount_opt( *NumViewports )  D3D10_VIEWPORT* pViewports );

STDMETHOD_( void, RSGetScissorRects )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __inout /*_range(0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )*/   UINT* NumRects,
    /* [annotation] */
    __out_ecount_opt( *NumRects )  D3D10_RECT* pRects );

STDMETHOD( GetDeviceRemovedReason )DECLARE_PARAMS(
    THIS );

STDMETHOD( SetExceptionMode )DECLARE_PARAMS(
    THIS,
    UINT RaiseFlags );

STDMETHOD_( UINT, GetExceptionMode )DECLARE_PARAMS(
    THIS );

STDMETHOD( GetPrivateData )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  REFGUID guid,
    /* [annotation] */
    __inout  UINT* pDataSize,
    /* [annotation] */
    __out_bcount_opt( *pDataSize )  void* pData );

STDMETHOD( SetPrivateData )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  REFGUID guid,
    /* [annotation] */
    __in  UINT DataSize,
    /* [annotation] */
    __in_bcount_opt( DataSize )  const void* pData );

STDMETHOD( SetPrivateDataInterface )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  REFGUID guid,
    /* [annotation] */
    __in_opt  const IUnknown* pData );

STDMETHOD_( void, ClearState )DECLARE_PARAMS(
    THIS );

STDMETHOD_( void, Flush )DECLARE_PARAMS(
    THIS );

STDMETHOD( CreateBuffer )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_BUFFER_DESC* pDesc,
    /* [annotation] */
    __in_opt  const D3D10_SUBRESOURCE_DATA* pInitialData,
    /* [annotation] */
    __out_opt  ID3D10Buffer** ppBuffer );

STDMETHOD( CreateTexture1D )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_TEXTURE1D_DESC* pDesc,
    /* [annotation] */
    __in_xcount_opt( pDesc->MipLevels * pDesc->ArraySize )  const D3D10_SUBRESOURCE_DATA* pInitialData,
    /* [annotation] */
    __out  ID3D10Texture1D** ppTexture1D );

STDMETHOD( CreateTexture2D )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_TEXTURE2D_DESC* pDesc,
    /* [annotation] */
    __in_xcount_opt( pDesc->MipLevels * pDesc->ArraySize )  const D3D10_SUBRESOURCE_DATA* pInitialData,
    /* [annotation] */
    __out  ID3D10Texture2D** ppTexture2D );

STDMETHOD( CreateTexture3D )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_TEXTURE3D_DESC* pDesc,
    /* [annotation] */
    __in_xcount_opt( pDesc->MipLevels )  const D3D10_SUBRESOURCE_DATA* pInitialData,
    /* [annotation] */
    __out  ID3D10Texture3D** ppTexture3D );

STDMETHOD( CreateShaderResourceView )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10Resource* pResource,
    /* [annotation] */
    __in_opt  const D3D10_SHADER_RESOURCE_VIEW_DESC* pDesc,
    /* [annotation] */
    __out_opt  ID3D10ShaderResourceView** ppSRView );

STDMETHOD( CreateRenderTargetView )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10Resource* pResource,
    /* [annotation] */
    __in_opt  const D3D10_RENDER_TARGET_VIEW_DESC* pDesc,
    /* [annotation] */
    __out_opt  ID3D10RenderTargetView** ppRTView );

STDMETHOD( CreateDepthStencilView )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  ID3D10Resource* pResource,
    /* [annotation] */
    __in_opt  const D3D10_DEPTH_STENCIL_VIEW_DESC* pDesc,
    /* [annotation] */
    __out_opt  ID3D10DepthStencilView** ppDepthStencilView );

STDMETHOD( CreateInputLayout )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in_ecount( NumElements )  const D3D10_INPUT_ELEMENT_DESC* pInputElementDescs,
    /* [annotation] */
    __in_range( 0, D3D10_1_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT )  UINT NumElements,
    /* [annotation] */
    __in  const void* pShaderBytecodeWithInputSignature,
    /* [annotation] */
    __in  SIZE_T BytecodeLength,
    /* [annotation] */
    __out_opt  ID3D10InputLayout** ppInputLayout );

STDMETHOD( CreateVertexShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const void* pShaderBytecode,
    /* [annotation] */
    __in  SIZE_T BytecodeLength,
    /* [annotation] */
    __out_opt  ID3D10VertexShader** ppVertexShader );

STDMETHOD( CreateGeometryShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const void* pShaderBytecode,
    /* [annotation] */
    __in  SIZE_T BytecodeLength,
    /* [annotation] */
    __out_opt  ID3D10GeometryShader** ppGeometryShader );

STDMETHOD( CreateGeometryShaderWithStreamOutput )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const void* pShaderBytecode,
    /* [annotation] */
    __in  SIZE_T BytecodeLength,
    /* [annotation] */
    __in_ecount_opt( NumEntries )  const D3D10_SO_DECLARATION_ENTRY* pSODeclaration,
    /* [annotation] */
    __in_range( 0, D3D10_SO_SINGLE_BUFFER_COMPONENT_LIMIT )  UINT NumEntries,
    /* [annotation] */
    __in  UINT OutputStreamStride,
    /* [annotation] */
    __out_opt  ID3D10GeometryShader** ppGeometryShader );

STDMETHOD( CreatePixelShader )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const void* pShaderBytecode,
    /* [annotation] */
    __in  SIZE_T BytecodeLength,
    /* [annotation] */
    __out_opt  ID3D10PixelShader** ppPixelShader );

STDMETHOD( CreateBlendState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_BLEND_DESC* pBlendStateDesc,
    /* [annotation] */
    __out_opt  ID3D10BlendState** ppBlendState );

STDMETHOD( CreateDepthStencilState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_DEPTH_STENCIL_DESC* pDepthStencilDesc,
    /* [annotation] */
    __out_opt  ID3D10DepthStencilState** ppDepthStencilState );

STDMETHOD( CreateRasterizerState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_RASTERIZER_DESC* pRasterizerDesc,
    /* [annotation] */
    __out_opt  ID3D10RasterizerState** ppRasterizerState );

STDMETHOD( CreateSamplerState )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_SAMPLER_DESC* pSamplerDesc,
    /* [annotation] */
    __out_opt  ID3D10SamplerState** ppSamplerState );

STDMETHOD( CreateQuery )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_QUERY_DESC* pQueryDesc,
    /* [annotation] */
    __out_opt  ID3D10Query** ppQuery );

STDMETHOD( CreatePredicate )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_QUERY_DESC* pPredicateDesc,
    /* [annotation] */
    __out_opt  ID3D10Predicate** ppPredicate );

STDMETHOD( CreateCounter )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_COUNTER_DESC* pCounterDesc,
    /* [annotation] */
    __out_opt  ID3D10Counter** ppCounter );

STDMETHOD( CheckFormatSupport )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  DXGI_FORMAT Format,
    /* [annotation] */
    __out  UINT* pFormatSupport );

STDMETHOD( CheckMultisampleQualityLevels )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  DXGI_FORMAT Format,
    /* [annotation] */
    __in  UINT SampleCount,
    /* [annotation] */
    __out  UINT* pNumQualityLevels );

STDMETHOD_( void, CheckCounterInfo )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out  D3D10_COUNTER_INFO* pCounterInfo );

STDMETHOD( CheckCounter )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  const D3D10_COUNTER_DESC* pDesc,
    /* [annotation] */
    __out  D3D10_COUNTER_TYPE* pType,
    /* [annotation] */
    __out  UINT* pActiveCounters,
    /* [annotation] */
    __out_ecount_opt( *pNameLength )  LPSTR szName,
    /* [annotation] */
    __inout_opt  UINT* pNameLength,
    /* [annotation] */
    __out_ecount_opt( *pUnitsLength )  LPSTR szUnits,
    /* [annotation] */
    __inout_opt  UINT* pUnitsLength,
    /* [annotation] */
    __out_ecount_opt( *pDescriptionLength )  LPSTR szDescription,
    /* [annotation] */
    __inout_opt  UINT* pDescriptionLength );

STDMETHOD_( UINT, GetCreationFlags )DECLARE_PARAMS(
    THIS );

STDMETHOD( OpenSharedResource )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  HANDLE hResource,
    /* [annotation] */
    __in  REFIID ReturnedInterface,
    /* [annotation] */
    __out_opt  void** ppResource );

STDMETHOD_( void, SetTextFilterSize )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __in  UINT Width,
    /* [annotation] */
    __in  UINT Height );

STDMETHOD_( void, GetTextFilterSize )DECLARE_PARAMS(
    THIS,
    /* [annotation] */
    __out_opt  UINT* pWidth,
    /* [annotation] */
    __out_opt  UINT* pHeight );

// Create vtable offsets
#undef STDMETHOD
#define STDMETHOD(method) PPCAT(PPCAT(PPCAT(vt, INTERFACE),_), method),
#undef STDMETHOD_
#define STDMETHOD_(type,method) PPCAT(PPCAT(PPCAT(vt, INTERFACE),_), method),

enum PPCAT( vt, INTERFACE )
{
    //  from d3d10.h
    STDMETHOD( QueryInterface )
    STDMETHOD_( ULONG, AddRef )
    STDMETHOD_( ULONG, Release )
    STDMETHOD_( void, VSSetConstantBuffers )
    STDMETHOD_( void, PSSetShaderResources )
    STDMETHOD_( void, PSSetShader )
    STDMETHOD_( void, PSSetSamplers )
    STDMETHOD_( void, VSSetShader )
    STDMETHOD_( void, DrawIndexed )
    STDMETHOD_( void, Draw )
    STDMETHOD_( void, PSSetConstantBuffers )
    STDMETHOD_( void, IASetInputLayout )
    STDMETHOD_( void, IASetVertexBuffers )
    STDMETHOD_( void, IASetIndexBuffer )
    STDMETHOD_( void, DrawIndexedInstanced )
    STDMETHOD_( void, DrawInstanced )
    STDMETHOD_( void, GSSetConstantBuffers )
    STDMETHOD_( void, GSSetShader )
    STDMETHOD_( void, IASetPrimitiveTopology )
    STDMETHOD_( void, VSSetShaderResources )
    STDMETHOD_( void, VSSetSamplers )
    STDMETHOD_( void, SetPredication )
    STDMETHOD_( void, GSSetShaderResources )
    STDMETHOD_( void, GSSetSamplers )
    STDMETHOD_( void, OMSetRenderTargets )
    STDMETHOD_( void, OMSetBlendState )
    STDMETHOD_( void, OMSetDepthStencilState )
    STDMETHOD_( void, SOSetTargets )
    STDMETHOD_( void, DrawAuto )
    STDMETHOD_( void, RSSetState )
    STDMETHOD_( void, RSSetViewports )
    STDMETHOD_( void, RSSetScissorRects )
    STDMETHOD_( void, CopySubresourceRegion )
    STDMETHOD_( void, CopyResource )
    STDMETHOD_( void, UpdateSubresource )
    STDMETHOD_( void, ClearRenderTargetView )
    STDMETHOD_( void, ClearDepthStencilView )
    STDMETHOD_( void, GenerateMips )
    STDMETHOD_( void, ResolveSubresource )
    STDMETHOD_( void, VSGetConstantBuffers )
    STDMETHOD_( void, PSGetShaderResources )
    STDMETHOD_( void, PSGetShader )
    STDMETHOD_( void, PSGetSamplers )
    STDMETHOD_( void, VSGetShader )
    STDMETHOD_( void, PSGetConstantBuffers )
    STDMETHOD_( void, IAGetInputLayout )
    STDMETHOD_( void, IAGetVertexBuffers )
    STDMETHOD_( void, IAGetIndexBuffer )
    STDMETHOD_( void, GSGetConstantBuffers )
    STDMETHOD_( void, GSGetShader )
    STDMETHOD_( void, IAGetPrimitiveTopology )
    STDMETHOD_( void, VSGetShaderResources )
    STDMETHOD_( void, VSGetSamplers )
    STDMETHOD_( void, GetPredication )
    STDMETHOD_( void, GSGetShaderResources )
    STDMETHOD_( void, GSGetSamplers )
    STDMETHOD_( void, OMGetRenderTargets )
    STDMETHOD_( void, OMGetBlendState )
    STDMETHOD_( void, OMGetDepthStencilState )
    STDMETHOD_( void, SOGetTargets )
    STDMETHOD_( void, RSGetState )
    STDMETHOD_( void, RSGetViewports )
    STDMETHOD_( void, RSGetScissorRects )
    STDMETHOD( GetDeviceRemovedReason )
    STDMETHOD( SetExceptionMode )
    STDMETHOD_( UINT, GetExceptionMode )
    STDMETHOD( GetPrivateData )
    STDMETHOD( SetPrivateData )
    STDMETHOD( SetPrivateDataInterface )
    STDMETHOD_( void, ClearState )
    STDMETHOD_( void, Flush )
    STDMETHOD( CreateBuffer )
    STDMETHOD( CreateTexture1D )
    STDMETHOD( CreateTexture2D )
    STDMETHOD( CreateTexture3D )
    STDMETHOD( CreateShaderResourceView )
    STDMETHOD( CreateRenderTargetView )
    STDMETHOD( CreateDepthStencilView )
    STDMETHOD( CreateInputLayout )
    STDMETHOD( CreateVertexShader )
    STDMETHOD( CreateGeometryShader )
    STDMETHOD( CreateGeometryShaderWithStreamOutput )
    STDMETHOD( CreatePixelShader )
    STDMETHOD( CreateBlendState )
    STDMETHOD( CreateDepthStencilState )
    STDMETHOD( CreateRasterizerState )
    STDMETHOD( CreateSamplerState )
    STDMETHOD( CreateQuery )
    STDMETHOD( CreatePredicate )
    STDMETHOD( CreateCounter )
    STDMETHOD( CheckFormatSupport )
    STDMETHOD( CheckMultisampleQualityLevels )
    STDMETHOD_( void, CheckCounterInfo )
    STDMETHOD( CheckCounter )
    STDMETHOD_( UINT, GetCreationFlags )
    STDMETHOD( OpenSharedResource )
    STDMETHOD_( void, SetTextFilterSize )
    STDMETHOD_( void, GetTextFilterSize )
};