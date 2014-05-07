#ifndef _CEF_CRY_RENDER_TARGET_H_
#define _CEF_CRY_RENDER_TARGET_H_

#include "CRenderTarget.h"

namespace CEFPlugin
{
	class CCryRenderTarget : public CRenderTarget
	{
	public:
		CCryRenderTarget(int width, int height) : CRenderTarget(width, height), _texId(0) {};
		virtual ~CCryRenderTarget() {};

		virtual int GetTextureID();

		virtual bool IsInitialized() { return GetTextureID()>0; }

		virtual void RenderHUD();

	protected:
		int _texId;
	};
}

#endif
