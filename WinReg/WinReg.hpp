#ifndef _WINREG_HPP
#define _WINREG_HPP

#include	"APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"APICommon.h"

#include	"winreg.h"

const HKEY _HKEY = HKEY_CURRENT_USER;

GS::UniString GetRegString(const GS::UniString& path, const GS::UniString& key, HKEY hkey = _HKEY, DWORD * const bufSize = NULL);

GS::UniString GetRegStringOrDefault(const GS::UniString& path, const GS::UniString& key, const GS::UniString& defaultValue, HKEY hkey = _HKEY, DWORD * const bufSize = NULL);

//If key doesn't exist, creates it with the default value and then returns it:
GS::UniString GetRegStringOrSetDefault(const GS::UniString& path, const GS::UniString& key, const GS::UniString& defaultValue, HKEY hKey = HKEY_CURRENT_USER, DWORD* bufSize = NULL);

void SetRegInt(const GS::UniString& path, const GS::UniString& key, const UInt32 value, HKEY hkey = _HKEY, DWORD* const bufSize = NULL);

UInt32 GetRegInt(const GS::UniString& path, const GS::UniString& key, HKEY hkey = _HKEY, DWORD * const bufSize = NULL);

UInt32 GetRegIntOrDefault(const GS::UniString& path, const GS::UniString& key, const int defaultValue, HKEY hkey = _HKEY, DWORD * const bufSize = NULL);

//If key doesn't exist, creates it with the default value and then returns it:
UInt32 GetRegIntOrSetDefault(const GS::UniString& path, const GS::UniString& key, const int defaultValue, HKEY hKey = HKEY_CURRENT_USER, DWORD* const bufSize = NULL);

void SetRegString(const GS::UniString& path, const GS::UniString& key, const GS::UniString& value, HKEY hkey = _HKEY, DWORD * const bufSize = NULL);


#endif //_WINREG_HPP

