#ifndef AC_27_H
#define AC_27_H

//#include	"ACAPI_MigrationHeader.hpp"

inline GSErrCode ACAPI_Database(API_DatabaseID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr)
{
	switch (code) {
	case APIDb_CalcBoundsID:
		return ACAPI_Element_CalcBounds(reinterpret_cast<const API_Elem_Head*> (par1), reinterpret_cast<API_Box3D*> (par2));
	default:
		return NULL;
	}
}

inline GSErrCode ACAPI_Interface(API_InterfaceID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr, void* par5 = nullptr)
{
	switch (code) {
	case APIIo_GetArcID:
		return ACAPI_UserInput_GetArc(reinterpret_cast<API_GetArcType*> (par1), reinterpret_cast<RubberLineInfoProc*> (par2));
	case APIIo_GetLineID:
		return ACAPI_UserInput_GetLine(reinterpret_cast<API_GetLineType*> (par1), reinterpret_cast<RubberLineInfoProc*> (par2));
	case APIIo_GetPointID:
		return ACAPI_UserInput_GetPoint(reinterpret_cast<API_GetPointType*> (par1), reinterpret_cast<RubberLineInfoProc*> (par2), reinterpret_cast<Get3DComponentProc*> (par3));
	case APIIo_GetMenuItemFlagsID:
		return ACAPI_MenuItem_GetMenuItemFlags(reinterpret_cast<const API_MenuItemRef*> (par1), reinterpret_cast<GSFlags*> (par2), reinterpret_cast<GS::UniString*> (par3));
	case APIIo_SetMenuItemFlagsID:
		return ACAPI_MenuItem_SetMenuItemFlags(reinterpret_cast<const API_MenuItemRef*> (par1), reinterpret_cast<GSFlags*> (par2), reinterpret_cast<GS::UniString*> (par3));
	default:
		return NULL;
	}
}

inline GSErrCode ACAPI_Environment(API_EnvironmentID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr)
{
	switch (code) {
	case APIEnv_GetLibrariesID:
		return ACAPI_LibraryManagement_GetLibraries(reinterpret_cast<GS::Array<API_LibraryInfo>*> (par1), reinterpret_cast<Int32*> (par2));
	default:
		return NULL;
	}
}

inline GSErrCode ACAPI_Navigator(API_NavigatorID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr)
{
	switch (code) {
	case APINavigator_GetNavigatorChildrenItemsID:
		return ACAPI_Navigator_GetNavigatorChildrenItems(reinterpret_cast<API_NavigatorItem*> (par1), reinterpret_cast<GS::Array<API_NavigatorItem>*> (par2));
	case APINavigator_GetNavigatorSetID:
		return ACAPI_Navigator_GetNavigatorSet(reinterpret_cast<API_NavigatorSet*> (par1), reinterpret_cast<Int32*> (par2));
	case APINavigator_GetNavigatorSetNumID:
		return ACAPI_Navigator_GetNavigatorSetNum(reinterpret_cast<Int32*> (par1));
	default:
		return NULL;
	}
}

inline GSErrCode ACAPI_Goodies(API_GoodiesID code, void* par1 = nullptr, void* par2 = nullptr, void* par3 = nullptr, void* par4 = nullptr)
{
	switch (code) {
	case APIAny_GetElemLibPartUnIdID:
		return ACAPI_LibraryPart_GetElemLibPartUnId(reinterpret_cast<API_Elem_Head*> (par1), reinterpret_cast<char*> (par2));
	default:
		return NULL;
	}
}

inline GSErrCode ACAPI_Element_Select(const GS::Array<API_Neig>& selNeigs, bool add)
{
	return ACAPI_Selection_Select(selNeigs, add);
}


inline GSErrCode ACAPI_Install_MenuHandler(short menuStrResID, APIMenuCommandProc* handlerProc)
{
	return ACAPI_MenuItem_InstallMenuHandler(menuStrResID, handlerProc);
}

inline GSErrCode ACAPI_Register_Menu(short menuStrResID, short promptStrResID, APIMenuCodeID menuPosCode, GSFlags menuFlags)
{
	return ACAPI_MenuItem_RegisterMenu(menuStrResID, promptStrResID, menuPosCode, menuFlags);
}

inline GSErrCode ACAPI_Notify_CatchSelectionChange(APISelectionChangeHandlerProc* handlerProc)
{
	return ACAPI_Notification_CatchSelectionChange(handlerProc);
}

inline GSErrCode ACAPI_LibPart_GetNum(Int32* count)
{
	return ACAPI_LibraryPart_GetNum(count);
}

inline GSErrCode ACAPI_LibPart_GetParams(Int32 libInd, double* a, double* b, Int32* addParNum, API_AddParType*** addPars)
{
	return ACAPI_LibraryPart_GetParams(libInd, a, b, addParNum, addPars);
}

inline GSErrCode ACAPI_LibPart_Search(API_LibPart* ancestor, bool createIfMissing, bool onlyPlaceable = false)
{
	return ACAPI_LibraryPart_Search(ancestor, createIfMissing, onlyPlaceable);
}

inline GSErrCode ACAPI_LibPart_Get(API_LibPart* libPart)
{
	return ACAPI_LibraryPart_Get(libPart);
}

inline GSErrCode ACAPI_Install_PanelHandler(Int32 refCon, APIPanelCreateProc* handlerCreateProc, APIPanelDestroyProc* handlerDestroyProc)
{
	return ACAPI_AddOnIntegration_InstallPanelHandler(refCon, handlerCreateProc, handlerDestroyProc);
}

inline GSErrCode ACAPI_Register_InfoBoxPanel(Int32 refCon, const API_ElemType& tool, short stringId, short pageId, bool visibleByDefault = false)
{
	return ACAPI_AddOnIntegration_RegisterInfoBoxPanel(refCon, tool, stringId, pageId, visibleByDefault);
}

#endif

