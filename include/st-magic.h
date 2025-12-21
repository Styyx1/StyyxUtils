#pragma once

namespace StyyxUtil
{

struct MagicUtil
{
    /// <summary>
    /// Check to see if spell is a playable spell
    /// </summary>
    /// <param name="spell"></param>
    /// <returns></returns>
    static inline bool IsSpellPlayable(RE::SpellItem *spell)
    {
        using st = RE::MagicSystem::SpellType;
        using av = RE::ActorValue;

        auto type = spell->GetSpellType();
        auto skill = spell->GetAssociatedSkill();

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

        return false;
    }

    /// <summary>
    /// Check if a MagicItem is permanent
    /// Credits: KernalsEgg for ApplySpell and IsPermanent
    /// [Blade and Blunt by colinswrath](https://github.com/colinswrath/BladeAndBlunt/blob/2dac82ffa6cd310adc456419930dc3dfb2a372bd/include/Conditions.h#L102)
    /// </summary>
    /// <param name="item"></param>
    /// <returns></returns>

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
    /// <summary>
    /// Apply spell from caster to target. Either adds it if the spell is permanent or casts it
    /// Credits: KernalsEgg for ApplySpell and IsPermanent
    /// [Blade and Blunt by colinswrath](https://github.com/colinswrath/BladeAndBlunt/blob/2dac82ffa6cd310adc456419930dc3dfb2a372bd/include/Conditions.h#L102)
    /// </summary>
    /// <param name="caster"></param>
    /// <param name="target"></param>
    /// <param name="spell"></param>
    inline static void ApplySpell(RE::Actor *caster, RE::Actor *target, RE::SpellItem *spell)
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
} // namespace StyyxUtil
