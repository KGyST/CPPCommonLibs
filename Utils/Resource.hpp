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

GS::UniString	GetStringFromResource(short resID, short stringID);

#endif //RESOURCE_HPP

