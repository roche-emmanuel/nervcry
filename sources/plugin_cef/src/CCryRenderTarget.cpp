#include "StdAfx.h"
#include "CCryRenderTarget.h"

namespace CEFPlugin
{

int CCryRenderTarget::GetTextureID() {
  //CHECK_RET(_texId>0,_texId,"Invalid render target texture ID: " << _texId);
  return _texId;
}

void CCryRenderTarget::RenderHUD()
{
	CHECK(GetTextureID()>0,"Invalid texture ID in RenderHUD.")
	gEnv->pRenderer->Draw2dImage(0.0f,0.0f,800, 600,GetTextureID(),0.0,1.0,1.0,0.0);
}

}
