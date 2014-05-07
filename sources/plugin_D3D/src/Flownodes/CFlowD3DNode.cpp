/* D3D_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>

#include <CPluginD3D.h>
#include <IPluginManager.h>
#include <Nodes/G2FlowBaseNode.h>

#include <d3d11.h>

namespace D3DPlugin
{
    class CFlowD3DNode :
        public CFlowBaseNode<eNCT_Singleton>
    {
            enum EInputPorts
            {
                EIP_GET = 0,
            };

            enum EOutputPorts
            {
                EOP_HOOKED = 0,
                EOP_RENDERER,
                EOP_FEATURELEVEL,
                EOP_GPU,
            };

        public:
            virtual void GetMemoryUsage( ICrySizer* s ) const
            {
                s->Add( *this );
            }

            CFlowD3DNode( SActivationInfo* pActInfo )
            {

            }

            virtual void GetConfiguration( SFlowNodeConfig& config )
            {
                static const SInputPortConfig inputs[] =
                {
                    InputPortConfig_Void( "Get", _HELP( "Get" ) ),
                    InputPortConfig_Null(),
                };

                static const SOutputPortConfig outputs[] =
                {
                    OutputPortConfig<bool>( "Hooked", _HELP( "D3D was hooked and D3D plugin is fully functional" ) ),
                    OutputPortConfig<string>( "Renderer", _HELP( "CryEngine Renderer in use" ) ),
                    OutputPortConfig<string>( "FeatureLevel", _HELP( "FeatureLevel in use" ) ),
                    OutputPortConfig<string>( "GPU", _HELP( "GPU that is in use" ) ),
                    OutputPortConfig_Null(),
                };

                config.pInputPorts = inputs;
                config.pOutputPorts = outputs;
                config.sDescription = _HELP( " D3D Info" );

                config.SetCategory( EFLN_APPROVED );
            }

            virtual void ProcessEvent( EFlowEvent evt, SActivationInfo* pActInfo )
            {
                switch ( evt )
                {
                    case eFE_Activate:

                        if ( IsPortActive( pActInfo, EIP_GET ) )
                        {
                            // This plug in is a bit special since the concrete interface is inside of the dx subsystem instead of the gPlugin pointer
                            IPluginD3D* pD3DPlugin = PluginManager::safeGetPluginConcreteInterface<IPluginD3D*>( PLUGIN_NAME );

                            string sRenderer = "N/A";
                            string sFeatureLevel = "N/A";
                            string sGPUName = "N/A";
                            bool bHooked = false;

                            if ( pD3DPlugin )
                            {
                                bHooked = pD3DPlugin->GetDevice();
                                sGPUName = pD3DPlugin->GetGPUName();

                                switch ( pD3DPlugin->GetType() )
                                {
                                    case D3D_DX9:
                                        sRenderer = "DX9";
                                        break;

                                    case D3D_DX10:
                                        sRenderer = "DX10";
                                        break;

                                    case D3D_DX11:
                                        sRenderer = "DX11";
                                        break;
                                }

                                switch ( pD3DPlugin->GetFeatureLevel() )
                                {
                                    case D3D_FEATURE_LEVEL_9_1:
                                        sFeatureLevel = "9.1";
                                        break;

                                    case D3D_FEATURE_LEVEL_9_2:
                                        sFeatureLevel = "9.2";
                                        break;

                                    case D3D_FEATURE_LEVEL_9_3:
                                        sFeatureLevel = "9.3";
                                        break;

                                    case D3D_FEATURE_LEVEL_10_0:
                                        sFeatureLevel = "10.0";
                                        break;

                                    case D3D_FEATURE_LEVEL_10_1:
                                        sFeatureLevel = "10.1";
                                        break;

                                    case D3D_FEATURE_LEVEL_11_0:
                                        sFeatureLevel = "11.0";
                                        break;
                                }
                            }

                            ActivateOutput<bool>( pActInfo, EOP_HOOKED, bHooked );
                            ActivateOutput<string>( pActInfo, EOP_RENDERER, sRenderer );
                            ActivateOutput<string>( pActInfo, EOP_FEATURELEVEL, sFeatureLevel );
                            ActivateOutput<string>( pActInfo, EOP_GPU, sGPUName );
                        }

                        break;
                }
            }
    };
}

REGISTER_FLOW_NODE_EX( "D3D_Plugin:Info",  D3DPlugin::CFlowD3DNode, CFlowD3DNode );
