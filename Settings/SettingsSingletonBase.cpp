#include "SettingsSingletonBase.hpp"
#include "Utils/Resource.hpp"
#include <exception>

SettingsSingleton& (*SETTINGS)() = SettingsSingleton::GetInstance;

SettingsSingleton::SettingsSingleton()
	:m_companyName				(GetStringFromResource_(32506, 1))
	,m_appName					(GetStringFromResource_(32000, 1))
	,m_logger					(Logger(m_companyName, m_appName))
{
}

SettingsSingleton::~SettingsSingleton()
{
}

SettingsSingleton& SettingsSingleton::GetInstance()
{
	std::lock_guard<std::mutex> lock(_mutex);

	static SettingsSingleton singleton;

	return singleton;
}

