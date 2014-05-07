#ifndef _DEBUGHELPERS_H_
#define _DEBUGHELPERS_H_

#include <sstream>
#include <CPluginCEF.h>
#include <DxErr.h>

#define SHOW_MSG(msg,title) MessageBox(NULL,msg,title,MB_ICONERROR|MB_OK);

#define LOG(level,msg) { \
	std::ostringstream os; \
	os << PLUGIN_CONSOLE_PREFIX << "[" << level << "] " << msg; \
	gEnv->pLog->Log(os.str().c_str()); }

#define logERROR(msg) { \
	std::ostringstream os; \
	os << PLUGIN_CONSOLE_PREFIX << "[ERROR] " << msg << "\nat " << __FILE__ << ":" << __LINE__; \
	gEnv->pLog->LogError(os.str().c_str()); \
	SHOW_MSG(os.str().c_str(),"Error"); }

#define logWARN(msg) { \
	std::ostringstream os; \
	os << PLUGIN_CONSOLE_PREFIX << "[WARNING] " << msg << "\nat " << __FILE__ << ":" << __LINE__; \
	gEnv->pLog->LogWarning(os.str().c_str()); }

#define logINFO(msg) LOG("INFO",msg)
#define logDEBUG(msg) LOG("DEBUG",msg)

#define CHECK(val,msg) if(!(val)) { logERROR(msg); return; }
#define CHECK_RET(val,ret,msg) if(!(val)) { logERROR(msg); return ret; }

#define CHECK_RESULT(val,msg) { HRESULT hr = (val); if(FAILED(hr)) { logERROR(msg << ", err=" << DXGetErrorString(hr) << ", desc=" << DXGetErrorDescription(hr)); return; } }
#define CHECK_RESULT_RET(val,ret,msg) { HRESULT hr = (val); if(FAILED(hr)) { logERROR(msg << ", err=" << DXGetErrorString(hr) << ", desc=" << DXGetErrorDescription(hr)); return ret; } }

#define THROW(msg) { logERROR("Throwing exception: " << msg); throw ; }
#define THROW_IF(cond,msg) if(cond) THROW(msg)

#endif
