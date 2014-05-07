#ifndef _CEF_BROWSER_CLIENT_H_
#define _CEF_BROWSER_CLIENT_H_

#include <cef_client.h>

#include "CRenderHandler.h"
#include "CRenderTarget.h"

namespace CEFPlugin
{
    /**
    This class is a minimal implementation of a CefClient, to provide a Render Handler to the CEF engine
    so that paint event can be retrieved for a given browser object.
    */
    class CBrowserClient : public CefClient
    {
    public:
        CBrowserClient();
        ~CBrowserClient();

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() {
        return _renderHandler.get();
    }

    void SetRenderTarget(CRenderTarget* target);

    protected:
        CefRefPtr<CRenderHandler> _renderHandler;

    IMPLEMENT_REFCOUNTING(CBrowserClient);
    };
}

#endif
