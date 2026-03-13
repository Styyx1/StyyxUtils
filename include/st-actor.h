#pragma once
#include <vector>

namespace StyyxUtil
{

struct ActorUtil
{
    /// @brief Fills a vector<RE::BGSPerk*> reference with all the perks an actor inherits from the actor base
    /// @param a_actor Actor which the perks are gotten from
    /// @param perks vector reference all the perks are added to
    static void GetPerksFromBaseActor(RE::Actor* a_actor, std::vector<RE::BGSPerk*>& perks)
    {
        if (!a_actor)
            return;

        const auto base = a_actor->GetActorBase();
        if (!base)
            return;

        const uint32_t perk_count = base->perkCount;
        for (uint32_t i = 0; i < perk_count; i++)
        {
            RE::BGSPerk* perk = base->perks[i].perk;
            if (!perk)
                continue;
            perks.push_back(perk);
        }
    }

    /// @brief Check if an actor has any heavy armor equipped. It returning false does not mean the actor has light armor equipped
    /// @param actor Actor to check
    /// @return returns true if the actor has any heavy armor equipped
    static bool ActorHasEquippedHeavyArmor(RE::Actor *actor)
    {
        if (!actor)
            return false;
        const auto proc = actor->currentProcess;
        if (!proc)
            return false;

        for (auto& [object, slot] : proc->equippedForms)
        {
            if (object)
            {
                if (const auto armor = object->As<RE::TESObjectARMO>())
                {
                    if (armor->IsHeavyArmor())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    /// @brief Check if an actor has any light armor equipped. It returning false does not mean the actor has heavy armor equipped
    /// @param actor Actor to check
    /// @return returns true if the actor has any light armor equipped
    static bool ActorHasEquippedLightArmor(const RE::Actor *actor)
    {
        if (!actor)
            return false;
        const auto proc = actor->currentProcess;
        if (!proc)
            return false;

        for (auto& [object, slot] : proc->equippedForms)
        {
            if (object)
            {
                if (const auto armor = object->As<RE::TESObjectARMO>())
                {
                    if (!armor->IsHeavyArmor())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /// @brief Very specific function used to see if an Actor is in a state an attack of opportunity should be possible
    /// @param victim The actor being attacked
    /// @param attacker The attacking Actor
    /// @return True if Actor is in a state an attack of opportunity should be possible
    static bool IsInOpportunityState(RE::Actor *victim, const RE::Actor *attacker)
    {
        return IsPowerAttacking(victim) || victim->IsStaggering() ||
               victim->actorState1.sitSleepState == RE::SIT_SLEEP_STATE::kIsSitting ||
               victim->actorState1.sitSleepState == RE::SIT_SLEEP_STATE::kIsSleeping ||
               (victim->GetHeadingAngle(attacker->GetPosition(), false) <= -135 ||
                victim->GetHeadingAngle(attacker->GetPosition(), false) >= 135) ||
               ActorHasEffectOfTypeActive(victim, RE::EffectArchetypes::ArchetypeID::kParalysis) ||
               ActorHasEffectOfTypeActive(victim, RE::EffectArchetypes::ArchetypeID::kCalm);
    }

    /// @brief Check if actor has Quest item as weapon
    /// @param actor The actor to check the equipped item of
    /// @return True if the actor has a quest item equipped
    static bool ActorHasQuestObjectInHand(RE::Actor *actor)
    {
        if (actor)
        {
            if (const auto *rightHandItem = actor->GetEquippedEntryData(false))
            {
                if (rightHandItem->IsQuestObject())
                {
                    return true;
                }
            }

            if (const auto *leftHandItem = actor->GetEquippedEntryData(true))
            {
                if (leftHandItem->IsQuestObject())
                {
                    return true;
                }
            }
        }
        return false;
    };

    /// @brief Check if actor is vampire
    /// @param a_ref Actor to check
    /// @return True if actor has the default object keyword for vampires
    static bool IsVampire(RE::Actor *a_ref)
    {
        if (a_ref->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordVampire))
        {
            return true;
        }
        return false;
    }

    /// @brief Check if actor is undead
    /// @param a_ref Actor to check
    /// @return True if actor has the default object keyword for undead
    static bool IsUndead(RE::Actor *a_ref)
    {
        if (a_ref->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordUndead))
            return true;
        return false;
    }

    /// @brief Check if actor is a dragon
    /// @param a_actor The actor to check
    /// @return True if actor has the Dragon keyword
    /// @note the Default Object in skyrim.esm is empty for that \n
    /// [This](https://www.nexusmods.com/skyrimspecialedition/mods/163540) is a mod that fixes this \n
    ///Here we do a manual lookup in case the default object is null
    static bool IsDragon(const RE::Actor *a_actor)
    {
        if (a_actor->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordDragon))
        {
            return true;
        }
        const auto key = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("ActorTypeDragon");
        if (!key)
            return false;
        return a_actor->HasKeyword(key);
    }


    /// @brief Get the current cell the player is in
    /// @return The current cell the player is in or nullptr if it can't be found
    static RE::TESObjectCELL *GetPlayerCell()
    {
        const auto player = RE::PlayerCharacter::GetSingleton();

        auto cell = player->GetParentCell();
        if (!cell)
        {
            cell = player->GetSaveParentCell();
        }
        return cell;
    }

    /// @brief Get the current light level the actor is standing in
    /// @param a_actor The actor to check
    /// @return The current light level or 0.0 if the actor process can't be found
    static float GetCurrentLightLevel(const RE::Actor *a_actor)
    {
        if (!a_actor)
            return 0.0f;

        const auto process = a_actor->GetHighProcess();
        return process ? process->lightLevel : 0.0f;
    }

    /// @brief Get the light level the player is standing in
    /// @return @ref GetCurrentLightLevel() for the player
    static float GetCurrentLightLevelPlayer()
    {
        const auto player = RE::PlayerCharacter::GetSingleton();
        return GetCurrentLightLevel(player);
    }

    /// @brief Try to stagger a target
    /// @param a_target The target to stagger
    /// @param a_staggerMult The stagger multiplier
    /// @param a_aggressor The attacker
    /// @note Credits: [Chocolate Poise by doodlez ](https://github.com/doodlum/skyrim-poise/blob/daf1344ebe667d34154213ab9fb61d0d27452b0d/src/Hooks/PoiseAV.h#L110)

    static void TryStagger(RE::Actor* a_target, float a_staggerMult, RE::Actor* a_aggressor) {
        using func_t = decltype(&TryStagger);
        static REL::Relocation<func_t> func{ RELOCATION_ID(36700, 37710) };
        func(a_target, a_staggerMult, a_aggressor);
    }

    /// @brief Check if actor is supposed to spawn dead
    /// @param actor The Actor to check
    /// @return True if actor has the Start Dead flag set
    /// @note  Credits: [SPID by PO3](https://github.com/powerof3/Spell-Perk-Item-Distributor/blob/4972b74819b935b1e443cb4022691ac572785da5/SPID/src/LookupNPC.cpp#L254)

    static bool StartsDead(const RE::Actor *actor)
    {
        return actor && (actor->formFlags & RE::Actor::RecordFlags::kStartsDead);
    }


    /// @brief Get maximum Health of an actor
    /// @param a_actor The actor to check
    /// @return The maximum health including temporary modifiers
    /// @note Credits: [Blade and Blunt by colinswrath](https://github.com/colinswrath/BladeAndBlunt/blob/2dac82ffa6cd310adc456419930dc3dfb2a372bd/include/Conditions.h#L92 )

    static float GetMaxHealth(RE::Actor *a_actor)
    {
        return a_actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kHealth) +
               a_actor->GetPermanentActorValue(RE::ActorValue::kHealth);
    }

    /// @brief Get maximum Stamina of an actor
    /// @param actor The actor to check
    /// @return The maximum Stamina including temporary modifiers
    static float GetMaxStamina(RE::Actor *actor)
    {
        return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kStamina) +
               actor->GetPermanentActorValue(RE::ActorValue::kStamina);
    }

    /// @brief Get maximum Magicka of an actor
    /// @param actor The actor to check
    /// @return The maximum Magicka including temporary modifiers
    static float GetMaxMagicka(RE::Actor *actor)
    {
        return actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, RE::ActorValue::kMagicka) +
               actor->GetPermanentActorValue(RE::ActorValue::kMagicka);
    }

    /// @brief Fully heals all 3 attributes of an actor
    /// @param a_actor The actor to heal
    static void FullyHealActor(RE::Actor *a_actor)
    {
        a_actor->RestoreActorValue(RE::ActorValue::kHealth, GetMaxHealth(a_actor));
        a_actor->RestoreActorValue(RE::ActorValue::kStamina, GetMaxStamina(a_actor));
        a_actor->RestoreActorValue(RE::ActorValue::kMagicka, GetMaxMagicka(a_actor));
    }

    /// @brief Check if actor has an effect of a specific type active
    /// @param a_actor The actor to check
    /// @param a_type The Effect archetype needed
    /// @return True if actor has an active effect with the set type
    static bool ActorHasEffectOfTypeActive(RE::Actor *a_actor, RE::EffectArchetypes::ArchetypeID a_type)
    {
        if (!a_actor)
            return false;

        const auto& activeEffects = a_actor->GetActiveEffectList();
        if (!activeEffects)
            return false;

        return std::ranges::any_of(*activeEffects, [a_type](const RE::ActiveEffect* effect) -> bool
        {
            if (!effect || effect->flags.any(RE::ActiveEffect::Flag::kInactive)) return false;
            const auto base = effect->GetBaseObject();
            return base && base->HasArchetype(a_type);
        });
    }

    /// @brief Check if an actor has an effect active with a specific keyword
    /// @param a_actor The actor to check
    /// @param a_keyword The keyword an effect should have
    /// @return True if the actor has an active effect with the keyword
    static bool HasEffectWithKeywordActive(RE::Actor *a_actor, const std::string_view a_keyword)
    {
        if (!a_actor || a_keyword.empty() || !a_actor->Is3DLoaded())
        {
            return false;
        }
        const auto& activeEffects = a_actor->GetActiveEffectList();
        if (!activeEffects)
            return false;

        if (const auto key = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(a_keyword)) {
            return std::ranges::any_of(*activeEffects, [key](const RE::ActiveEffect* effect) -> bool {
                if (!effect || effect->flags.any(RE::ActiveEffect::Flag::kInactive)) return false;
                const auto base = effect->GetBaseObject();
                return base && base->HasKeyword(key);
            });
        }
        return std::ranges::any_of(*activeEffects, [a_keyword](const RE::ActiveEffect* effect) -> bool {
            if (!effect || effect->flags.any(RE::ActiveEffect::Flag::kInactive)) return false;
            const auto base = effect->GetBaseObject();
            return base && base->HasKeywordString(a_keyword);
        });
    }


    /// @brief Check if an actor has a specific effect active
    /// @param a_actor The actor to check
    /// @param a_effect The effect to check for
    /// @return true if the specified effect is active
    static bool IsEffectActive(RE::Actor *a_actor, const RE::EffectSetting *a_effect)
    {
        if (!a_actor || !a_effect)
        {
            return false;
        }
        const auto& activeEffects = a_actor->GetActiveEffectList();
        if (!activeEffects)
            return false;

        return std::ranges::any_of(*activeEffects, [a_effect](const RE::ActiveEffect* effect) -> bool
        {
            if (!effect || effect->flags.any(RE::ActiveEffect::Flag::kInactive))
                return false;
            const auto base = effect->GetBaseObject();
            return base == a_effect;
        });
    }

    /// @brief Add item to actor
    /// @param a_actor The actor to add the item to
    /// @param a_item The item to add
    /// @param a_extraList The extra data to add
    /// @param a_count The amount to add
    /// @param a_fromRefr The reference the item is coming from
    static void AddItem(RE::Actor *a_actor, RE::TESBoundObject *a_item, RE::ExtraDataList *a_extraList, int a_count,
                        RE::TESObjectREFR *a_fromRefr)
    {
        using func_t = decltype(AddItem);
        static REL::Relocation<func_t> func{RELOCATION_ID(36525,37525)};
        return func(a_actor, a_item, a_extraList, a_count, a_fromRefr);
    }

    /// @brief Helper function to add an item to the player
    /// @param a_item The item to add to the player
    /// @param a_count The amount to add
    static void AddItemPlayer(RE::TESBoundObject *a_item, const int a_count)
    {
        return AddItem(RE::PlayerCharacter::GetSingleton(), a_item, nullptr, a_count, nullptr);
    }

    /// @brief Remove item from the player
    /// @param item The item to remove
    /// @param count The amount ot remove
    /// @return
    static int RemoveItemPlayer(RE::TESBoundObject *item, int count)
    {
        using func_t = decltype(RemoveItemPlayer);
        static REL::Relocation<func_t> func{RELOCATION_ID(16564, 16919)};
        return func(item, count);
    }

    /// @brief Check if actor has the specified item in the inventory
    /// @param actor The actor to check
    /// @param item The item to look for
    /// @return True if actor has at least one of the item
    static bool ActorHasItem(RE::Actor* actor, RE::TESBoundObject* item) {
        if (!actor || !item)
            return false;

        const auto& inv = actor->GetInventory();
        const auto it = inv.find(item);
        return it != inv.end() && it->second.first > 0;
    }

    /// @brief Get the weapon a character is currently wielding
    /// @param a_actor The actor to check
    /// @return The weapon the actor is currently wielding. If none, returns nullptr
    /// @note Credits: [Valhalla Combat by D7ry](https://github.com/D7ry/valhallaCombat/blob/48fb4c3b9bb6bbaa691ce41dbd33f096b74c07e3/src/include/Utils.cpp#L10)
    static RE::TESObjectWEAP* GetWieldingWeapon(RE::Actor *a_actor)
    {
        if (const auto weapon = a_actor->GetAttackingWeapon())
        {
            const auto obj = weapon->object;
            return obj ? obj->As<RE::TESObjectWEAP>() : nullptr;
        }
        if (const auto rhs = a_actor->GetEquippedObject(false); rhs && rhs->IsWeapon())
        {
            return rhs->As<RE::TESObjectWEAP>();
        }
        if (const auto lhs = a_actor->GetEquippedObject(true); lhs && lhs->IsWeapon())
        {
            return lhs->As<RE::TESObjectWEAP>();
        }

        return nullptr;
    }

    /// @brief Get the player mount
    /// @return The mount as actor
    static RE::Actor* GetPlayerMount()
    {
        RE::NiPointer<RE::Actor> currentMount;
        if ( RE::PlayerCharacter::GetSingleton()->GetMount(currentMount)) {
            return currentMount.get();
        }
        return nullptr;
    }

    /// @brief Check if an actor is power attacking
    /// @param actor The actor to check
    /// @return True if actor is power attacking
    static bool IsPowerAttacking(const RE::Actor *actor)
    {
        const auto high = actor->GetHighProcess();
        if (!high)
            return false;

        const auto &attackData = high->attackData;
        if (!attackData)
            return false;

        return attackData->data.flags.any(RE::AttackData::AttackFlag::kPowerAttack);
    }

    /// @brief Check if an actor is shield bashing
    /// @param actor The actor to check
    /// @return True if actor is attacking with a bash
    static bool IsBashing(const RE::Actor* actor) {

        const auto high = actor->GetHighProcess();

        if (!high)
            return false;

        if (actor->GetAttackState() == RE::ATTACK_STATE_ENUM::kNone)
            return false;

        const auto& attackData = high->attackData;
        if (!attackData)
            return false;

        return attackData->data.flags.any(RE::AttackData::AttackFlag::kBashAttack);
    }


    /// @brief Get all nearby actors
    /// @param a_ref The reference to check nearby
    /// @param a_radius The radius to search for actors
    /// @param a_ignorePlayer Ignore the player as actor
    /// @return vector of all actors in a set radius around a reference
    /// @note Credits: [Papyrus Extender by PO3](https://github.com/powerof3/PapyrusExtenderSSE/)
    static std::vector<RE::Actor*> GetNearbyActors(const RE::TESObjectREFR* a_ref, const float a_radius, const bool a_ignorePlayer)
    {
        std::vector<RE::Actor*> result;
        const auto processLists = RE::ProcessLists::GetSingleton();
        if (!processLists)
            return result;

        if (a_ignorePlayer && processLists->numberHighActors == 0)
            return result;

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
        return result;
    }


    /// @brief Runs the console command SetLevel to set an actor's level to the amount
    /// @param actor The actor to set the level of
    /// @param level The level the actor gets set to
    /// @note The console command also updates the actor's stats which the standalone function does not do automatically
    static void SetNPCLevel(RE::Actor *actor, uint16_t level)
    {
        const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
        const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
        if (!script)
            return;
        script->SetCommand(std::format("SetLevel {}", level));
        script->CompileAndRun(actor);
    }

    /// @brief Get the actor value percentage of an actor
    /// @param a_actor The actor to get the value from
    /// @param a_av The Actor Value to get
    /// @return float between 0.0 and 1.0
    /// @note 0.0 means 0% and 1.0 means 100%
    static float GetActorValuePercentage(RE::Actor* a_actor, RE::ActorValue a_av)
    {
        using func_t = decltype(&GetActorValuePercentage);
        static REL::Relocation<func_t> func{ RELOCATION_ID(0, 37337) };
        return func(a_actor, a_av);
    }
    

};

} // namespace StyyxUtil
