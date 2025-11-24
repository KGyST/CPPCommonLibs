#include	"Resource.hpp"


// -----------------------------------------------------------------------------
// Load a localisable Unicode string from resource
// -----------------------------------------------------------------------------

GS::UniString GetStringFromResource(short resID, short stringID)
{
	GS::UniString result;

	auto _a = ACAPI_GetOwnResModule();

	RSGetIndString(&result, resID, stringID, _a);

	return result;
}

// GetStringFromResource

