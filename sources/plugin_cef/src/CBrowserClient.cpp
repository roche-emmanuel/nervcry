#include "StdAfx.h"
#include "CBrowserClient.h"

namespace CEFPlugin
{

CBrowserClient::CBrowserClient() {
    logDEBUG("Creating new CBrowserClient.");

    // Here we build a new render handler object that should be assigned in this instance:
    _renderHandler = new CRenderHandler();
}

CBrowserClient::~CBrowserClient() {
    logDEBUG("Deleting CBrowserClient.");
}

void CBrowserClient::SetRenderTarget(CRenderTarget* target) {
	_renderHandler->SetRenderTarget(target);
}


}
