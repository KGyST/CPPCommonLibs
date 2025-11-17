#ifndef _SETTINGS_SINGLETON_TEMPLATE_HPP
#define _SETTINGS_SINGLETON_TEMPLATE_HPP

#include	"../APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"../APICommon.h"

#if ACVER == 27
#include	"AC27.hpp"
#endif

#include	<mutex>
#include	"Logger/Logger.hpp"
#include	"Utils/Resource.hpp"


template <class Derived>
class SettingsSingletonBase
{
	static std::mutex _mutex;

	SettingsSingletonBase(const SettingsSingletonBase&) = delete;
	void operator=(const SettingsSingletonBase&) = delete;

protected:
	GS::UniString								m_appName;
	GS::UniString								m_companyName;
	Logger											m_logger;

	SettingsSingletonBase() = default;
	SettingsSingletonBase(const GS::UniString& companyName, const GS::UniString& appName)
		: m_companyName(companyName)
		, m_appName(appName)
		, m_logger(companyName, appName) {}
	~SettingsSingletonBase() = default;

public:
	static Derived& GetInstance() 
	{
		std::lock_guard<std::mutex> lock(_mutex);

		static Derived singleton;

		return singleton;
	}

	Logger& GetLogger() { return m_logger; };
};

template <class Derived>
std::mutex SettingsSingletonBase<Derived>::_mutex;


#endif // !_SETTINGS_SINGLETON_TEMPLATE_HPP

