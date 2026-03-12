//
// Created by styyx on 08/03/2026.
//

#pragma once
#include <unordered_set>

namespace StyyxUtil
{
    struct PerkUtil
    {

        ///
        /// @brief array of all skill relevant for the stats menu. Does not take any custom skill or the likes into account
        ///
        static constexpr std::array<RE::ActorValue, 18> kPlayableSkills = {
            RE::ActorValue::kOneHanded, RE::ActorValue::kTwoHanded,
            RE::ActorValue::kArchery, RE::ActorValue::kBlock,
            RE::ActorValue::kSmithing, RE::ActorValue::kHeavyArmor,
            RE::ActorValue::kLightArmor, RE::ActorValue::kPickpocket,
            RE::ActorValue::kLockpicking, RE::ActorValue::kSneak,
            RE::ActorValue::kAlchemy, RE::ActorValue::kSpeech,
            RE::ActorValue::kAlteration, RE::ActorValue::kConjuration,
            RE::ActorValue::kDestruction, RE::ActorValue::kIllusion,
            RE::ActorValue::kRestoration, RE::ActorValue::kEnchanting
        };

        /// @brief recursively look through the perk tree nodes in an AVIF
        /// @param node the perk tree node you want to start with
        /// @param set_out unordered set reference to write the perks to
        /// @param visited unordered set to add the visited nodes to
        static void TraversePerkNode(RE::BGSSkillPerkTreeNode* node,
                                     std::unordered_set<RE::BGSPerk*>& set_out,
                                     std::unordered_set<RE::BGSSkillPerkTreeNode*>& visited)
        {
            if (!node || !visited.insert(node).second)
                return;

            if (node->perk) {
                set_out.insert(node->perk);
            }

            for (auto* child : node->children) {
                TraversePerkNode(child, set_out, visited);
            }
        };

        /// @brief Gets a unordered_set of all the perks from a given skill \n early return if skill is not part of @ref kPlayableSkills
        /// @param av the skill to get perks to.
        /// @return unordered set with all perks of a specific skill
        static std::unordered_set<RE::BGSPerk*> GetPerksForSkill(RE::ActorValue av)
        {
            std::unordered_set<RE::BGSPerk*> out;
            if (!std::ranges::contains(kPlayableSkills.begin(), kPlayableSkills.end(), av))
                return out;

            std::unordered_set<RE::BGSSkillPerkTreeNode*> visited;
            if (const auto avif = RE::ActorValueList::GetActorValueInfo(av); avif && avif->perkTree)
                TraversePerkNode(avif->perkTree, out, visited);
            return out;
        }

        static std::unordered_set<RE::BGSPerk*> GetAllPlayablePerks()
        {
            return GetPerksForSkills(kPlayableSkills);
        }

        static std::unordered_set<RE::BGSPerk*> GetAllMagicPerks()
        {
            return GetPerksForSkills(kMageSkills);

        }

        static std::unordered_set<RE::BGSPerk*> GetAllThiefPerks()
        {
            return GetPerksForSkills(kThiefSkills);
        }

        static std::unordered_set<RE::BGSPerk*> GetAllWarriorPerks()
        {
            return GetPerksForSkills(kWarriorSkills);
        }
    private:

        static constexpr std::array<RE::ActorValue, 6> kWarriorSkills = {
            RE::ActorValue::kOneHanded, RE::ActorValue::kTwoHanded,
            RE::ActorValue::kHeavyArmor, RE::ActorValue::kArchery,
            RE::ActorValue::kSmithing, RE::ActorValue::kBlock
        };
        static constexpr std::array<RE::ActorValue, 6> kThiefSkills = {
            RE::ActorValue::kSpeech, RE::ActorValue::kAlchemy,
            RE::ActorValue::kLockpicking, RE::ActorValue::kSneak,
            RE::ActorValue::kPickpocket, RE::ActorValue::kLightArmor
        };
        static constexpr std::array<RE::ActorValue, 6> kMageSkills = {
            RE::ActorValue::kAlteration, RE::ActorValue::kConjuration,
            RE::ActorValue::kDestruction, RE::ActorValue::kIllusion,
            RE::ActorValue::kEnchanting, RE::ActorValue::kRestoration
        };

        static std::unordered_set<RE::BGSPerk*> GetPerksForSkills(std::span<const RE::ActorValue> skills)
        {
            std::unordered_set<RE::BGSPerk*> out;
            std::unordered_set<RE::BGSSkillPerkTreeNode*> visited;

            for (const auto av : skills)
            {
                if (const auto avif = RE::ActorValueList::GetActorValueInfo(av); avif && avif->perkTree)
                    TraversePerkNode(avif->perkTree, out, visited);
            }
            return out;
        }

    };
}
