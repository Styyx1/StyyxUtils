#pragma once

namespace StyyxUtil
{
struct RefUtil
{	
	//this will require a specific _KID.ini file to work as Ore Veins do not have a keyword by default. 
	static inline bool IsRefOreVein( RE::TESObjectREFR *a_ref )
	{
		if ( !a_ref )
			return false;

		return a_ref->HasKeywordByEditorID( "ActiTypeOre" ) || a_ref->GetBaseObject()->HasKeywordByEditorID( "ActiTypeOre" );
	}
};
}
