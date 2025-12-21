#pragma once

namespace StyyxUtil
{
struct SoundUtil
{
    inline static void PlaySound(RE::Actor *a_actor, RE::BGSSoundDescriptorForm *a_sound, float a_volume)
    {
        RE::BSSoundHandle handle;
        auto am = RE::BSAudioManager::GetSingleton();

        am->BuildSoundDataFromDescriptor(handle, a_sound->soundDescriptor);
        handle.SetVolume(a_volume);
        handle.SetObjectToFollow(a_actor->Get3D());
        handle.Play();
    }
};
struct AVUtil
{
    /// <summary>
    /// Very useful for use with Actor Value Generator
    /// </summary>
    /// <param name="av_name"></param>
    /// <returns></returns>
    static inline RE::ActorValue LookupActorValueByName(const char *av_name)
    {
        using func_t = decltype(&LookupActorValueByName);
        REL::Relocation<func_t> func{REL::ID(27203)};
        return func(av_name);
    }
};
struct MiscUtil
{
    static inline bool IsQuestObject(RE::ExtraDataList *a_list)
    {
        using func_t = decltype(&IsQuestObject);
        REL::Relocation<func_t> target{REL::ID(12052)};
        return target(a_list);
    }

    /// <summary>
    /// Is any menu open from a specified vector
    /// </summary>
    /// <param name="a_ui"></param>
    /// <param name="a_menuNames"></param>
    /// <returns></returns>
    [[nodiscard]] static inline bool IsAnyOfMenuOpen(RE::UI *a_ui, const std::vector<std::string> &a_menuNames)
    {
        if (!a_ui)
            return true;
        for (auto &menuName : a_menuNames)
        {
            if (auto menu = a_ui->GetMenu(menuName); menu && menu.get()->OnStack())
                return true;
        }
        return false;
    }


    /// <summary>
    /// Helper to get the game setting off a const char*
    /// </summary>
    /// <param name="a_setting"></param>
    /// <returns></returns>
    static inline RE::Setting *GetGameSetting(const char *a_setting)
    {
        return RE::GameSettingCollection::GetSingleton()
                   ? RE::GameSettingCollection::GetSingleton()->GetSetting(a_setting)
                   : nullptr;
    }

    template <class T> 
    static inline void ChangeGameSetting(RE::Setting *setting, const T &value)
    {
        if (!setting)
        {
            return;
        }

        switch (setting->GetType())
        {

        case RE::Setting::Type::kBool:
            if constexpr (std::is_same_v<T, bool> || std::is_same_v<T, int> || std::is_same_v<T, uint32_t>)
            {
                setting->data.b = static_cast<bool>(value);
            }
            break;

        case RE::Setting::Type::kFloat:
            if constexpr (std::is_floating_point_v<T> || std::is_integral_v<T>)
            {
                setting->data.f = static_cast<float>(value);
            }
            break;

        case RE::Setting::Type::kSignedInteger:
            if constexpr (std::is_integral_v<T>)
            {
                setting->data.i = static_cast<int32_t>(value);
            }
            break;

        case RE::Setting::Type::kUnsignedInteger:
            if constexpr (std::is_integral_v<T>)
            {
                setting->data.u = static_cast<std::uint32_t>(value);
            }
            break;

        case RE::Setting::Type::kString:
            if constexpr (std::is_same_v<T, const char *> || std::is_same_v<T, std::string>)
            {
                setting->data.s(value);
            }
            break;

        default:
            break;
        }
    };

    /// <summary>
    /// Set Gamesetting based on the setting name. Uses another templated function to safely get the tpye
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="gmst"></param>
    /// <param name="value"></param>
    template <class T> 
    static inline void SetGMST(const char *gmst, const T &value)
    {
      ChangeGameSetting(GetGameSetting(gmst), value);
    };

