#ifndef _WINREG_HPP
#define _WINREG_HPP

#include	"APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"APICommon.h"

#include	"winreg.h"

const HKEY _HKEY = HKEY_CURRENT_USER;

GS::UniString GetRegString(const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hkey = _HKEY, DWORD * const o_bufSize = NULL);

GS::UniString GetRegStringOrDefault(const GS::UniString& i_defaultValue, const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hkey = _HKEY, DWORD * const o_bufSize = NULL);

//If key doesn't exist, creates it with the default value and then returns it:
GS::UniString GetRegStringOrSetDefault(const GS::UniString& i_defaultValue, const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hKey = HKEY_CURRENT_USER, DWORD* o_bufSize = NULL);

UInt32 GetRegInt(const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hkey = _HKEY, DWORD * const o_bufSize = NULL);

UInt32 GetRegIntOrDefault(const int i_defaultValue, const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hkey = _HKEY, DWORD * const o_bufSize = NULL);

//If key doesn't exist, creates it with the default value and then returns it:
UInt32 GetRegIntOrSetDefault(const int i_defaultValue, const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hKey = HKEY_CURRENT_USER, DWORD* const o_bufSize = NULL);

void SetRegString(const GS::UniString& i_val, const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hkey = _HKEY, DWORD * const o_bufSize = NULL);

void SetRegInt(const UInt32 i_val, const GS::UniString& i_key, const GS::UniString& i_path, HKEY i_hkey = _HKEY, DWORD * const o_bufSize = NULL);

#endif //_WINREG_HPP

