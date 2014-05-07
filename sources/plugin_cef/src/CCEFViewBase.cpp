#include "StdAfx.h"
#include "CCEFViewBase.h"

namespace CEFPlugin
{

CCEFViewBase::CCEFViewBase(int width, int height): _width(width), _height(height), _mode(VIEWMODE_HUD) {
  logDEBUG("Creating new CEFViewBase.");	

  // We create the browser client interface:
	_browserClient = new CBrowserClient();
}

CCEFViewBase::~CCEFViewBase() {
    logDEBUG("Deleting CEFViewBase.");
    Uninitialize();
}

void CCEFViewBase::CreateBrowser(std::string url) {
  
  logDEBUG("Assigning render target...");
  CHECK(_renderTarget.get(),"Invalid render target.");
  _browserClient->SetRenderTarget(_renderTarget.get());

  // Create the browser window:
  CefWindowInfo window_info;
  CefBrowserSettings browserSettings;

  browserSettings.file_access_from_file_urls = STATE_ENABLED;
  browserSettings.universal_access_from_file_urls = STATE_ENABLED;

  // in linux set a gtk widget, in windows a hwnd. If not available set nullptr - may cause some render errors, in context-menu and plugins.
  window_info.SetAsWindowless(nullptr,true); // true for transparent.

  logDEBUG("Creating Browser with url=" << url);
  _browser = CefBrowserHost::CreateBrowserSync(window_info, _browserClient.get(), url, browserSettings, nullptr);
  CHECK(_browser.get(),"Invalid browser object.")
  logDEBUG("Browser created.");

  // inject user-input by calling:
  // browser->GetHost()->SendKeyEvent(...);
  // browser->GetHost()->SendMouseMoveEvent(...);
  // browser->GetHost()->SendMouseClickEvent(...);
  // browser->GetHost()->SendMouseWheelEvent(...);  
}

void CCEFViewBase::Initialize()
{
  CHECK(_renderTarget.get(),"Invalid render target.");
  logDEBUG("Initializing ViewBase.")
  _renderTarget->Initialize();
}

void CCEFViewBase::Uninitialize()
{
  CHECK(_renderTarget.get(),"Invalid render target.");
  logDEBUG("Uninitializing ViewBase.")
  _renderTarget->Uninitialize();
}

bool CCEFViewBase::IsInitialized() {
  CHECK_RET(_renderTarget.get(),false,"Invalid render target.");
  return _renderTarget->IsInitialized();
}

void CCEFViewBase::RenderHUD() {
  CHECK(_mode==VIEWMODE_HUD,"Invalid view mode");
  CHECK(_renderTarget.get(),"Invalid render target.");
  _renderTarget->RenderHUD();
}

}
