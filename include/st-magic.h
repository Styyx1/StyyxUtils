#pragma once

namespace StyyxUtil {

    struct MagicUtil {
        static bool IsPermanent(RE::MagicItem* item)
        {
            switch (item->GetSpellType()){
            case RE::MagicSystem::SpellType::kDisease:
            case RE::MagicSystem::SpellType::kAbility:
            case RE::MagicSystem::SpellType::kAddiction:
                return true;            
            default: 
                return false;
            }
        }

        inline static void ApplySpell(RE::Actor* caster, RE::Actor* target, RE::SpellItem* spell)
        {
            if (IsPermanent(spell)) {
                target->AddSpell(spell);
            }
            else {
                caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(spell, false, target, 1.0F, false, 0.0F, nullptr);
            }
        }
    };
}