    /// <summary>
    /// This is the only AI Generated Function. 
    /// It returns the entry point as string
    /// Only useful for logging
    /// </summary>
    /// <param name="entryPoint"></param>
    /// <returns></returns>
    static inline const char* EntryPointToString(RE::BGSEntryPoint::ENTRY_POINT entryPoint)
    {
        using namespace RE;
        switch (entryPoint) {
        case BGSEntryPoint::ENTRY_POINTS::kCalculateWeaponDamage: return "kCalculateWeaponDamage";
        case BGSEntryPoint::ENTRY_POINTS::kCalculateMyCriticalHitChance: return "kCalculateMyCriticalHitChance";
        case BGSEntryPoint::ENTRY_POINTS::kCalculateMyCriticalHitDamage: return "kCalculateMyCriticalHitDamage";
        case BGSEntryPoint::ENTRY_POINTS::kCalculateMineExplodeChance: return "kCalculateMineExplodeChance";
        case BGSEntryPoint::ENTRY_POINTS::kAdjustLimbDamage: return "kAdjustLimbDamage";
        case BGSEntryPoint::ENTRY_POINTS::kAdjustBookSkillPoints: return "kAdjustBookSkillPoints";
        case BGSEntryPoint::ENTRY_POINTS::kModRecoveredHealth: return "kModRecoveredHealth";
        case BGSEntryPoint::ENTRY_POINTS::kGetShouldAttack: return "kGetShouldAttack";
        case BGSEntryPoint::ENTRY_POINTS::kModBuyPrices: return "kModBuyPrices";
        case BGSEntryPoint::ENTRY_POINTS::kAddLeveledListOnDeath: return "kAddLeveledListOnDeath";
        case BGSEntryPoint::ENTRY_POINTS::kGetMaxCarryWeight: return "kGetMaxCarryWeight";
        case BGSEntryPoint::ENTRY_POINTS::kModAddictionChance: return "kModAddictionChance";
        case BGSEntryPoint::ENTRY_POINTS::kModAddictionDuration: return "kModAddictionDuration";
        case BGSEntryPoint::ENTRY_POINTS::kModPositiveChemDuration: return "kModPositiveChemDuration";
        case BGSEntryPoint::ENTRY_POINTS::kActivate: return "kActivate";
        case BGSEntryPoint::ENTRY_POINTS::kIgnoreRunningDuringDetection: return "kIgnoreRunningDuringDetection";
        case BGSEntryPoint::ENTRY_POINTS::kIgnoreBrokenLock: return "kIgnoreBrokenLock";
        case BGSEntryPoint::ENTRY_POINTS::kModEnemyCriticalHitChance: return "kModEnemyCriticalHitChance";
        case BGSEntryPoint::ENTRY_POINTS::kModSneakAttackMult: return "kModSneakAttackMult";
        case BGSEntryPoint::ENTRY_POINTS::kModMaxPlaceableMines: return "kModMaxPlaceableMines";
        case BGSEntryPoint::ENTRY_POINTS::kModBowZoom: return "kModBowZoom";
        case BGSEntryPoint::ENTRY_POINTS::kModRecoverArrowChance: return "kModRecoverArrowChance";
        case BGSEntryPoint::ENTRY_POINTS::kModSkillUse: return "kModSkillUse";
        case BGSEntryPoint::ENTRY_POINTS::kModTelekinesisDistance: return "kModTelekinesisDistance";
        case BGSEntryPoint::ENTRY_POINTS::kModTelekinesisDamageMult: return "kModTelekinesisDamageMult";
        case BGSEntryPoint::ENTRY_POINTS::kModTelekinesisDamage: return "kModTelekinesisDamage";
        case BGSEntryPoint::ENTRY_POINTS::kModBashingDamage: return "kModBashingDamage";
        case BGSEntryPoint::ENTRY_POINTS::kModPowerAttackStamina: return "kModPowerAttackStamina";
        case BGSEntryPoint::ENTRY_POINTS::kModPowerAttackDamage: return "kModPowerAttackDamage";
        case BGSEntryPoint::ENTRY_POINTS::kModSpellMagnitude: return "kModSpellMagnitude";
        case BGSEntryPoint::ENTRY_POINTS::kModSpellDuration: return "kModSpellDuration";
        case BGSEntryPoint::ENTRY_POINTS::kModSecondaryValueWeight: return "kModSecondaryValueWeight";
        case BGSEntryPoint::ENTRY_POINTS::kModArmorWeight: return "kModArmorWeight";
        case BGSEntryPoint::ENTRY_POINTS::kModIncomingStagger: return "kModIncomingStagger";
        case BGSEntryPoint::ENTRY_POINTS::kModTargetStagger: return "kModTargetStagger";
        case BGSEntryPoint::ENTRY_POINTS::kModAttackDamage: return "kModAttackDamage";
        case BGSEntryPoint::ENTRY_POINTS::kModIncomingDamage: return "kModIncomingDamage";
        case BGSEntryPoint::ENTRY_POINTS::kModTargetDamageResistance: return "kModTargetDamageResistance";
        case BGSEntryPoint::ENTRY_POINTS::kModSpellCost: return "kModSpellCost";
        case BGSEntryPoint::ENTRY_POINTS::kModPercentBlocked: return "kModPercentBlocked";
        case BGSEntryPoint::ENTRY_POINTS::kModShieldDeflectArrowChance: return "kModShieldDeflectArrowChance";
        case BGSEntryPoint::ENTRY_POINTS::kModIncomingSpellMagnitude: return "kModIncomingSpellMagnitude";
        case BGSEntryPoint::ENTRY_POINTS::kModIncomingSpellDuration: return "kModIncomingSpellDuration";
        case BGSEntryPoint::ENTRY_POINTS::kModPlayerIntimidation: return "kModPlayerIntimidation";
        case BGSEntryPoint::ENTRY_POINTS::kModPlayerReputation: return "kModPlayerReputation";
        case BGSEntryPoint::ENTRY_POINTS::kModFavorPoints: return "kModFavorPoints";
        case BGSEntryPoint::ENTRY_POINTS::kModBribeAmount: return "kModBribeAmount";
        case BGSEntryPoint::ENTRY_POINTS::kModDetectionLight: return "kModDetectionLight";
        case BGSEntryPoint::ENTRY_POINTS::kModDetectionMovement: return "kModDetectionMovement";
        case BGSEntryPoint::ENTRY_POINTS::kModSoulGemRecharge: return "kModSoulGemRecharge";
        case BGSEntryPoint::ENTRY_POINTS::kSetSweepAttack: return "kSetSweepAttack";
        case BGSEntryPoint::ENTRY_POINTS::kApplyCombatHitSpell: return "kApplyCombatHitSpell";
        case BGSEntryPoint::ENTRY_POINTS::kApplyBashingSpell: return "kApplyBashingSpell";
        case BGSEntryPoint::ENTRY_POINTS::kApplyReanimateSpell: return "kApplyReanimateSpell";
        case BGSEntryPoint::ENTRY_POINTS::kSetBooleanGraphVariable: return "kSetBooleanGraphVariable";
        case BGSEntryPoint::ENTRY_POINTS::kModSpellCastingSoundEvent: return "kModSpellCastingSoundEvent";
        case BGSEntryPoint::ENTRY_POINTS::kModPickpocketChance: return "kModPickpocketChance";
        case BGSEntryPoint::ENTRY_POINTS::kModDetectionSneakSkill: return "kModDetectionSneakSkill";
        case BGSEntryPoint::ENTRY_POINTS::kModFallingDamage: return "kModFallingDamage";
        case BGSEntryPoint::ENTRY_POINTS::kModLockpickSweetSpot: return "kModLockpickSweetSpot";
        case BGSEntryPoint::ENTRY_POINTS::kModSellPrices: return "kModSellPrices";
        case BGSEntryPoint::ENTRY_POINTS::kCanPickpocketEquippedItem: return "kCanPickpocketEquippedItem";
        case BGSEntryPoint::ENTRY_POINTS::kModLockpickLevelAllowed: return "kModLockpickLevelAllowed";
        case BGSEntryPoint::ENTRY_POINTS::kSetLockpickStartingArc: return "kSetLockpickStartingArc";
        case BGSEntryPoint::ENTRY_POINTS::kSetProgressionPicking: return "kSetProgressionPicking";
        case BGSEntryPoint::ENTRY_POINTS::kMakeLockpicksUnbreakable: return "kMakeLockpicksUnbreakable";
        case BGSEntryPoint::ENTRY_POINTS::kModAlchemyEffectiveness: return "kModAlchemyEffectiveness";
        case BGSEntryPoint::ENTRY_POINTS::kApplyWeaponSwingSpell: return "kApplyWeaponSwingSpell";
        case BGSEntryPoint::ENTRY_POINTS::kModCommandedActorLimit: return "kModCommandedActorLimit";
        case BGSEntryPoint::ENTRY_POINTS::kApplySneakingSpell: return "kApplySneakingSpell";
        case BGSEntryPoint::ENTRY_POINTS::kModPlayerMagicSlowdown: return "kModPlayerMagicSlowdown";
        case BGSEntryPoint::ENTRY_POINTS::kModWardMagickaAbsorptionPct: return "kModWardMagickaAbsorptionPct";
        case BGSEntryPoint::ENTRY_POINTS::kModInitialIngredientEffectsLearned: return "kModInitialIngredientEffectsLearned";
        case BGSEntryPoint::ENTRY_POINTS::kPurifyAlchemyIngredients: return "kPurifyAlchemyIngredients";
        case BGSEntryPoint::ENTRY_POINTS::kFilterActivation: return "kFilterActivation";
        case BGSEntryPoint::ENTRY_POINTS::kCanDualCastSpell: return "kCanDualCastSpell";
        case BGSEntryPoint::ENTRY_POINTS::kModTemperingHealth: return "kModTemperingHealth";
        case BGSEntryPoint::ENTRY_POINTS::kModEnchantmentPower: return "kModEnchantmentPower";
        case BGSEntryPoint::ENTRY_POINTS::kModSoulPctCapturedToWeapon: return "kModSoulPctCapturedToWeapon";
        case BGSEntryPoint::ENTRY_POINTS::kModSoulGemEnchanting: return "kModSoulGemEnchanting";
        case BGSEntryPoint::ENTRY_POINTS::kModNumberAppliedEnchantmentsAllowed: return "kModNumberAppliedEnchantmentsAllowed";
        case BGSEntryPoint::ENTRY_POINTS::kSetActivateLabel: return "kSetActivateLabel";
        case BGSEntryPoint::ENTRY_POINTS::kModShoutOK: return "kModShoutOK";
        case BGSEntryPoint::ENTRY_POINTS::kModPoisonDoseCount: return "kModPoisonDoseCount";
        case BGSEntryPoint::ENTRY_POINTS::kShouldApplyPlacedItem: return "kShouldApplyPlacedItem";
        case BGSEntryPoint::ENTRY_POINTS::kModArmorRating: return "kModArmorRating";
        case BGSEntryPoint::ENTRY_POINTS::kModLockpickingCrimeChance: return "kModLockpickingCrimeChance";
        case BGSEntryPoint::ENTRY_POINTS::kModIngredientsHarvested: return "kModIngredientsHarvested";
        case BGSEntryPoint::ENTRY_POINTS::kModSpellRange_TargetLoc: return "kModSpellRange_TargetLoc";
        case BGSEntryPoint::ENTRY_POINTS::kModPotionsCreated: return "kModPotionsCreated";
        case BGSEntryPoint::ENTRY_POINTS::kModLockpickingKeyRewardChance: return "kModLockpickingKeyRewardChance";
        case BGSEntryPoint::ENTRY_POINTS::kAllowMountActor: return "kAllowMountActor";
        default: return "UnknownEntryPoint";
        }
    }

