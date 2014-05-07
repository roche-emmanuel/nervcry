////////////////////////////////////////////////////////////////////////////
//
//  Crytek Engine Source File.
//  Copyright (C), Crytek Studios, 2001-2011.
// -------------------------------------------------------------------------
//  File name:   UISettings.cpp
//  Version:     v1.00
//  Created:     10/8/2011 by Paul Reindell.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "UISettings.h"
#include "UIManager.h"

#include <ILevelSystem.h>

////////////////////////////////////////////////////////////////////////////
CUISettings::CUISettings()
	: m_pUIEvents(NULL)
	, m_pUIFunctions(NULL)
	, m_currResId(0)
{
}

////////////////////////////////////////////////////////////////////////////
#define GET_CVAR_SAFE(var, name) { var = gEnv->pConsole->GetCVar(name); if (!var) {var = SNullCVar::Get(); gEnv->pLog->LogError("UISetting uses undefined CVar: %s", name);} }

void CUISettings::InitEventSystem()
{
	if (!gEnv->pFlashUI) return;

	// CVars
 	GET_CVAR_SAFE(m_pRXVar, "r_Width");
 	GET_CVAR_SAFE(m_pRYVar, "r_Height");
 	GET_CVAR_SAFE(m_pFSVar, "r_Fullscreen");
	GET_CVAR_SAFE(m_pGQVar, "sys_spec");
	GET_CVAR_SAFE(m_pMusicVar, "s_MusicVolume");
	GET_CVAR_SAFE(m_pSFxVar, "s_SFXVolume");
	GET_CVAR_SAFE(m_pVideoVar, "sys_flash_video_soundvolume");
	GET_CVAR_SAFE(m_pMouseSensitivity, "cl_sensitivity");
	GET_CVAR_SAFE(m_pInvertMouse, "cl_invertMouse");
	GET_CVAR_SAFE(m_pInvertController, "cl_invertController");


	m_Resolutions.push_back(std::make_pair(1024,768));
	m_Resolutions.push_back(std::make_pair(1280,720));
	m_Resolutions.push_back(std::make_pair(1280,1050));
	m_Resolutions.push_back(std::make_pair(1680,1050));
	m_Resolutions.push_back(std::make_pair(1920,1080));
	m_Resolutions.push_back(std::make_pair(1920,1200));

	// events to send from this class to UI flowgraphs
	m_pUIFunctions = gEnv->pFlashUI->CreateEventSystem("Settings", IUIEventSystem::eEST_SYSTEM_TO_UI);
	m_eventSender.Init(m_pUIFunctions);

	{
		SUIEventDesc eventDesc("OnGraphicChanged", "Triggered on graphic settings change");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("Resolution", "Resolution ID");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("ResX", "Screen X resolution");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("ResY", "Screen Y resolution");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("FullScreen", "Fullscreen");
		m_eventSender.RegisterEvent<eUIE_GraphicSettingsChanged>(eventDesc);
	}

	{
		SUIEventDesc eventDesc("OnSoundChanged", "Triggered if sound volume changed");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("Music", "Music volume");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("SFx", "SFx volume");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("Video", "Video volume");
		m_eventSender.RegisterEvent<eUIE_SoundSettingsChanged>(eventDesc);
	}

	{
		SUIEventDesc eventDesc("OnGameSettingsChanged", "Triggered if game settings changed");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("MouseSensitivity", "Mouse Sensitivity");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("InvertMouse", "Invert Mouse");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("InvertController", "Invert Controller");
		m_eventSender.RegisterEvent<eUIE_GameSettingsChanged>(eventDesc);
	}

	{
		SUIEventDesc eventDesc("OnResolutions", "Triggered if resolutions were requested.");
		eventDesc.SetDynamic("Resolutions", "UI array with all resolutions (x1,y1,x2,y2,...)");
		m_eventSender.RegisterEvent<eUIE_OnGetResolutions>(eventDesc);
	}

	{
		SUIEventDesc eventDesc("OnResolutionItem", "Triggered once per each resolution if resolutions were requested.");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_String>("ResString", "Resolution as string (X x Y)");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("ID", "Resolution ID");
		m_eventSender.RegisterEvent<eUIE_OnGetResolutionItems>(eventDesc);
	}

	{
		SUIEventDesc eventDesc("OnLevelItem", "Triggered once per level if levels were requested.");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_String>("LevelLabel", "@ui_<level> for localization");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_String>("LevelName", "name of the level");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_String>("LevelPath", "path to the level");
		m_eventSender.RegisterEvent<eUIE_OnGetLevelItems>(eventDesc);
	}


	// events that can be sent from UI flowgraphs to this class
	m_pUIEvents = gEnv->pFlashUI->CreateEventSystem("Settings", IUIEventSystem::eEST_UI_TO_SYSTEM);
	m_eventDispatcher.Init(m_pUIEvents, this, "UISettings");

	{
		SUIEventDesc eventDesc("SetGraphics", "Call this to set graphic modes");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("Resolution", "Resolution ID");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("Quality", "Graphics Quality");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("Fullscreen", "Fullscreen (True/False)");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnSetGraphicSettings);
	}

	{
		SUIEventDesc eventDesc("SetResolution", "Call this to set resolution");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("ResX", "Screen X resolution");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Int>("ResY", "Screen Y resolution");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("Fullscreen", "Fullscreen (True/False)");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnSetResolution);
	}

	{
		SUIEventDesc eventDesc("SetSound", "Call this to set sound settings");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("Music", "Music volume");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("SFx", "SFx volume");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("Video", "Video volume");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnSetSoundSettings);
	}

	{
		SUIEventDesc eventDesc("SetGameSettings", "Call this to set game settings");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Float>("MouseSensitivity", "Mouse Sensitivity");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("InvertMouse", "Invert Mouse");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_Bool>("InvertController", "Invert Controller");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnSetGameSettings);
	}

	{
		SUIEventDesc eventDesc("GetResolutionList", "Execute this node will trigger the \"Events:Settings:OnResolutions\" node.");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnGetResolutions);
	}

	{
		SUIEventDesc eventDesc("GetCurrGraphics", "Execute this node will trigger the \"Events:Settings:OnGraphicChanged\" node.");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnGetCurrGraphicsSettings);
	}

	{
		SUIEventDesc eventDesc("GetCurrSound", "Execute this node will trigger the \"Events:Settings:OnSoundChanged\" node.");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnGetCurrSoundSettings);
	}

	{
		SUIEventDesc eventDesc("GetCurrGameSettings", "Execute this node will trigger the \"Events:Settings:OnGameSettingsChanged\" node.");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnGetCurrGameSettings);
	}

	{
		SUIEventDesc eventDesc("GetLevels", "Execute this node will trigger the \"Events:Settings:OnLevelItem\" node once per level.");
		eventDesc.AddParam<SUIParameterDesc::eUIPT_String>("LevelPath", "ie. levels/multiplayer");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnGetLevels);
	}

	{
		SUIEventDesc eventDesc("LogoutUser", "Execute this node to save settings and logout user");
		m_eventDispatcher.RegisterEvent(eventDesc, &CUISettings::OnLogoutUser);
	}

	gEnv->pFlashUI->RegisterModule(this, "CUISettings");
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::UnloadEventSystem()
{
	if (gEnv->pFlashUI)
		gEnv->pFlashUI->UnregisterModule(this);
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::Init()
{
#ifdef _RELEASE
	for (int i = 0; i < m_Resolutions.size(); ++i)
	{
		if (m_Resolutions[i].first == m_pRXVar->GetIVal() && m_Resolutions[i].second == m_pRYVar->GetIVal())
		{
			m_currResId = i;
			SendGraphicSettingsChange();
			break;
		}
	}
	SendSoundSettingsChange();
	SendGameSettingsChange();
#endif
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::Update(float fDeltaTime)
{
#ifndef _RELEASE
 	static int rX = -1;
 	static int rY = -1;
 	if (rX != m_pRXVar->GetIVal() || rY != m_pRYVar->GetIVal())
	{
		rX = m_pRXVar->GetIVal();
		rY = m_pRYVar->GetIVal();
		m_currResId = 0;

		for (unsigned int i = 0; i < m_Resolutions.size(); ++i)
		{
			if (m_Resolutions[i].first == rX && m_Resolutions[i].second == rY)
			{
				m_currResId = i;
				SendGraphicSettingsChange();
				break;
			}
		}

	}

	static float music = -1.f;
	static float sfx = -1.f;
	static float video = -1.f;
	if (music != m_pMusicVar->GetFVal() || sfx != m_pSFxVar->GetFVal() || video != m_pVideoVar->GetFVal())
	{
		SendSoundSettingsChange();
		music = m_pMusicVar->GetFVal();
		sfx = m_pSFxVar->GetFVal();
		video = m_pVideoVar->GetFVal();
	}

	static float sensivity = -1.f;
	static bool invertMouse = m_pInvertMouse->GetIVal() == 1;
	static bool invertController = m_pInvertController->GetIVal() == 1;
	if (sensivity != m_pMouseSensitivity->GetFVal() || invertMouse != (m_pInvertMouse->GetIVal() == 1) || invertController != (m_pInvertController->GetIVal() == 1))
	{
		SendGameSettingsChange();
		sensivity = m_pMouseSensitivity->GetFVal();
		invertMouse = m_pInvertMouse->GetIVal() == 1;
		invertController = m_pInvertController->GetIVal() == 1;
	}

#endif
}

////////////////////////////////////////////////////////////////////////////
// ui events
////////////////////////////////////////////////////////////////////////////
void CUISettings::OnSetGraphicSettings( int resIndex, int graphicsQuality, bool fullscreen )
{
#if !defined(PS3) && !defined(XENON)
	if (resIndex >= 0 && resIndex < m_Resolutions.size())
	{
		m_currResId = resIndex;

		m_pRXVar->Set(m_Resolutions[resIndex].first);
		m_pRYVar->Set(m_Resolutions[resIndex].second);
		m_pGQVar->Set(graphicsQuality);
		m_pFSVar->Set(fullscreen);

		SendGraphicSettingsChange();
	}
#endif
}

////////////////////////////////////////////////////////////////////////////
// DEPRECATED: should consider to use OnSetGraphicSettings
void CUISettings::OnSetResolution( int resX, int resY, bool fullscreen )
{
#if !defined(PS3) && !defined(XENON)
	m_pRXVar->Set(resX);
	m_pRYVar->Set(resY);
	m_pFSVar->Set(fullscreen);
	return;
#endif
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnSetSoundSettings( float music, float sfx, float video )
{
	m_pMusicVar->Set(music);
	m_pSFxVar->Set(sfx);
	if (m_pVideoVar != m_pMusicVar)
		m_pVideoVar->Set(video);
	SendSoundSettingsChange();
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnSetGameSettings( float sensitivity, bool invertMouse, bool invertController )
{
	m_pMouseSensitivity->Set(sensitivity);
	m_pInvertMouse->Set(invertMouse);
	m_pInvertController->Set(invertController);
	SendGameSettingsChange();
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnGetResolutions()
{
	SendResolutions();
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnGetCurrGraphicsSettings()
{
	SendGraphicSettingsChange();
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnGetCurrSoundSettings()
{
	SendSoundSettingsChange();
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnGetCurrGameSettings()
{
	SendGameSettingsChange();
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnGetLevels( string levelPathFilter )
{
	if (gEnv->pGame && gEnv->pGame->GetIGameFramework() && gEnv->pGame->GetIGameFramework()->GetILevelSystem())
	{
		int i = 0;
		while ( ILevelInfo* pLevelInfo = gEnv->pGame->GetIGameFramework()->GetILevelSystem()->GetLevelInfo( i++ ) )
		{
			string levelPath = pLevelInfo->GetPath();
			levelPath.MakeLower();
			levelPathFilter.MakeLower();
			if(strncmp(levelPathFilter, levelPath.c_str(), levelPathFilter.length()) == 0)
			{
 				m_eventSender.SendEvent<eUIE_OnGetLevelItems>(pLevelInfo->GetDisplayName(), pLevelInfo->GetName(), pLevelInfo->GetPath());
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::OnLogoutUser()
{
//TODO: SAFE CURRENT SETTINGS?

	if (gEnv->pGame && gEnv->pGame->GetIGameFramework() && gEnv->pGame->GetIGameFramework()->GetIPlayerProfileManager())
	{
		IPlayerProfileManager* pProfileManager = gEnv->pGame->GetIGameFramework()->GetIPlayerProfileManager();
		pProfileManager->LogoutUser(pProfileManager->GetCurrentUser());
	}
}


////////////////////////////////////////////////////////////////////////////
// ui functions
////////////////////////////////////////////////////////////////////////////
void CUISettings::SendResolutions()
{
	SUIArguments resolutions;
	for (unsigned int i = 0; i < m_Resolutions.size(); ++i)
	{
		string res;
		res.Format("%i x %i", m_Resolutions[i].first, m_Resolutions[i].second);
		m_eventSender.SendEvent<eUIE_OnGetResolutionItems>(res, (int)i);

		resolutions.AddArgument(m_Resolutions[i].first);
		resolutions.AddArgument(m_Resolutions[i].second);
	}
 	m_eventSender.SendEvent<eUIE_OnGetResolutions>(resolutions);
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::SendGraphicSettingsChange()
{
 	m_eventSender.SendEvent<eUIE_GraphicSettingsChanged>(m_currResId, m_Resolutions[m_currResId].first, m_Resolutions[m_currResId].second, m_pFSVar->GetIVal() != 0);
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::SendSoundSettingsChange()
{
 	m_eventSender.SendEvent<eUIE_SoundSettingsChanged>(m_pMusicVar->GetFVal(), m_pSFxVar->GetFVal(), m_pVideoVar->GetFVal());
}

////////////////////////////////////////////////////////////////////////////
void CUISettings::SendGameSettingsChange()
{
 	m_eventSender.SendEvent<eUIE_GameSettingsChanged>(m_pMouseSensitivity->GetFVal(), m_pInvertMouse->GetIVal() != 0, m_pInvertController->GetIVal() != 0);
}

////////////////////////////////////////////////////////////////////////////
REGISTER_UI_EVENTSYSTEM( CUISettings );
