#include	"WinReg.hpp"

HKEY _GetOrCreateRegPath(const GS::UniString& i_path, HKEY i_hKey/* = HKEY_CURRENT_USER*/)
{
	HKEY hKey;
	LSTATUS status = RegCreateKeyExW(i_hKey,
		(wchar_t*)(i_path.ToUStr().Get()),
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hKey,
		NULL
	);

	return hKey;
}

GS::UniString GetRegString(const GS::UniString& i_path, const GS::UniString& i_key, HKEY i_hKey/* = HKEY_CURRENT_USER*/, DWORD* const o_bufSize/* = NULL*/)
{
	char sBuffer[255];
	DWORD iBuffer = 255;

	LSTATUS _stat = RegGetValueW(i_hKey,
		i_path.ToUStr().Get(),		/*L"SOFTWARE\\GRAPHISOFT\\ARCHICAD\\Archicad 26.0.0 INT R1\\Add-On Manager",*/
		i_key.ToUStr().Get(),		/*L"Default Location",*/
		RRF_RT_REG_SZ + RRF_ZEROONFAILURE,
		NULL,
		&sBuffer,
		&iBuffer);

	wchar_t* ws = (wchar_t*)sBuffer;

	if (o_bufSize != NULL)
		*o_bufSize = iBuffer;

	return GS::UniString(ws);
}

GS::UniString GetRegStringOrDefault(const GS::UniString& i_path, const GS::UniString& i_key, const GS::UniString& i_defaultValue, HKEY i_hKey/* = HKEY_CURRENT_USER*/, DWORD* o_bufSize/* = NULL*/)
{
	DWORD iBufferSize = 255;

	GS::UniString iResult = GetRegString(i_path, i_key, i_hKey, &iBufferSize);

	if (o_bufSize != NULL)
		*o_bufSize = iBufferSize;

	if (iBufferSize != NULL)
		return iResult;
	else
		return i_defaultValue;
}

GS::UniString GetRegStringOrSetDefault(const GS::UniString& i_path, const GS::UniString& i_key, const GS::UniString& i_defaultValue, HKEY i_hKey/* = HKEY_CURRENT_USER*/, DWORD* o_bufSize/* = NULL*/)
{
	DWORD iBufferSize = 255;

	GS::UniString iResult = GetRegString(i_path, i_key, i_hKey, &iBufferSize);

	if (o_bufSize != NULL)
		*o_bufSize = iBufferSize;

	if (iBufferSize != NULL)
		return iResult;
	else
		SetRegString(i_path, i_key, i_defaultValue, i_hKey, o_bufSize);

	return i_defaultValue;
}

void SetRegString(const GS::UniString& i_path, const GS::UniString& i_key, const GS::UniString& i_val, HKEY i_hKey/* = HKEY_CURRENT_USER*/, DWORD* const o_bufSize/* = NULL*/)
{
	HKEY hKey = _GetOrCreateRegPath(i_path, i_hKey);

	auto wVal = (wchar_t*)(i_val.ToUStr().Get());
	auto key = (wchar_t*)(i_key.ToUStr().Get());

	auto _b = (BYTE*)wVal;
	auto _bs = (DWORD)(i_val.GetLength() * 2);

	LSTATUS status = RegSetValueExW(hKey,
		key,
		0,
		REG_SZ,
		_b,
		_bs);

	if (o_bufSize != NULL)
		*o_bufSize = _bs;

	status = RegCloseKey(i_hKey);
	status = RegCloseKey(hKey);
}

