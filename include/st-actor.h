#pragma once

namespace StyyxUtil
{

struct ActorUtil
{
    inline static bool IsInOpportunityState(RE::Actor *victim, RE::Actor *attacker)
    {
        return IsPowerAttacking(victim) || victim->IsStaggering() ||
               victim->actorState1.sitSleepState == RE::SIT_SLEEP_STATE::kIsSitting ||
               victim->actorState1.sitSleepState == RE::SIT_SLEEP_STATE::kIsSleeping ||
               (victim->GetHeadingAngle(attacker->GetPosition(), false) <= -135 ||
                victim->GetHeadingAngle(attacker->GetPosition(), false) >= 135) ||
               ActorHasEffectOfTypeActive(victim, RE::EffectArchetypes::ArchetypeID::kParalysis) ||
               ActorHasEffectOfTypeActive(victim, RE::EffectArchetypes::ArchetypeID::kCalm);
    }    

    inline static float GetInventoryWeight(RE::Actor *actor)
    {
        return actor->GetActorValue(RE::ActorValue::kInventoryWeight);
    }

    inline static float GetMassFromInventory(RE::Actor *actor)
    {
        if (!actor)
            return 1.0f;

        float invWeight = actor->GetEquippedWeight() ? actor->GetEquippedWeight() : 1.0f;
        const float maxInvWeight = 800.0f;
        float weightRatio = std::min(invWeight / maxInvWeight, 1.0f);
        float mass = 1.0f + weightRatio * (80.0f - 1.0f);

        return mass;
    }

    inline static bool ActorHasQuestObjectInHand(RE::Actor *actor)
    {
        if (actor)
        {
            auto *rightHandItem = actor->GetEquippedEntryData(false);
            if (rightHandItem)
            {
                if (rightHandItem->IsQuestObject())
                {
                    return true;
                }
            }

            auto *leftHandItem = actor->GetEquippedEntryData(true);
            if (leftHandItem)
            {
                if (leftHandItem->IsQuestObject())
                {
                    return true;
                }
            }
        }
        return false;
    };

    inline static bool IsVampire(RE::Actor *a_ref)
    {
        if (a_ref->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordVampire))
        {
            return true;
        }
        return false;
    }

