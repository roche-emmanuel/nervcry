#include "StdAfx.h"
#include "CCryView.h"

#include "CCryDX11RenderTarget.h"

namespace CEFPlugin
{

CCryView::CCryView(int width, int height, std::string url): CCEFViewBase(width,height) {
  // select the render target to build based on the current renderer type:
  ERenderType rendererType = gEnv->pRenderer->GetRenderType();
  // CHECK( rendererType == eRT_DX11 || rendererType == eRT_DX9, "Currently only DX9 and DX11 renderers are supported!" );
  CHECK( rendererType == eRT_DX11, "Currently only DX11 renderer is supported!" );

  if(rendererType == eRT_DX11) {
    _renderTarget = new CCryDX11RenderTarget(_width,_height);
  }

  // Finalize the construction of the browser:
  CreateBrowser(url);
}

CCryView::~CCryView() 
{

}

} // namespace
