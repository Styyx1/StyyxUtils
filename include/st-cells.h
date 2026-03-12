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

    /// @brief Get a vector of all actors in the specified cell
    /// @param a_cell the cell to check
    /// @return vector with all actors in the cell
    static std::vector<RE::Actor*> GetAllActorsInCell(RE::TESObjectCELL *a_cell)
    {
        std::vector<RE::Actor*> result;
        if (!a_cell)
            return result;

        for (const auto& ref : a_cell->references)
        {
            if (!ref)
                continue;
            auto actor = ref->As<RE::Actor>();
            if (!actor)
                continue;
            result.push_back(actor);
        }
        return result;
    }

};
} // namespace StyyxUtil
