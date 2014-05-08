/* D3D_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>

#include <CPluginCEF.h>
#include <IPluginManager.h>
#include "CCEFSystem.h"
#include "CCryView.h"
#include <Nodes/G2FlowBaseNode.h>

namespace CEFPlugin
{
    class CFlowCEFHUDView :
        public CFlowBaseNode<eNCT_Instanced>
    {
        enum EInputPorts
        {
            //Create the view and start updating the texture
            EIP_START = 0,
            //Delete the view and release the texture
            EIP_RELEASE,
            EIP_WIDTH,
            EIP_HEIGHT,
            EIP_TOURL,                        
        };

        enum EOutputPorts
        {
            EOP_STARTED = 0,
            EOP_RELEASED,
        };

    public:
        virtual void GetMemoryUsage( ICrySizer* s ) const
        {
            s->Add( *this );
        }

        virtual IFlowNodePtr Clone( SActivationInfo* pActInfo )
        {
            return new CFlowCEFHUDView( pActInfo );
        }

        CFlowCEFHUDView( SActivationInfo* pActInfo )
        {
        }

        ~CFlowCEFHUDView()
        {
            if (_view.get() )
            {
                _sys->DestroyView( _view.get() );
                _view = NULL;
            }
        }

        virtual void GetConfiguration( SFlowNodeConfig& config )
        {
            static const SInputPortConfig inputs[] =
            {
                InputPortConfig_Void( "Start", _HELP( "Create and begin updating the view." ) ),
                InputPortConfig_Void( "Release", _HELP( "Shutdown and release the view" ) ),
                InputPortConfig<int>( "Width", -1, _HELP( "Width of the view" ) ),
                InputPortConfig<int>( "Height", -1, _HELP( "Height of the view" ) ),   
                InputPortConfig<string>( "URL", "http://www.google.fr", _HELP( "Go to a URL" ), NULL, NULL ),             
                InputPortConfig_Null(),
            };

            static const SOutputPortConfig outputs[] =
            {
                OutputPortConfig<bool>( "Started", _HELP( "The view was created and is working properly." ) ),
                OutputPortConfig<bool>( "Released", _HELP( "The view was shut down and released." ) ),
                OutputPortConfig_Null(),
            };

            config.pInputPorts = inputs;
            config.pOutputPorts = outputs;
            config.sDescription = _HELP( "Instance of a CEF View" );

            config.SetCategory( EFLN_APPROVED );
        }

        virtual void ProcessEvent( EFlowEvent evt, SActivationInfo* pActInfo )
        {

            // Note: do not try to cache the value of _plugin here as this will lead
            // to unexpected crashes.
            _plugin = PluginManager::safeGetPluginConcreteInterface<IPluginCEF*>( PLUGIN_NAME );
            CHECK(_plugin,"Invalid CEF plugin concrete interface in Flownode.");                    
            _sys = _plugin->GetSystem();
            CHECK(_sys,"Invalid CEF system in Flownode.");                    


            if(evt != eFE_Activate) {
                return;
            }

            if ( IsPortActive( pActInfo, EIP_START ) && !_view.get())
            {
                // Retrieve the current input values:
                int ww = GetPortInt( pActInfo, EIP_WIDTH );
                int hh = GetPortInt( pActInfo, EIP_HEIGHT );

                if(ww=-1) {
                    ww = gEnv->pRenderer->GetWidth();
                    logDEBUG("Using renderer width: " << ww);
                }
                if(hh==-1) {
                    hh = gEnv->pRenderer->GetHeight();       
                    logDEBUG("Using renderer height: " << hh);
                }
                  
                std::string url = GetPortString( pActInfo, EIP_TOURL );

                _view = _sys->CreateView(ww,hh,url);
                logDEBUG("Flownode view created.");
                ActivateOutput<bool>( pActInfo, EOP_STARTED, true);
            }

            if(!_view.get()) {
                return; // nothing else can be done without a view instance.
            }

            if ( IsPortActive( pActInfo, EIP_RELEASE ) )
            {
                _sys->DestroyView( _view.get() );
                _view = NULL;
            }

            // if ( IsPortActive( pActInfo, EIP_TOURL ) )
            // {
            //     std::string url = GetPortString( pActInfo, EIP_TOURL );

            //     if ( view && url.length() != 0 )
            //     {
            //         view->GetView()->LoadURL( WebURL( WSLit( url.c_str() ) ) );
            //     }
            // }
        }

    private:
        IPluginCEF* _plugin;
        CCEFSystem* _sys;
        CefRefPtr<CCEFViewBase> _view;
    };
}

REGISTER_FLOW_NODE_EX( "Nerv:CEF:HUDView",  CEFPlugin::CFlowCEFHUDView, CFlowCEFHUDView );