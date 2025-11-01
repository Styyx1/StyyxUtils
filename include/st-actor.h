#pragma once

namespace StyyxUtil {

	struct ActorUtil {

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

        inline static float GetCurrentLightLevel(RE::Actor* actor)
        {
            auto process = actor->GetHighProcess();
            if (!process) {
                return 0.0f;
            }
            return process->lightLevel;
        }

        inline static float GetCurrentLightLevelPlayer()
        {
			auto player = RE::PlayerCharacter::GetSingleton();
            auto process = player->GetHighProcess();
            if (!process) {
                return 0.0f;
            }
            return process->lightLevel;
		}

        // check if actor starts dead. https://github.com/powerof3/Spell-Perk-Item-Distributor/blob/4972b74819b935b1e443cb4022691ac572785da5/SPID/src/LookupNPC.cpp#L254
        inline static bool StartsDead(const RE::Actor* actor)
        {
            return actor && (actor->formFlags & RE::Actor::RecordFlags::kStartsDead);
        }
		//Get the maximum health of an actor. https://github.com/colinswrath/BladeAndBlunt/blob/2dac82ffa6cd310adc456419930dc3dfb2a372bd/include/Conditions.h#L92
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
            a->RestoreActorValue(RE::ActorValue::kHealth, GetMaxHealth(a));
            a->RestoreActorValue(RE::ActorValue::kStamina, GetMaxStamina(a));
            a->RestoreActorValue(RE::ActorValue::kMagicka, GetMaxMagicka(a));
        }

        static bool ActorHasEffectOfTypeActive(RE::Actor* a_actor, RE::EffectArchetypes::ArchetypeID a_type)
        {
            if (!a_actor) {
                return false;
            }
            auto activeEffects = a_actor->GetActiveEffectList();
            RE::EffectSetting* setting = nullptr;
            if (!activeEffects->empty()) {
                for (RE::ActiveEffect* effect : *activeEffects) {
                    if (effect; !effect->flags.any(RE::ActiveEffect::Flag::kInactive)) {
                        setting = effect ? effect->GetBaseObject() : nullptr;
                        if (setting) {
                            if (setting->HasArchetype(a_type)) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
		}

        static bool HasEffectWithKeywordActive(RE::Actor* a_actor, std::string_view a_keyword) {
            if (!a_actor || a_keyword.empty()) {
                return false;
            }
            auto activeEffects = a_actor->GetActiveEffectList();
            RE::EffectSetting* setting = nullptr;
            if (!activeEffects->empty()) {
                for (RE::ActiveEffect* effect : *activeEffects) {
                    if (effect; !effect->flags.any(RE::ActiveEffect::Flag::kInactive)) {
                        setting = effect ? effect->GetBaseObject() : nullptr;
                        if (setting) {
                            if (setting->HasKeywordString(a_keyword)) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
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

        static void AddItem(RE::Actor* a, RE::TESBoundObject* item, RE::ExtraDataList* extraList, int count, RE::TESObjectREFR* fromRefr)
        {
            using func_t = decltype(AddItem);
            REL::Relocation<func_t> func{ REL::ID(37525) };
            return func(a, item, extraList, count, fromRefr);
        }

        static void AddItemPlayer(RE::TESBoundObject* item, int count)
        {
            return AddItem(RE::PlayerCharacter::GetSingleton(), item, nullptr, count, nullptr);
        }

        static int RemoveItemPlayer(RE::TESBoundObject* item, int count)
        {
            using func_t = decltype(RemoveItemPlayer);
            REL::Relocation<func_t> func{ REL::ID(16919) };
            return func(item, count);
        }

        static int get_item_count(RE::Actor* a, RE::TESBoundObject* item)
        {
            if (auto changes = a->GetInventoryChanges())
            {
                using func_t = int(RE::InventoryChanges*, RE::TESBoundObject*);
                REL::Relocation<func_t> func{ REL::ID(16047) };
                return func(changes, item);
            }
            return 0;
        }

        // Credit: D7ry for getWieldingWeapon in ValhallaCombat
    // https://github.com/D7ry/valhallaCombat/blob/48fb4c3b9bb6bbaa691ce41dbd33f096b74c07e3/src/include/Utils.cpp#L10
        inline static RE::TESObjectWEAP* getWieldingWeapon(RE::Actor* a_actor)
        {
            auto weapon = a_actor->GetAttackingWeapon();
            if (weapon)
            {
                return weapon->object->As<RE::TESObjectWEAP>();
            }
            auto rhs = a_actor->GetEquippedObject(false);
            if (rhs && rhs->IsWeapon())
            {
                return rhs->As<RE::TESObjectWEAP>();
            }
            auto lhs = a_actor->GetEquippedObject(true);
            if (lhs && lhs->IsWeapon())
            {
                return lhs->As<RE::TESObjectWEAP>();
            }

            return nullptr;
        }

        static bool GetMount(RE::Actor* a_actor, RE::ActorPtr* a_mountOut)
        {
            using func_t = decltype(&GetMount);
            REL::Relocation<func_t> func{ REL::ID(38702) };
            return func(a_actor, a_mountOut);
        }

        static inline bool IsPowerAttacking(RE::Actor* actor)
        {
            if (auto high = actor->GetHighProcess())
            {
                if (const auto& attackData = high->attackData)
                {
                    auto flags = attackData->data.flags;

                    if (flags && flags.any(RE::AttackData::AttackFlag::kPowerAttack))
                    {
                        return true;
                    }
                }
            }
            return false;
        }


	};
}