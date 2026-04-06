#pragma once

namespace StyyxUtil
{
    struct CellUtil
    {
        /// @brief A vector of what I consider dungeon Keywords
        inline static const std::vector<std::string> is_a_dungeon {
            "LocTypeDungeon",     "LocSetCave",          "LocSetCaveIce",           "LocTypeDwarvenAutomatons",
            "LocTypeAnimalDen",   "LocTypeBanditCamp",   "LocTypeDragonPriestLair", "LocTypeDraugrCrypt",
            "LocTypeFalmerHive",  "LocTypeForswornCamp", "LocTypeGiantCamp",        "LocTypeHagravenNest",
            "LocTypeVampireLair", "LocTypeWarlockLair",  "LocTypeWerewolfLair"};

        /// @brief Check if a cell is a dungeon
        /// @param a_cell The cell to check
        /// @return Returns true if the cell has one of the dungeon keywords
        static bool IsDungeon(const RE::TESObjectCELL *a_cell)
        {
            if (!a_cell)
                return false;
            if (const auto loc = a_cell->GetLocation(); loc && loc->HasAnyKeywordByEditorID(is_a_dungeon) && a_cell->IsInteriorCell())
            {
                return true;
            }
            return false;
        }

        /// @brief Check if a cell is a Jail
        /// @param a_cell The cell to check
        /// @return Returns true if the cell has the Jail keyword
        static bool IsJail(RE::TESObjectCELL *a_cell)
        {
            if (!a_cell)
                return false;
            const auto loc = a_cell->GetLocation();
            if (const auto key = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("LocTypeJail"); key && loc && loc->HasKeyword(key))
            {
                return true;
            }
            return false;
        }

        static bool IsPlayerHome(RE::BGSLocation* a_location)
        {
            if (!a_location)
                return false;
            static auto PlayerCellKeyword = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("LocTypePlayerHouse");
            if (PlayerCellKeyword && a_location->HasKeyword(PlayerCellKeyword))
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
}