    /// <summary>
    /// Checks if an esp/esl/esm is active
    /// useful if the dll requires Forms from an esp
    /// </summary>
    /// <param name="mod_name"></param>
    /// <returns></returns>
    static inline bool IsModLoaded(std::string_view mod_name) {
        const auto data_handler = RE::TESDataHandler::GetSingleton();
        auto main_file = data_handler->LookupModByName(mod_name);
        
        if (!main_file || main_file->compileIndex == 0xFF)
            return false;
        return true;
    }

    /// <summary>
    /// Helper function to log AttackStates
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    inline static const char* AttackStateToString(RE::ATTACK_STATE_ENUM state) {

        switch (state) {
        case RE::ATTACK_STATE_ENUM::kNone:
            return "kNone";
        case RE::ATTACK_STATE_ENUM::kDraw:
            return "kDraw";
        case RE::ATTACK_STATE_ENUM::kSwing:
            return "kSwing";
        case RE::ATTACK_STATE_ENUM::kHit:
            return "kHit";
        case RE::ATTACK_STATE_ENUM::kNextAttack:
            return "kNextAttack";
        case RE::ATTACK_STATE_ENUM::kFollowThrough:
            return "kFollowThrough";
        case RE::ATTACK_STATE_ENUM::kBash:
            return "kBash";
        case RE::ATTACK_STATE_ENUM::kBowDraw:
            return "kBowDraw";
        case RE::ATTACK_STATE_ENUM::kBowAttached:
            return "kBowAttached";
        case RE::ATTACK_STATE_ENUM::kBowDrawn:                
            return "kBowDrawn";
        case RE::ATTACK_STATE_ENUM::kBowReleasing:
            return "kBowReleasing";
        case RE::ATTACK_STATE_ENUM::kBowReleased:
            return "kBowReleased";
        case RE::ATTACK_STATE_ENUM::kBowNextAttack:
            return "kBowNextAttack";
        case RE::ATTACK_STATE_ENUM::kBowFollowThrough:
            return "kBowFollowThrough";
        case RE::ATTACK_STATE_ENUM::kFire:
            return "kFire";
        case RE::ATTACK_STATE_ENUM::kFiring:
            return "kFiring";
        case RE::ATTACK_STATE_ENUM::kFired:
            return "kFired";
        default:
            return "Unknown Attack State";

        }

        
    };
};
struct MathUtil {

