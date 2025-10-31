#pragma once

namespace StyyxUtil {

	struct CellUtil {
		inline static std::vector<std::string> is_a_dungeon{
		"LocTypeDungeon",
		"LocSetCave",
		"LocSetCaveIce",
		"LocTypeDwarvenAutomatons",
		"LocTypeAnimalDen",
		"LocTypeBanditCamp",
		"LocTypeDragonPriestLair",
		"LocTypeDraugrCrypt",
		"LocTypeFalmerHive",
		"LocTypeForswornCamp",
		"LocTypeGiantCamp",
		"LocTypeHagravenNest",
		"LocTypeVampireLair",
		"LocTypeWarlockLair",
		"LocTypeWerewolfLair" };

		inline static bool IsDungeon(RE::TESObjectCELL* a_cell)
		{
			auto loc = a_cell->GetLocation();
			if (loc && loc->HasAnyKeywordByEditorID(is_a_dungeon) && a_cell->IsInteriorCell())
			{
				return true;
			}
			else
				return false;
		}
	};
}