#include "StdAfx.h"
#include "CRenderTarget.h"

namespace CEFPlugin
{

CRenderTarget::CRenderTarget(int width, int height): _width(width), _height(height) {
  logDEBUG("Creating new CRenderTarget.");
}

CRenderTarget::~CRenderTarget() {
  logDEBUG("Deleting CRenderTarget.");
}

}
