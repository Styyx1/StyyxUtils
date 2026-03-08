//
// Created by styyx on 08/03/2026.
//

#pragma once

namespace StyyxUtil
{
    struct PerkUtil
    {
        static inline std::unordered_set<RE::BGSPerk*> playable_perks;

        static void TraversePerkNode(RE::BGSSkillPerkTreeNode* node,
                                     std::unordered_set<RE::BGSPerk*>& them_perks,
                                     std::unordered_set<RE::BGSSkillPerkTreeNode*>& visited)
        {
            if (!node || visited.contains(node))
                return;

            visited.insert(node);

            if (node->perk) {
                playable_perks.insert(node->perk);
            }

            for (auto* child : node->children) {
                TraversePerkNode(child, them_perks, visited);
            }
        };


        static void BuildPlayablePerks()
        {
            {
                std::unordered_set<RE::BGSSkillPerkTreeNode*> visited;

                const auto avif_destruction = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kDestruction);
                const auto avif_restoration = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kRestoration);
                const auto avif_conjuration = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kConjuration);
                const auto avif_illusion = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kIllusion);
                const auto avif_enchanting = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kEnchanting);
                const auto avif_alteration = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kAlteration);
                const auto avif_onehanded = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kOneHanded);
                const auto avif_twohanded = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kTwoHanded);
                const auto avif_smithing = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kSmithing);
                const auto avif_heavyarmor = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kHeavyArmor);
                const auto avif_archery = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kArchery);
                const auto avif_block = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kBlock);
                const auto avif_pickpocket = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kPickpocket);
                const auto avif_lockpicking = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kLockpicking);
                const auto avif_sneaking = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kSneak);
                const auto avif_lightarmor = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kLightArmor);
                const auto avif_speech = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kSpeech);
                const auto avif_alchemy = RE::ActorValueList::GetActorValueInfo(RE::ActorValue::kAlchemy);

                std::vector avifs = {
                    avif_destruction, avif_restoration, avif_conjuration, avif_illusion,
                    avif_enchanting, avif_alteration, avif_onehanded, avif_twohanded,
                    avif_smithing, avif_heavyarmor, avif_archery, avif_block,
                    avif_pickpocket, avif_lockpicking, avif_sneaking, avif_lightarmor,
                    avif_speech, avif_alchemy
                };

                for (const auto& avif : avifs)
                {
                    if (avif && avif->perkTree)
                    {
                        TraversePerkNode(avif->perkTree, playable_perks, visited);
                    }
                }
            }
        }
    };
}