#ifndef _WINREG_HPP
#define _WINREG_HPP

#include	"APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"APICommon.h"

#include	"winreg.h"

const HKEY _HKEY = HKEY_CURRENT_USER;

// -------------------------------- Helper functions -------------------------------

HKEY _GetOrCreateRegPath(const GS::UniString& path, HKEY hKey = HKEY_CURRENT_USER);

template<typename T>
void _Set(const GS::UniString& i_path, const GS::UniString& i_key, const T i_val, HKEY i_hKey = HKEY_CURRENT_USER, DWORD* const o_bufSize = NULL)
{
	HKEY hKey = _GetOrCreateRegPath(i_path, i_hKey);
	const DWORD _bs = sizeof(T);

	LSTATUS status = RegSetValueExW(hKey,
		i_key.ToUStr().Get(),
		0,
		RegTraits<T>::RegType,
		reinterpret_cast<const BYTE*>(&i_val),
		_bs);

	if (o_bufSize) *o_bufSize = _bs;

	status = RegCloseKey(hKey);
}

template<typename T>
T _Get(const GS::UniString& i_path, const GS::UniString& i_key, HKEY i_hKey = HKEY_CURRENT_USER, DWORD* o_bufSize = NULL, LSTATUS* o_status = NULL)
{
	T iBuffer;
	DWORD iBufferSize = sizeof(T);

	LSTATUS _status = RegGetValueW(i_hKey,
		i_path.ToUStr().Get(),		/*L"SOFTWARE\\GRAPHISOFT\\ARCHICAD\\Archicad 26.0.0 INT R1\\Add-On Manager",*/
		i_key.ToUStr().Get(),		/*L"Use Default Location",*/
		(RegTraits<T>::RegGetFlag),
		NULL,
		reinterpret_cast<BYTE*>(&iBuffer),
		&iBufferSize);

	if (o_bufSize) *o_bufSize = iBufferSize;
	if (o_status) *o_status = _status;

	return iBuffer;
}

template<typename T>
T _GetOrDefault(const GS::UniString& i_path, const GS::UniString& i_key, const T i_defaultValue, HKEY i_hKey = HKEY_CURRENT_USER, DWORD* const o_bufSize = NULL)
{
	LSTATUS _status;

	T iResult = _Get<T>(i_path, i_key, i_hKey, o_bufSize, &_status);

	if (o_bufSize && _status == ERROR_SUCCESS)
		return iResult;
	else
		return i_defaultValue;
}

template<typename T>
T _GetOrSetDefault(const GS::UniString& i_path, const GS::UniString& i_key, const T i_defaultValue, HKEY i_hKey = HKEY_CURRENT_USER, DWORD* const o_bufSize = NULL)
{
	LSTATUS _status;

	T iResult = _Get<T>(i_path, i_key, i_hKey, o_bufSize, &_status);

	if (o_bufSize && _status == ERROR_SUCCESS)
		return iResult;
	else
	{
		_Set<T>(i_path, i_key, i_defaultValue, i_hKey, o_bufSize);
		return i_defaultValue;
	}
}

// --------------------------------/Helper functions -------------------------------

inline UInt32 GetRegInt(const GS::UniString& path, const GS::UniString& key, HKEY hkey = _HKEY, DWORD* const bufSize = NULL) { return _Get<UInt32>(path, key, hkey, bufSize); }

inline UInt32 GetRegIntOrDefault(const GS::UniString& path, const GS::UniString& key, const int defaultValue, HKEY hkey = _HKEY, DWORD* const bufSize = NULL) { return _GetOrDefault<UInt32>(path, key, defaultValue, hkey, bufSize); }

//If key doesn't exist, creates it with the default value and then returns it:
inline UInt32 GetRegIntOrSetDefault(const GS::UniString& path, const GS::UniString& key, const int defaultValue, HKEY hKey = HKEY_CURRENT_USER, DWORD* const bufSize = NULL) { return _GetOrSetDefault<UInt32>(path, key, defaultValue, hKey, bufSize); }

inline void SetRegInt(const GS::UniString& path, const GS::UniString& key, const UInt32 value, HKEY hkey = _HKEY, DWORD* const bufSize = NULL) { return _Set<UInt32>(path, key, value, hkey, bufSize); }


inline double GetRegDouble(const GS::UniString& path, const GS::UniString& key, HKEY hkey = _HKEY, DWORD* const bufSize = NULL) { return _Get<double>(path, key, hkey, bufSize); }

inline double GetRegDoubleOrDefault(const GS::UniString& path, const GS::UniString& key, const double& defaultValue, HKEY hkey = _HKEY, DWORD* const bufSize = NULL) { return _GetOrDefault<double>(path, key, defaultValue, hkey, bufSize); }

//If key doesn't exist, creates it with the default value and then returns it:
inline double GetRegDoubleOrSetDefault(const GS::UniString& path, const GS::UniString& key, const int defaultValue, HKEY hKey = HKEY_CURRENT_USER, DWORD* const bufSize = NULL) { return _GetOrSetDefault<double>(path, key, defaultValue, hKey, bufSize); }

inline void SetRegDouble(const GS::UniString& path, const GS::UniString& key, const double value, HKEY hkey  = HKEY_CURRENT_USER , DWORD* const bufSize  = nullptr ) { return _Set<double>(path, key, value, hkey, bufSize); }


GS::UniString GetRegString(const GS::UniString& path, const GS::UniString& key, HKEY hkey = _HKEY, DWORD* const bufSize = NULL);

GS::UniString GetRegStringOrDefault(const GS::UniString& path, const GS::UniString& key, const GS::UniString& defaultValue, HKEY hkey = _HKEY, DWORD* const bufSize = NULL);

//If key doesn't exist, creates it with the default value and then returns it:
GS::UniString GetRegStringOrSetDefault(const GS::UniString& path, const GS::UniString& key, const GS::UniString& defaultValue, HKEY hKey = HKEY_CURRENT_USER, DWORD* bufSize = NULL);

void SetRegString(const GS::UniString& path, const GS::UniString& key, const GS::UniString& value, HKEY hkey = _HKEY, DWORD* const bufSize = NULL);


template <typename T>
struct RegTraits;

template <>
struct RegTraits<double>
{
	static constexpr DWORD RegType = REG_BINARY;
	static constexpr DWORD RegGetFlag = RRF_RT_REG_BINARY;
};

template <>
struct RegTraits<UInt32>
{
	static constexpr DWORD RegType = REG_DWORD;
	static constexpr DWORD RegGetFlag = RRF_RT_REG_DWORD;
};


#endif //_WINREG_HPP

