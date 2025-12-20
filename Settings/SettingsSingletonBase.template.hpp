#ifndef _SETTINGS_SINGLETON_TEMPLATE_HPP
#define _SETTINGS_SINGLETON_TEMPLATE_HPP

#include	<mutex>

#include	"../APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"../APICommon.h"

#if ACVER == 27
#include	"AC27.hpp"
#endif

#include  "PolygonReducer_Resource.h"
#include	"Logger/Logger.hpp"
#include	"Utils/Resource.hpp"


template <class T_Derived>
class SettingsSingletonBase
{
	SettingsSingletonBase(const SettingsSingletonBase&) = delete;
	void operator=(const SettingsSingletonBase&) = delete;

protected:
	GS::UniString							m_companyName;
	GS::UniString							m_appName;
	Logger										m_logger;

	SettingsSingletonBase() = default;
	SettingsSingletonBase(GS::UniString i_companyName, GS::UniString i_appName)
	: m_companyName(i_companyName)
	, m_appName(i_appName)
	, m_logger(m_companyName, m_appName) {};
	~SettingsSingletonBase() = default;
	GS::UniString GetRegPath() { return "SOFTWARE\\" + m_companyName + "\\" + m_appName;	}

public:
	static T_Derived& GetInstance() 
	{
		static T_Derived singleton;
		return singleton;
	}

	Logger& GetLogger() { 
		return m_logger; };
};


#endif // !_SETTINGS_SINGLETON_TEMPLATE_HPP

