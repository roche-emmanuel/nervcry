#ifndef _CEF_RENDER_HANDLER_H_
#define _CEF_RENDER_HANDLER_H_

#include <cef_render_handler.h>
#include "CRenderTarget.h"

namespace CEFPlugin
{
	/**
	This class is a minimal implementation of a CefClient, to provide a Render Handler to the CEF engine
	so that paint event can be retrieved for a given browser object.
	*/
	class CRenderHandler : public CefRenderHandler
	{
	public:
		CRenderHandler();
		~CRenderHandler();

		void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height);

		bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);

		void SetRenderTarget(CRenderTarget* target);
		
	protected:
		CefRefPtr<CRenderTarget> _renderTarget;

	IMPLEMENT_REFCOUNTING(CRenderHandler);
	};
}

#endif
