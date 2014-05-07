#ifndef _CEF_VIEW_BASE_H_
#define _CEF_VIEW_BASE_H_

#include "CBrowserClient.h"
#include "CRenderTarget.h"
#include <cef_base.h>

namespace CEFPlugin
{
  /**
  This class is used as a base class for all "Views" based on a CEF browser object.
  It is responsible for encapsulating/controlling the browser inputs and javascript commands
  as well as rendering. 
  */
  class CCEFViewBase : public CefBase
  {
  public:
    enum ViewMode {
      VIEWMODE_HUD,
      VIEWMODE_OBJECT
    };

  public:
    CCEFViewBase(int width, int height);
    virtual ~CCEFViewBase();
    
    virtual bool IsInitialized();
    virtual void Initialize();
    virtual void Uninitialize();

    virtual void SetViewMode(int mode) { _mode = mode; }
    virtual int GetViewMode() { return _mode; }

    virtual bool IsHUDView() { return _mode==VIEWMODE_HUD; }
    
    virtual void RenderHUD();

  protected:
    void CreateBrowser(std::string url = "http://www.google.fr");
    
    int _width;
    int _height;
    int _mode;

    CefRefPtr<CefBrowser> _browser;
    CefRefPtr<CBrowserClient> _browserClient;
    CefRefPtr<CRenderTarget> _renderTarget;

  IMPLEMENT_REFCOUNTING(CCEFViewBase);    
  };
}

#endif
