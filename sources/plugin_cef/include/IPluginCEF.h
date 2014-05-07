/* CEF_Plugin - for licensing and copyright see license.txt */

#include <IPluginBase.h>

#pragma once

/**
* @brief CEF Plugin Namespace
*/
namespace CEFPlugin
{
    class CCEFSystem;

    /**
    * @brief plugin CEF concrete interface
    */
    struct IPluginCEF
    {
        /**
        * @brief Get Plugin base interface
        */
        virtual PluginManager::IPluginBase* GetBase() = 0;

        virtual CCEFSystem* GetSystem() = 0;
    };
};