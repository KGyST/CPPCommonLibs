#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include	"../APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"../APICommon.h"

//#if ACVER == 27
//#include	"ACAPI_MigrationHeader.hpp"
#include	"AC27.hpp"
//#endif

#include	"StringsEnum.hpp"

void		GetStringFromResource(GS::UniString* buffer, short resID, short stringID);
GS::UniString	GetStringFromResource_(short resID, short stringID);
GS::UniString GSFR(IntStr stringID);

#endif //RESOURCE_HPP

