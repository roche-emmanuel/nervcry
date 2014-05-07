#include "StdAfx.h"
#include "CCryDX11RenderTarget.h"
#include <ITexture.h>

#include <CPluginCEF.h>
#include <boost/cstdint.hpp>

// #define USE_DX11_MAPPING

namespace CEFPlugin
{

CCryDX11RenderTarget::CCryDX11RenderTarget(int width, int height) : CCryRenderTarget(width, height) {
	
}

CCryDX11RenderTarget::~CCryDX11RenderTarget() {

}

void CCryDX11RenderTarget::PaintRects(const CefRenderHandler::RectList &dirtyRects, const void *buffer) {
	CHECK(_texture,"Invalid DX11 texture.")

  ID3D11Device* pDevice = static_cast<ID3D11Device*>( gD3DDevice );
	ID3D11DeviceContext* pContext = NULL;
	pDevice->GetImmediateContext( &pContext );

#ifdef USE_DX11_MAPPING
	// When using Mapped texture we have to copy the complete data:

	D3D11_MAPPED_SUBRESOURCE mapped;
	CHECK_RESULT(pContext->Map( _texture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped ),"Cannot map DX11 texture.");

	char* pSrc = (char*)buffer;
	char* pDest = static_cast<char*>( mapped.pData );

  int offsetSrc = 0;
  int offsetDst = 0;
  int rowOffset = mapped.RowPitch % _width;

  for ( int row = 0; row < _height; ++row )
  {
    for ( int col = 0; col < _width; ++col )
    {
        pDest[offsetDst] = pSrc[offsetSrc + 2];
        pDest[offsetDst + 1] = pSrc[offsetSrc + 1];
        pDest[offsetDst + 2] = pSrc[offsetSrc];
        pDest[offsetDst + 3] = pSrc[offsetSrc + 3];
        offsetSrc += 4;
        offsetDst += 4;
    }

    offsetDst += rowOffset;	
  }

	pContext->Unmap( _texture.Get(), 0 );
#else
	D3D11_BOX box;
	unsigned char* tmpBuffer;

  for (CefRenderHandler::RectList::const_iterator it = dirtyRects.begin(); it!= dirtyRects.end(); ++it) {
    const CefRect& rect = *it;

    box.left = rect.x;
    box.right = rect.x+rect.width;
    box.top = rect.y;
    box.bottom = rect.y+rect.height;
    box.front=0;
    box.back=1;

    tmpBuffer = new unsigned char[rect.width*rect.height*4];
    unsigned char* dest = tmpBuffer;
    unsigned char* src = (unsigned char*)buffer;
    src += rect.y*_width*4 + rect.x*4;
    int srcRowOffset = (_width - rect.width)*4;

    for(int r=0;r<rect.height;++r) {
    	for(int c=0;c<rect.width;++c) {
    		*dest++ = src[2];
    		*dest++ = src[1];
    		*dest++ = src[0];
    		*dest++ = src[3];
    		src+=4;
    	}
    	src += srcRowOffset;
    }

    logDEBUG("Calling Update Subresource with rect x="<<rect.x<<", y="<<rect.y<<", srcW="<<rect.width<<", srcH="<<rect.height);
		pContext->UpdateSubresource(_texture.Get(), 0, &box, (void*)tmpBuffer,rect.width*4,0);

		delete tmpBuffer;

    // Paint a single rect on the mapped destination:
    // note that buffer is |width|*|height|*4 bytes
    // in size and represents a BGRA image with an upper-left origin.
    //PaintRect(rect.x, rect.y, rect.width, rect.height, buffer, mapped.pData, mapped.RowPitch);
  }
#endif

}

void CCryDX11RenderTarget::PaintRect(int srcX, int srcY, int srcWidth, int srcHeight, const void* srcBuffer, void* destBuffer, int pitch) {
	logDEBUG("Should update rect x="<<srcX<<", y="<<srcY<<", srcW="<<srcWidth<<", srcH="<<srcHeight);

	// Prepare RGBA buffer:

	// upload buffer with UpdateSubresource:
}

void CCryDX11RenderTarget::Initialize() {
	if(_texId>0) {
		CHECK(_texture.Get(),"Invalid DX11 texture object.");
		return;
	}

	logDEBUG("Creating DX11 texture of size " << _width << "x" << _height);
	void* pD3DTextureDst = NULL;
#ifdef USE_DX11_MAPPING
  ITexture* pCryTex = gD3DSystem->CreateTexture(&pD3DTextureDst,_width,_height,1,eTF_A8R8G8B8,FT_USAGE_DYNAMIC);
#else
  ITexture* pCryTex = gD3DSystem->CreateTexture(&pD3DTextureDst,_width,_height,1,eTF_A8R8G8B8,FT_NOMIPS);
 #endif
  // ITexture* pCryTex = gD3DSystem->CreateTexture(&pD3DTextureDst,_width,_height,1,eTF_A8R8G8B8,0);
  CHECK(pCryTex,"Invalid CryEngine texture.");
  CHECK(pD3DTextureDst,"Invalid DX11 texture object.");
  _texture = ComPtr<ID3D11Texture2D>(static_cast<ID3D11Texture2D*>(pD3DTextureDst));
 	_texId = pCryTex->GetTextureID();
 	CHECK(_texId>0,"Invalid texture ID generated: " << _texId);
}

void CCryDX11RenderTarget::Uninitialize() {
	_texture.SafeRelease();
	_texId = 0;
}

}
