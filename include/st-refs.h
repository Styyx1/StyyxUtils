#pragma once

namespace StyyxUtil
{
struct RefUtil
{
	/// @brief Check if a reference is a Ore Vein
	/// @note Requires [OreKeywords_KID.ini](https://github.com/Styyx1/StyyxUtils/blob/main/distr/OreKeywords_KID.ini) to be present in the user's game
	/// @param a_ref The reference to to check
	/// @return bool is true if the reference or its base object have the keyword
	static bool IsRefOreVein( RE::TESObjectREFR *a_ref )
	{
		if ( !a_ref )
			return false;

		return a_ref->HasKeywordByEditorID( "ActiTypeOre" ) || a_ref->GetBaseObject()->HasKeywordByEditorID( "ActiTypeOre" );
	}
};
}
