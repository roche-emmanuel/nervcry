#pragma once
#include <IPluginD3D.h>
#include <IGameFramework.h>
#include <CCEFViewBase.h>

namespace CEFPlugin
{
    class CCEFSystem : public D3DPlugin::ID3DEventListener, public IGameFrameworkListener
    {
    public:
        typedef std::vector< CefRefPtr<CCEFViewBase> > ViewList;

    public:
        CCEFSystem( void );
        ~CCEFSystem( void );

        // ID3DListener methods
        virtual void OnPrePresent() override;
        virtual void OnPostPresent()  override;
        virtual void OnPreReset() override;
        virtual void OnPostReset() override;
        virtual void OnPostBeginScene() override;

        // IGameFramework needed implementation:
        virtual void OnPreRender() override;

        // IGameFramework NO OP implementations:
        virtual void OnPostUpdate( float fDeltaTime ) override;
        virtual void OnSaveGame( ISaveGame* pSaveGame ) override;
        virtual void OnLoadGame( ILoadGame* pLoadGame ) override;
        virtual void OnLevelEnd( const char* nextLevel ) override;
        virtual void OnActionEvent( const SActionEvent& event ) override;

        CCEFViewBase* CreateView(int width, int height, std::string url = "http://www.google.fr");
        void DestroyView(CCEFViewBase* view);

    protected:
        ViewList _views;
    };
}
