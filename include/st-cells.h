#pragma once

namespace StyyxUtil
{

struct CellUtil
{
    /// <summary>
    /// Vector with what i consider a dungeon in the game
    /// </summary>
    inline static std::vector<std::string> is_a_dungeon{
        "LocTypeDungeon",     "LocSetCave",          "LocSetCaveIce",           "LocTypeDwarvenAutomatons",
        "LocTypeAnimalDen",   "LocTypeBanditCamp",   "LocTypeDragonPriestLair", "LocTypeDraugrCrypt",
        "LocTypeFalmerHive",  "LocTypeForswornCamp", "LocTypeGiantCamp",        "LocTypeHagravenNest",
        "LocTypeVampireLair", "LocTypeWarlockLair",  "LocTypeWerewolfLair"};

    /// <summary>
    /// Check if a_cell is considered a dungeon
    /// </summary>
    /// <param name="a_cell"></param>
    /// <returns></returns>
    inline static bool IsDungeon(RE::TESObjectCELL *a_cell)
    {
        if (!a_cell)
            return false;
        auto loc = a_cell->GetLocation();
        if (loc && loc->HasAnyKeywordByEditorID(is_a_dungeon) && a_cell->IsInteriorCell())
        {
            return true;
        }
        else
            return false;
    }

    /// <summary>
    /// Check if a_cell is a Jail
    /// </summary>
    /// <param name="a_cell"></param>
    /// <returns></returns>
    inline static bool IsJail(RE::TESObjectCELL *a_cell)
    {
        if (!a_cell)
            return false;
        auto loc = a_cell->GetLocation();
        auto key = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("LocTypeJail");
        if (key && loc && loc->HasKeyword(key))
        {
            return true;
        }
        return false;
    }
};
} // namespace StyyxUtil
