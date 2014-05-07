#include "StdAfx.h"
#include "CRenderHandler.h"

namespace CEFPlugin
{

CRenderHandler::CRenderHandler() {
  logDEBUG("Creating new CRenderHandler.");
}

CRenderHandler::~CRenderHandler() {
  logDEBUG("Deleting CRenderHandler.");
}

bool CRenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
	CHECK_RET(_renderTarget.get(),false,"Invalid render target object.")
	logDEBUG("Retrieving View rect of size " << _renderTarget->GetWidth()  << "x" << _renderTarget->GetHeight());
	rect = CefRect(0, 0, _renderTarget->GetWidth(), _renderTarget->GetHeight());
	return true;	
}

void CRenderHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) {
	logDEBUG("Calling OnPaint.");
	CHECK(_renderTarget.get(),"Invalid render target object.")
	CHECK(width==_renderTarget->GetWidth(),"Buffer width doesn't match render target: " << width << "!=" << _renderTarget->GetWidth());
	CHECK(width==_renderTarget->GetHeight(),"Buffer height doesn't match render target: " << height << "!=" << _renderTarget->GetHeight());

	if(dirtyRects.empty()) {
		logWARN("No dirty rect to paint!");
		return;
	}

	switch(type) {
	case PET_POPUP:
		logWARN("In OnPaint for PET_POPUP with " << dirtyRects.size() << " dirty rects.");
		return;
	case PET_VIEW:
		return _renderTarget->PaintRects(dirtyRects, buffer);
	default:
		THROW("Invalid PaintElementType: " << type);
	}
}

void CRenderHandler::SetRenderTarget(CRenderTarget* target) {
	CHECK(target,"Invalid RenderTarget object.");
	CHECK(_renderTarget.get()==NULL,"Reassigning render target ?")
	_renderTarget = target;
}

}
