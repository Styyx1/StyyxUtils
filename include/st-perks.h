//
// Created by styyx on 08/03/2026.
//

#pragma once
#include <unordered_set>

namespace StyyxUtil
{
    struct PerkUtil
    {
        static inline std::unordered_set<RE::BGSPerk*> playable_perks;

        static constexpr RE::ActorValue kPlayableSkills[] = {
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

        static std::unordered_set<RE::BGSPerk*> GetPerksForSkill(RE::ActorValue av)
        {
            std::unordered_set<RE::BGSPerk*> out;
            std::unordered_set<RE::BGSSkillPerkTreeNode*> visited;
            if (const auto avif = RE::ActorValueList::GetActorValueInfo(av); avif && avif->perkTree)
                TraversePerkNode(avif->perkTree, out, visited);
            return out;
        }

        static std::unordered_set<RE::BGSPerk*> GetAllPlayablePerks()
        {
            std::unordered_set<RE::BGSPerk*> out;
            std::unordered_set<RE::BGSSkillPerkTreeNode*> visited;
            for (const auto av : kPlayableSkills) {
                if (const auto avif = RE::ActorValueList::GetActorValueInfo(av); avif && avif->perkTree)
                    TraversePerkNode(avif->perkTree, out, visited);
            }
            return out;
        }
    };
}
