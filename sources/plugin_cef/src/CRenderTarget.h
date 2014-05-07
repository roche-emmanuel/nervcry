#ifndef _CEF_RENDER_TARGET_H_
#define _CEF_RENDER_TARGET_H_

#include <cef_base.h>
#include <cef_render_handler.h>

namespace CEFPlugin
{
	class CRenderTarget : public CefBase
	{
	public:
		CRenderTarget(int width, int height);
		virtual ~CRenderTarget();

		// Main method used to draw some content on a target texture. This must be re-implemented:
		virtual void PaintRects(const CefRenderHandler::RectList &dirtyRects, const void *buffer) = 0;

		// Retrieve the dimensions of the target:
		virtual int GetWidth() { return _width; }
		virtual int GetHeight() { return _height; }

		virtual void Initialize() = 0;
		virtual void Uninitialize() = 0;
		virtual bool IsInitialized() = 0;
		
		virtual void RenderHUD() = 0;
		
	protected:
		int _width;
		int _height;

	IMPLEMENT_REFCOUNTING(CRenderTarget);
	};
}

#endif
