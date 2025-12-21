#pragma once

namespace StyyxUtil
{

struct ActorUtil
{
    /// barely useful here but used in one of my mods
    /// this is true for the next 3 functions actuallly
    
    /// <summary>
    /// Gets the state in which an attack of opportunity is possible
    /// </summary>
    /// <param name="victim"></param>
    /// <param name="attacker"></param>
    /// <returns></returns>
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

    /// <summary>
    /// Helper Function to Get the current inventory weight of an actor
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    inline static float GetInventoryWeight(RE::Actor *actor)
    {
        return actor->GetActorValue(RE::ActorValue::kInventoryWeight);
    }

    /// <summary>
    /// used for a mass affects inventory weight calculation
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
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

    /// <summary>
    /// Checks if the equipped weapon of the actor is a quest item
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
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
    /// <summary>
    /// Check if actor is a vampire
    /// </summary>
    /// <param name="a_ref"></param>
    /// <returns></returns>
    inline static bool IsVampire(RE::Actor *a_ref)
    {
        if (a_ref->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordVampire))
        {
            return true;
        }
        return false;
    }

    /// <summary>
    /// check if actor is Undead
    /// </summary>
    /// <param name="a_ref"></param>
    /// <returns></returns>
    inline static bool IsUndead(RE::Actor *a_ref)
    {
        if (a_ref->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordUndead))
            return true;
        return false;
    }

    /// <summary>
    /// Check if actor is a dragon
    /// Note, the Default Object in skyrim.esm is empty for that
    /// https://www.nexusmods.com/skyrimspecialedition/mods/163540 is a mod that fixes this
    /// Here we do a manual lookup in case the default object is null
    /// </summary>
    /// <param name="a_ref"></param>
    /// <returns></returns>
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

    /// <summary>
    /// Get player cell and if parent cell is null, GetSaveParentCell
    /// </summary>
    /// <param name="player"></param>
    /// <returns></returns>
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

    /// <summary>
    /// Get light level of actor
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    inline static float GetCurrentLightLevel(RE::Actor *actor)
    {
        auto process = actor->GetHighProcess();
        if (!process)
        {
            return 0.0f;
        }
        return process->lightLevel;
    }

    /// <summary>
    /// Get light level of player
    /// convenience function
    /// </summary>
    /// <returns></returns>
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

    //Credits: https://github.com/doodlum/skyrim-poise/blob/daf1344ebe667d34154213ab9fb61d0d27452b0d/src/Hooks/PoiseAV.h#L110    
    /// <summary>
    /// Try to stagger actor.
    ///  a_aggressor can be nullptr
    /// </summary>
    /// <param name="a_actor"></param>
    /// <param name="mult"></param>
    /// <param name="a_aggressor"></param>
    inline static void TryStagger(RE::Actor* a_actor, float mult, RE::Actor* a_aggressor) {
        return FuncCall<37710, void>(a_actor, mult, a_aggressor);
    }


    // https://github.com/powerof3/Spell-Perk-Item-Distributor/blob/4972b74819b935b1e443cb4022691ac572785da5/SPID/src/LookupNPC.cpp#L254
    /// <summary>
    /// Check if actor has the Starts Dead flag
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    inline static bool StartsDead(const RE::Actor *actor)
    {
        return actor && (actor->formFlags & RE::Actor::RecordFlags::kStartsDead);
    }

    // https://github.com/colinswrath/BladeAndBlunt/blob/2dac82ffa6cd310adc456419930dc3dfb2a372bd/include/Conditions.h#L92    
    /// <summary>
    /// Gets Maximum Health of an actor, including current modifiers
    /// </summary>
    /// <param name="a_actor"></param>
    /// <returns></returns>
    inline static float GetMaxHealth(RE::Actor *a_actor)
    {
        return a_actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kHealth) +
               a_actor->GetPermanentActorValue(RE::ActorValue::kHealth);
    }
    /// <summary>
    /// Gets Maximum Stamina of an actor, including current modifiers
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    inline static float GetMaxStamina(RE::Actor *actor)
    {
        return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kStamina) +
               actor->GetPermanentActorValue(RE::ActorValue::kStamina);
    }
    /// <summary>
    /// Gets Maximum Magicka of an actor, including current modifiers
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    inline static float GetMaxMagicka(RE::Actor *actor)
    {
        return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kMagicka) +
               actor->GetPermanentActorValue(RE::ActorValue::kMagicka);
    }
    /// <summary>
    /// fully heal all 3 attributes of an actor
    /// </summary>
    /// <param name="a"></param>
    inline static void FullyHealActor(RE::Actor *a)
    {
        a->RestoreActorValue(RE::ActorValue::kHealth, GetMaxHealth(a));
        a->RestoreActorValue(RE::ActorValue::kStamina, GetMaxStamina(a));
        a->RestoreActorValue(RE::ActorValue::kMagicka, GetMaxMagicka(a));
    }
    /// <summary>
    /// Check if actor has any spell of a specific archetype active
    /// </summary>
    /// <param name="a_actor"></param>
    /// <param name="a_type"></param>
    /// <returns></returns>
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
    /// <summary>
    /// Check if actor has any effect with keyword active
    /// </summary>
    /// <param name="a_actor"></param>
    /// <param name="a_keyword"></param>
    /// <returns></returns>
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
    /// <summary>
    /// Check if actor has a specific effect active
    /// </summary>
    /// <param name="a_actor"></param>
    /// <param name="a_effect"></param>
    /// <returns></returns>
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
    /// <summary>
    /// Add Item function. Adds item to the actor
    /// </summary>
    /// <param name="a"></param>
    /// <param name="item"></param>
    /// <param name="extraList"></param>
    /// <param name="count"></param>
    /// <param name="fromRefr"></param>
    static void AddItem(RE::Actor *a, RE::TESBoundObject *item, RE::ExtraDataList *extraList, int count,
                        RE::TESObjectREFR *fromRefr)
    {
        using func_t = decltype(AddItem);
        REL::Relocation<func_t> func{REL::ID(37525)};
        return func(a, item, extraList, count, fromRefr);
    }
    /// <summary>
    /// Helper function to add item to the player. AddItem with fille actor parameter
    /// </summary>
    /// <param name="item"></param>
    /// <param name="count"></param>
    static void AddItemPlayer(RE::TESBoundObject *item, int count)
    {
        return AddItem(RE::PlayerCharacter::GetSingleton(), item, nullptr, count, nullptr);
    }
    /// <summary>
    /// remove item from the player
    /// </summary>
    /// <param name="item"></param>
    /// <param name="count"></param>
    /// <returns></returns>
    static int RemoveItemPlayer(RE::TESBoundObject *item, int count)
    {
        using func_t = decltype(RemoveItemPlayer);
        REL::Relocation<func_t> func{REL::ID(16919)};
        return func(item, count);
    }

    /// <summary>
    /// Check if any actor has a specific item in their inventory
    /// </summary>
    /// <param name="actor"></param>
    /// <param name="item"></param>
    /// <returns></returns>
    static bool ActorHasItem(RE::Actor* actor, RE::TESBoundObject* item) {
        if (!actor || !item)
            return false;

        for (auto& object : actor->GetInventory()) {
            if (object.first == item && object.second.first > 0) {
                return true;
            }
        }
        return false;
    }

    // Credit: D7ry for getWieldingWeapon in ValhallaCombat
    // https://github.com/D7ry/valhallaCombat/blob/48fb4c3b9bb6bbaa691ce41dbd33f096b74c07e3/src/include/Utils.cpp#L10

    /// <summary>
    /// Gets the weapon the actor is wielding
    /// </summary>
    /// <param name="a_actor"></param>
    /// <returns></returns>

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

    /// <summary>
    /// Gets the mount of an actor
    /// </summary>
    /// <param name="a_actor"></param>
    /// <param name="a_mountOut"></param>
    /// <returns></returns>
    static bool GetMount(RE::Actor *a_actor, RE::ActorPtr *a_mountOut)
    {
        using func_t = decltype(&GetMount);
        REL::Relocation<func_t> func{REL::ID(38702)};
        return func(a_actor, a_mountOut);
    }

    /// <summary>
    /// Gets the player mount
    /// </summary>
    /// <param name="player"></param>
    /// <returns></returns>
    static inline RE::Actor* GetPlayerMount(RE::PlayerCharacter* player)
    {
        RE::NiPointer<RE::Actor> currentMount;
        if (player->GetMount(currentMount)) {
            return currentMount.get();
        }
        return nullptr;
    }
    /// <summary>
    /// Check if actor is power attacking
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
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
    /// <summary>
    /// check if actor is bash attacking
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    static inline bool IsBashing(RE::Actor* actor) {
        if (auto high = actor->GetHighProcess(); high) {
            if (actor->GetAttackState() == RE::ATTACK_STATE_ENUM::kNone)
                return false;

            if (const auto& attackData = high->attackData; attackData) {
                auto flags = attackData->data.flags;
                if (flags && flags.any(RE::AttackData::AttackFlag::kBashAttack)) {
                    return true;
                }
            }
        }
        return false;
    }

    //Credits: https://github.com/powerof3/PapyrusExtenderSSE/

    /// <summary>
    /// Get a vector of nearby actors
    /// </summary>
    /// <param name="a_ref"></param>
    /// <param name="a_radius"></param>
    /// <param name="a_ignorePlayer"></param>
    /// <returns></returns>
    inline static std::vector<RE::Actor*> GetNearbyActors(RE::TESObjectREFR* a_ref, float a_radius, bool a_ignorePlayer)
    {
        {
            std::vector<RE::Actor*> result;
            if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
                if (a_ignorePlayer && processLists->numberHighActors == 0) {
                    return result;
                }

                const auto squaredRadius = a_radius * a_radius;
                const auto originPos = a_ref->GetPosition();

                result.reserve(processLists->numberHighActors);

                const auto get_actor_within_radius = [&](RE::Actor* a_actor) {
                    if (a_actor && a_actor != a_ref && originPos.GetSquaredDistance(a_actor->GetPosition()) <= squaredRadius) {
                        result.emplace_back(a_actor);
                    }
                    };
                for (auto& actorHandle : processLists->highActorHandles) {
                    const auto actor = actorHandle.get();
                    get_actor_within_radius(actor.get());
                }

                if (!a_ignorePlayer) {
                    get_actor_within_radius(RE::PlayerCharacter::GetSingleton());
                }

                if (!result.empty()) {
                    return result;
                }
            }
            return result;
        }
    }

    /// <summary>
    /// runs the console command SetLevel
    /// We use the console command cause that one also levels up the stats of the npc
    /// </summary>
    /// <param name="actor"></param>
    /// <param name="level"></param>
    static inline void SetNPCLevel(RE::Actor *actor, uint16_t level)
    {
        const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
        const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
        script->SetCommand(std::format("SetLevel {}", level));
        script->CompileAndRun(actor);
    }    

    template <auto FuncID, typename Ret, typename... Args> static inline Ret FuncCall(Args... args)
    {
        using func_t = Ret(*)(Args...);
        REL::Relocation<func_t> target{ REL::ID(FuncID) };
        return target(std::forward<Args>(args)...);
    }

    // can set the level but doesn't calculate stats other than the consolde command
    static inline void ActorSetLevel(RE::TESActorBaseData *a_actor, int a_level)
    {
        return FuncCall<14385, void>(a_actor, a_level);
    }

    /// <summary>
    /// Same as the condition function in the CK.    
    /// returns from 0 - 1.0.     
    /// 1 == 100%.    
    /// </summary>
    /// <param name="a_actor"></param>
    /// <param name="a_av"></param>
    /// <returns></returns>
    static float GetActorValuePercentage(RE::Actor* a_actor, RE::ActorValue a_av)
    { 
        return FuncCall<37337, float>(a_actor, a_av);
    }
    

};

} // namespace StyyxUtil