    inline static bool IsUndead(RE::Actor *a_ref)
    {
        if (a_ref->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordUndead))
            return true;
        return false;
    }

    inline static bool IsDragon(RE::Actor *a_ref)
    {
        if (a_ref->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordDragon))
        {
            return true;
        }
        auto key = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("ActorTypeDragon");
        if (!key)
            return false;
        if (a_ref->HasKeyword(key))
        {
            return true;
        }

        return false;
    }

    inline static RE::TESObjectCELL *GetPlayerCell(RE::PlayerCharacter *player)
    {
        auto cell = player->GetParentCell();
        if (!cell)
        {
            cell = player->GetSaveParentCell();
        }
        if (!cell)
        {
            return nullptr;
        }
        return cell;
    }

    inline static float GetCurrentLightLevel(RE::Actor *actor)
    {
        auto process = actor->GetHighProcess();
        if (!process)
        {
            return 0.0f;
        }
        return process->lightLevel;
    }

    inline static float GetCurrentLightLevelPlayer()
    {
        auto player = RE::PlayerCharacter::GetSingleton();
        auto process = player->GetHighProcess();
        if (!process)
        {
            return 0.0f;
        }
        return process->lightLevel;
    }

    // check if actor starts dead.
    // https://github.com/powerof3/Spell-Perk-Item-Distributor/blob/4972b74819b935b1e443cb4022691ac572785da5/SPID/src/LookupNPC.cpp#L254
    inline static bool StartsDead(const RE::Actor *actor)
    {
        return actor && (actor->formFlags & RE::Actor::RecordFlags::kStartsDead);
    }
    // Get the maximum health of an actor.
    // https://github.com/colinswrath/BladeAndBlunt/blob/2dac82ffa6cd310adc456419930dc3dfb2a372bd/include/Conditions.h#L92
    inline static float GetMaxHealth(RE::Actor *a_actor)
    {
        return a_actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kHealth) +
               a_actor->GetPermanentActorValue(RE::ActorValue::kHealth);
    }

    inline static float GetMaxStamina(RE::Actor *actor)
    {
        return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kStamina) +
               actor->GetPermanentActorValue(RE::ActorValue::kStamina);
    }

    inline static float GetMaxMagicka(RE::Actor *actor)
    {
        return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kMagicka) +
               actor->GetPermanentActorValue(RE::ActorValue::kMagicka);
    }

    inline static void FullyHealActor(RE::Actor *a)
    {
        a->RestoreActorValue(RE::ActorValue::kHealth, GetMaxHealth(a));
        a->RestoreActorValue(RE::ActorValue::kStamina, GetMaxStamina(a));
        a->RestoreActorValue(RE::ActorValue::kMagicka, GetMaxMagicka(a));
    }

    static bool ActorHasEffectOfTypeActive(RE::Actor *a_actor, RE::EffectArchetypes::ArchetypeID a_type)
    {
        if (!a_actor)
        {
            return false;
        }
        auto activeEffects = a_actor->GetActiveEffectList();
        RE::EffectSetting *setting = nullptr;
        if (!activeEffects->empty())
        {
            for (RE::ActiveEffect *effect : *activeEffects)
            {
                if (effect; !effect->flags.any(RE::ActiveEffect::Flag::kInactive))
                {
                    setting = effect ? effect->GetBaseObject() : nullptr;
                    if (setting)
                    {
                        if (setting->HasArchetype(a_type))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    static bool HasEffectWithKeywordActive(RE::Actor *a_actor, std::string_view a_keyword)
    {
        if (!a_actor || a_keyword.empty())
        {
            return false;
        }
        auto activeEffects = a_actor->GetActiveEffectList();
        RE::EffectSetting *setting = nullptr;
        if (!activeEffects->empty())
        {
            for (RE::ActiveEffect *effect : *activeEffects)
            {
                if (effect; !effect->flags.any(RE::ActiveEffect::Flag::kInactive))
                {
                    setting = effect ? effect->GetBaseObject() : nullptr;
                    if (setting)
                    {
                        if (setting->HasKeywordString(a_keyword))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    static bool IsEffectActive(RE::Actor *a_actor, RE::EffectSetting *a_effect)
    {
        if (!a_actor || !a_effect)
        {
            return false;
        }
        auto activeEffects = a_actor->GetActiveEffectList();
        RE::EffectSetting *setting = nullptr;
        if (!activeEffects->empty())
        {
            for (RE::ActiveEffect *effect : *activeEffects)
            {
                if (effect; !effect->flags.any(RE::ActiveEffect::Flag::kInactive))
                {
                    setting = effect ? effect->GetBaseObject() : nullptr;
                    if (setting)
                    {
                        if (setting == a_effect)
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    static void AddItem(RE::Actor *a, RE::TESBoundObject *item, RE::ExtraDataList *extraList, int count,
                        RE::TESObjectREFR *fromRefr)
    {
        using func_t = decltype(AddItem);
        REL::Relocation<func_t> func{REL::ID(37525)};
        return func(a, item, extraList, count, fromRefr);
    }

    static void AddItemPlayer(RE::TESBoundObject *item, int count)
    {
        return AddItem(RE::PlayerCharacter::GetSingleton(), item, nullptr, count, nullptr);
    }

    static int RemoveItemPlayer(RE::TESBoundObject *item, int count)
    {
        using func_t = decltype(RemoveItemPlayer);
        REL::Relocation<func_t> func{REL::ID(16919)};
        return func(item, count);
    }

    static int get_item_count(RE::Actor *a, RE::TESBoundObject *item)
    {
        if (auto changes = a->GetInventoryChanges())
        {
            using func_t = int(RE::InventoryChanges *, RE::TESBoundObject *);
            REL::Relocation<func_t> func{REL::ID(16047)};
            return func(changes, item);
        }
        return 0;
    }

    // Credit: D7ry for getWieldingWeapon in ValhallaCombat
    // https://github.com/D7ry/valhallaCombat/blob/48fb4c3b9bb6bbaa691ce41dbd33f096b74c07e3/src/include/Utils.cpp#L10
    inline static RE::TESObjectWEAP *getWieldingWeapon(RE::Actor *a_actor)
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

    static bool GetMount(RE::Actor *a_actor, RE::ActorPtr *a_mountOut)
    {
        using func_t = decltype(&GetMount);
        REL::Relocation<func_t> func{REL::ID(38702)};
        return func(a_actor, a_mountOut);
    }

    static inline bool IsPowerAttacking(RE::Actor *actor)
    {
        if (auto high = actor->GetHighProcess())
        {
            if (const auto &attackData = high->attackData)
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

    // tried it with ActorSetLevel from below but that does not calculate the stats
    static inline void SetNPCLevel(RE::Actor *actor, uint16_t level)
    {
        const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
        const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
        script->SetCommand(std::format("SetLevel {}", level));
        script->CompileAndRun(actor);
    }

    template <auto FuncID, typename Ret, typename... Args> static inline Ret FuncCall(Args... args)
    {
        using func_t = Ret (*)(Args...);
        REL::Relocation<func_t> target{REL::ID(FuncID)};
        return target(std::forward<Args>(args)...);
    }

    // can set the level but doesn't calculate stats other than the consolde command
    static inline void ActorSetLevel(RE::TESActorBaseData *a_actor, int a_level)
    {
        return FuncCall<14385, void>(a_actor, a_level);
    }

    // returns from 0 - 1.0 1 == 100%
    static float GetActorValuePercentage(RE::Actor* a_actor, RE::ActorValue a_av)
    { return FuncCall<37337, float>(a_actor, a_av);
    }

};

} // namespace StyyxUtil
