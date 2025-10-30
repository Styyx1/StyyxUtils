#pragma once

namespace Util {

    struct Randomiser
    {
        static std::mt19937& GetRNG()
        {
            static std::mt19937 gen(std::random_device{}());
            return gen;
        }

        static int GetRandomInt(int a_min, int a_max)
        {
            std::uniform_int_distribution<int> distrib(a_min, a_max);
            return distrib(GetRNG());
        }

        static float GetRandomFloat(float a_min, float a_max)
        {
            std::uniform_real_distribution<float> distrib(a_min, a_max);
            return distrib(GetRNG());
        }

        static float GetRoundedFloat(float a_min, float a_max, int decimals = 2)
        {
            auto value = GetRandomFloat(a_min, a_max);
            float factor = std::pow(10.0f, static_cast<float>(decimals));
            return std::round(value * factor) / factor;
        }
    };

	struct Actor {

        inline static RE::TESObjectCELL* GetPlayerCell(RE::PlayerCharacter* player)
        {
            auto cell = player->GetParentCell();
            if (!cell) {
                cell = player->GetSaveParentCell();
            }
            if (!cell) {
                return nullptr;
            }
			return cell;
        }

        inline static float GetMaxHealth(RE::Actor* a_actor){
            return a_actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kHealth) + a_actor->GetPermanentActorValue(RE::ActorValue::kHealth);
        }

        inline static float GetMaxStamina(RE::Actor* actor)
        {
            return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kStamina) + actor->GetPermanentActorValue(RE::ActorValue::kStamina);
        }

        inline static float GetMaxMagicka(RE::Actor* actor) {
            return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kMagicka) + actor->GetPermanentActorValue(RE::ActorValue::kMagicka);
        }

        inline static void FullyHealActor(RE::Actor* a) {
            a->RestoreActorValue(RE::ActorValue::kHealth, Util::Actor::GetMaxHealth(a));
            a->RestoreActorValue(RE::ActorValue::kStamina, Util::Actor::GetMaxStamina(a));
            a->RestoreActorValue(RE::ActorValue::kMagicka, Util::Actor::GetMaxMagicka(a));
        }

        static bool IsEffectActive(RE::Actor* a_actor, RE::EffectSetting* a_effect)
        {
            if (!a_actor || !a_effect) {
                return false;
            }
            auto activeEffects = a_actor->GetActiveEffectList();
            RE::EffectSetting* setting = nullptr;
            if (!activeEffects->empty()) {
                for (RE::ActiveEffect* effect : *activeEffects) {
                    if (effect; !effect->flags.any(RE::ActiveEffect::Flag::kInactive)) {
                        setting = effect ? effect->GetBaseObject() : nullptr;
                        if (setting) {
                            if (setting == a_effect) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }


	};

    struct Cells {

    };

    struct Magic {
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