    /// <summary>
    /// Template function to add to a value without ever risking to overflow the maximum value that type can have.
    /// Probably not needed for most things but i learned about std::conditional_t
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="base"></param>
    /// <param name="increment"></param>
    /// <returns></returns>
    template <typename T>
    static inline T SafelyAdd(T base, T increment) {
        static_assert(std::is_arithmetic_v<T>, "T must be a number");
        
        if (increment < 0)
            return base;

        // so uint8_t and int8_t are covered
        using ForMath = std::conditional_t < std::is_integral_v<T> && sizeof(T) < sizeof(int), int, T > ;
        ForMath safe_base = static_cast<ForMath>(base);
        ForMath safeI_increment = static_cast<ForMath>(increment);
        ForMath max_value = static_cast<ForMath>(std::numeric_limits<T>::max());

        ForMath sum = safe_base + safeI_increment;
        if (sum > max_value)
            sum = max_value;

        return static_cast<T>(sum);
    }

    /// <summary>
    /// Template function to add to a value up to a set cap. Quite useful for global variables for example
    /// use it like this: AddWithCap<float>(GlobalVariable*->value, 1.0, 100) 
    /// this will add 1 to the global up to 100;
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="base"></param>
    /// <param name="increment"></param>
    /// <param name="cap"></param>
    /// <returns></returns>
    template <typename T>
    static inline T AddWithCap(T base, T increment, T cap = std::numeric_limits<T>::max()) {
        static_assert(std::is_arithmetic_v<T>, "T must be a number");

        if (increment < 0)
            return base;

        // so uint8_t and int8_t are covered
        using ForMath = std::conditional_t < std::is_integral_v<T> && sizeof(T) < sizeof(int), int, T > ;
        ForMath safe_base = static_cast<ForMath>(base);
        ForMath safeI_increment = static_cast<ForMath>(increment);
        ForMath safe_cap = std::min(static_cast<ForMath>(cap), static_cast<ForMath>(std::numeric_limits<T>::max()));

        ForMath sum = safe_base + safeI_increment;
        if (sum > safe_cap) 
            sum = safe_cap;

        return static_cast<T>(sum);

    }
};
} // namespace StyyxUtil
