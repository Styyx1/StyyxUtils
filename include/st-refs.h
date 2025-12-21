#pragma once

namespace StyyxUtil
{
struct RefUtil
{	
	/// <summary>
	/// Is a reference a Ore Vein
	/// this will require a specific _KID.ini file, found in this library's distr folder, to work, as Ore Veins do not have a keyword by default. 
	/// </summary>
	/// <param name="a_ref"></param>
	/// <returns></returns>
	static inline bool IsRefOreVein( RE::TESObjectREFR *a_ref )
	{
		if ( !a_ref )
			return false;

		return a_ref->HasKeywordByEditorID( "ActiTypeOre" ) || a_ref->GetBaseObject()->HasKeywordByEditorID( "ActiTypeOre" );
	}
};
}
