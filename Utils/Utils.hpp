#ifndef _UTILS_HPP
#define _UTILS_HPP

#include	"../APIEnvir.h"
#include	"ACAPinc.h"					// also includes APIdefs.h
#include	"../APICommon.h"

#if ACVER == 27
//#include	"ACAPI_MigrationHeader.hpp"
#include	"..\..\CPPCommonLibs\AC27.hpp"
#endif

#include	"StringsEnum.hpp"

extern void		GetStringFromResource(GS::UniString* buffer, short resID, short stringID);
extern GS::UniString	GetStringFromResource_(short resID, short stringID);
extern GS::UniString GSFR(IntStr stringID);

#endif //_UTILS_HPP

