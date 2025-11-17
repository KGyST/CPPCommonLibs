#ifndef _SETTINGS_SINGLETON_HPP
#define _SETTINGS_SINGLETON_HPP

#include	"../APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"../APICommon.h"

#if ACVER == 27
#include	"AC27.hpp"
#endif

#include	<mutex>
#include	"Logger/Logger.hpp"


class SettingsSingleton
{
	SettingsSingleton();
	~SettingsSingleton();
	SettingsSingleton(const SettingsSingleton&);
	void operator=(const SettingsSingleton&) {};
	
	GS::UniString								m_appName;
	GS::UniString								m_companyName;
	Logger											m_logger;
	GS::UniString								m_sFilter;
public:
	static SettingsSingleton& GetInstance();

	Logger& GetLogger() { return m_logger; };

	void SetFilterText(GS::UniString const& i_sFilter) { m_sFilter = i_sFilter.ToLowerCase(); };
	GS::UniString GetFilterText() const { return m_sFilter ; } ;
};

static std::mutex _mutex;
extern SettingsSingleton& (*SETTINGS)();

#endif // !_SETTINGS_SINGLETON_HPP

