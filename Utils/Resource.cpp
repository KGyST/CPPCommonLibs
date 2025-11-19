#include	"Resource.hpp"


// -----------------------------------------------------------------------------
// Load a localisable Unicode string from resource
// -----------------------------------------------------------------------------

void		GetStringFromResource(GS::UniString* buffer, short resID, short stringID)
{
	if (buffer != nullptr && !RSGetIndString(buffer, resID, stringID, ACAPI_GetOwnResModule()))
		buffer->Clear();

	return;
}

GS::UniString GetStringFromResource_(short resID, short stringID)
{
	GS::UniString *buffer = new GS::UniString;

	RSGetIndString(buffer, resID, stringID, ACAPI_GetOwnResModule());

	GS::UniString result = *buffer;
	auto _s = result.ToCStr().Get();

	return result;
}

GS::UniString GSFR(IntStr stringID)
{
	GS::UniString _r = GetStringFromResource_(TABLE_DATA, (short)stringID);
	auto _s = _r.ToCStr().Get();
	return _r;
}
// GetStringFromResource

