#ifndef _CEF_CRYDX11_RENDER_TARGET_H_
#define _CEF_CRYDX11_RENDER_TARGET_H_

#include "CCryRenderTarget.h"
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "ComPtr.h"

namespace CEFPlugin
{
	class CCryDX11RenderTarget : public CCryRenderTarget
	{
	public:
		CCryDX11RenderTarget(int width, int height);
		~CCryDX11RenderTarget();

		virtual void PaintRects(const CefRenderHandler::RectList &dirtyRects, const void *buffer);
		
		void PaintRect(int srcX, int srcY, int srcWidth, int srcHeight, const void* srcBuffer, void* destBuffer, int pitch);

		virtual void Initialize();
		virtual void Uninitialize();

	protected:
		ComPtr<ID3D11Texture2D> _texture;
	};
}

#endif
