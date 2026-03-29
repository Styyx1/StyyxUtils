#pragma once

namespace StyyxUtil
{
    struct MagicUtil
    {
        /// @brief Check if spell is self targeting
        /// @param a_spell The spell to check
        /// @return true if the spell is self targeting
        static bool IsSelfTargetSpell(RE::MagicItem* a_spell)
        {
            if (!a_spell)
                return false;
            return a_spell->GetDelivery() == RE::MagicSystem::Delivery::kSelf;
        }

        /// @brief Check if a spell is playable, as in, able to be cast
        /// @param spell The spell to check
        /// @return True if spell is a castable spell
        static bool IsSpellPlayable(const RE::SpellItem *spell)
        {
            using st = RE::MagicSystem::SpellType;
            using av = RE::ActorValue;

            const auto type = spell->GetSpellType();
            const auto skill = spell->GetAssociatedSkill();

            switch (type)
            {
            case st::kStaffEnchantment:
            case st::kScroll:
            case st::kSpell:
            case st::kLeveledSpell:
            case st::kVoicePower:
            case st::kLesserPower:
            case st::kPower:
                break;

            default:
                return false;
            }
            switch (skill)
            {
            case av::kAlteration:
            case av::kDestruction:
            case av::kConjuration:
            case av::kIllusion:
            case av::kRestoration:
                return true;
            default:
                return false;
            }
        }

        /// @brief Check if a magic item is permanent
        /// @param item The magic item. Also accepts SpellItem
        /// @return True if spell is Disease, Ability or Addiction
        /// @note Credits: KernalsEgg for ApplySpell and IsPermanent \n [Blade and Blunt by colinswrath](https://github.com/colinswrath/BladeAndBlunt/blob/2dac82ffa6cd310adc456419930dc3dfb2a372bd/include/Conditions.h#L102)
        static bool IsPermanent(RE::MagicItem *item)
        {
            switch (item->GetSpellType())
            {
            case RE::MagicSystem::SpellType::kDisease:
            case RE::MagicSystem::SpellType::kAbility:
            case RE::MagicSystem::SpellType::kAddiction:
                return true;
            default:
                return false;
            }
        }

        /// @brief Casts Spell from caster to actor. If the spell is permanent (@ref MagicUtil::IsPermanent) it adds the spell
        /// @param caster The Actor casting the spell
        /// @param target The Target for the spell
        /// @param spell The spell being cast
        static void ApplySpell(RE::Actor *caster, RE::Actor *target, RE::SpellItem *spell)
        {
            if (IsPermanent(spell))
            {
                target->AddSpell(spell);
            }
            else
            {
                caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)
                    ->CastSpellImmediate(spell, false, target, 1.0F, false, 0.0F, nullptr);
            }
        }
    };
}
