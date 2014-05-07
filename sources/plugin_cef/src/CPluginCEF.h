/* CEF_Plugin - for licensing and copyright see license.txt */

#pragma once

#include <IPluginBase.h>
#include <Game.h>

#include <IPluginManager.h>
#include <CPluginBase.hpp>

#include <IPluginCEF.h>
#include <IPluginD3D.h>

#define PLUGIN_NAME "CEF"
#define PLUGIN_CONSOLE_PREFIX "[" PLUGIN_NAME " " PLUGIN_TEXT "] " //!< Prefix for Logentries by this plugin

namespace CEFPlugin
{
    /**
    * @brief Provides information and manages the resources of this plugin.
    */
    class CPluginCEF :
        public PluginManager::CPluginBase,
        public IPluginCEF
    {
        public:
            CPluginCEF();
            ~CPluginCEF();

            // IPluginBase
            bool Release( bool bForce = false );

            int GetInitializationMode() const
            {
                return int( PluginManager::IM_Default );
            };

            bool Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager, const char* sPluginDirectory );

            bool RegisterTypes( int nFactoryType, bool bUnregister );

            const char* GetVersion() const
            {
                return "1.0.0.0";
            };

            const char* GetName() const
            {
                return PLUGIN_NAME;
            };

            const char* GetCategory() const
            {
                return "Visual";
            };

            const char* ListAuthors() const
            {
                return "Emmanuel ROCHE";
            };

            const char* ListCVars() const;

            const char* GetStatus() const;

            const char* GetCurrentConcreteInterfaceVersion() const
            {
                return "1.0";
            };

            void* GetConcreteInterface( const char* sInterfaceVersion )
            {
                return static_cast < IPluginCEF* >( this );
            };

            // IPluginCEF
            IPluginBase* GetBase()
            {
                return static_cast<IPluginBase*>( this );
            };

            bool InitDependencies();
            bool CheckDependencies() const;
            
            // TODO: Add your concrete interface implementation
            virtual CCEFSystem* GetSystem();
    };

    extern CPluginCEF* gPlugin;
    extern D3DPlugin::IPluginD3D* gD3DSystem;
    extern void* gD3DDevice;
}

/**
* @brief This function is required to use the Autoregister Flownode without modification.
* Include the file "CPluginCEF.h" in front of flownode.
*/
inline void GameWarning( const char* sFormat, ... ) PRINTF_PARAMS( 1, 2 );
inline void GameWarning( const char* sFormat, ... )
{
    va_list ArgList;
    va_start( ArgList, sFormat );
    CEFPlugin::gPlugin->LogV( ILog::eWarningAlways, sFormat, ArgList );
    va_end( ArgList );
};
