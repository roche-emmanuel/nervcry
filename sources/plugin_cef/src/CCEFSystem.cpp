#include "StdAfx.h"
#include "CCEFSystem.h"

#include <cef_app.h>
#include "CCryView.h"

namespace CEFPlugin
{
// CEF Render to texture implementation taken from:
// http://www.ogre3d.org/forums/viewtopic.php?f=11&t=79079

CCEFSystem::CCEFSystem( void )
{
    CHECK(gD3DSystem,"D3D not initialized when initing CEF Plugin.");
    gD3DSystem->RegisterListener( this );

    IGameFramework* pGameFramework = gEnv->pGame->GetIGameFramework();
    pGameFramework->RegisterListener( this, "CCEFSystem", FRAMEWORKLISTENERPRIORITY_HUD );
    // pGameFramework->RegisterListener( this, "CCEFSystem", eFLPriority_Default );


    // Perform initialization of the CEF engine.
    CefSettings settings;

    // checkout detailed settings options http://magpcss.org/ceforum/apidocs/projects/%28default%29/_cef_settings_t.html
    // nearly all the settings can be set via args too.
    settings.multi_threaded_message_loop = false;
    CefString(&settings.browser_subprocess_path).FromASCII("cef_process.exe");
    settings.ignore_certificate_errors = 1;
    settings.windowless_rendering_enabled = 1;
    settings.remote_debugging_port = 8080;
    settings.no_sandbox = 1;
    // CefString(&settings.cache_path).FromASCII("");
    // CefString(&settings.log_file).FromASCII("");
    // settings.log_severity = LOGSEVERITY_DEFAULT;
    // CefString(&settings.resources_dir_path).FromASCII("");
    // CefString(&settings.locales_dir_path).FromASCII("");


    HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);
    CefMainArgs args(hInst);

    // CefInitialize creates a sub-proccess and executes the same executeable, as calling CefInitialize, if not set different in settings.browser_subprocess_path
    // if you create an extra program just for the childproccess you only have to call CefExecuteProcess(...) in it.
    CHECK(CefInitialize(args, settings, nullptr, NULL),"Cannot initialize CEF.");
}

CCEFSystem::~CCEFSystem( void )
{
    CHECK(gD3DSystem,"D3D not initialized when stopping CEF Plugin.");
    gD3DSystem->UnregisterListener( this );

    // Remove all the views:
    _views.clear();

    CefShutdown();
    logDEBUG("Unloaded CEF system.");
}

void CCEFSystem::OnPostUpdate( float fDeltaTime )
{
    //Check if some views should be initialized:
    for(ViewList::iterator it = _views.begin(); it != _views.end(); ++it) {
        // logDEBUG("Checking if view is initialized.");

        if(!((*it)->IsInitialized())) {
            logDEBUG("Initializing View...");
            (*it)->Initialize();
            logDEBUG("View initialized.");
        }
        // logDEBUG("View already initialized.");
    }

    // logDEBUG("Calling CEF DoMessageLoopWork..." );
    CefDoMessageLoopWork();
    // logDEBUG("CEF DoMessageLoopWork done." );       

    // Render the HUD views:
    for(ViewList::iterator it = _views.begin(); it != _views.end(); ++it) {
        if((*it)->IsHUDView()) {
            // logDEBUG("Rendering HUD view");
            (*it)->RenderHUD();
            // logDEBUG("HUD View Rendered.");
        }
    }
}

void CCEFSystem::OnPreRender()
{
 
}

CCEFViewBase* CCEFSystem::CreateView(int width, int height, std::string url)
{
    // logDEBUG("Adding view to CEF system.");
    CCEFViewBase* view = new CCryView(width,height,url);
    _views.push_back(view);
    // logDEBUG("View added to CEF system. Ptr="<<(const void*)view);
    return view;
}

void CCEFSystem::DestroyView(CCEFViewBase* view)
{
    CHECK(view,"Invalid view object.")  
    for(ViewList::iterator it = _views.begin(); it != _views.end(); ++it) {
        if(it->get() == view) {
            _views.erase(it);
            return;
        }
    }
}


void CCEFSystem::OnSaveGame( ISaveGame* pSaveGame ) 
{
}

void CCEFSystem::OnLoadGame( ILoadGame* pLoadGame )
{
}

void CCEFSystem::OnLevelEnd( const char* nextLevel )
{
}

void CCEFSystem::OnActionEvent( const SActionEvent& event )
{
}

void CCEFSystem::OnPrePresent()
{
}

void CCEFSystem::OnPostPresent() 
{
}

void CCEFSystem::OnPreReset()
{
}

void CCEFSystem::OnPostReset()
{
}

void CCEFSystem::OnPostBeginScene()
{
}


}
