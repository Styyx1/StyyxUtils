#pragma once

namespace StyyxUtil
{
    struct MiscUtil
    {
        /// @brief Helper function to get Game settings by name
        /// @param a_setting Game setting name
        /// @return The setting related to the setting name
        static RE::Setting *GetGameSetting(const char *a_setting)
        {
            return RE::GameSettingCollection::GetSingleton()
                       ? RE::GameSettingCollection::GetSingleton()->GetSetting(a_setting)
                       : nullptr;
        }

        /// @brief Helper template to easily set a game setting to a value
        /// @tparam T can be bool, int, float, uint, string
        /// @param setting The setting you want to change
        /// @param value The value you want to set the setting to
        template <class T>
        static void ChangeGameSetting(RE::Setting *setting, const T &value)
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

        /// @brief Set a game setting (by name) to a specific value
        /// @tparam T can be bool, int, float, uint or string
        /// @param gmst Name of the game setting you want to change
        /// @param value Value to set the setting to
        /// @par Example
        /// @code
        /// MiscUtil::SetGMST("iAVDhmsLevelUp", 5);
        /// @endcode
        template <class T>
        static void SetGMST(const char *gmst, const T &value)
        {
            ChangeGameSetting(GetGameSetting(gmst), value);
        };

        /// @brief Check if a mod is loaded by its full file name
        /// @param mod_name The full name of the mod including extension
        /// @return true if the mod is loaded
        /// @note Pass the full filename including extension, e.g. "Skyrim.esm" not "Skyrim".\n Works with .esl, .esp and .esm
        /// @par Example
        /// @code
        /// if (MiscUtil::IsModLoaded("Skyrim.esm")) { ... }
        /// @endcode
        static bool IsModLoaded(const std::string_view& mod_name)
        {
            const auto data_handler = RE::TESDataHandler::GetSingleton();

            if (const auto main_file = data_handler->LookupModByName(mod_name); !main_file || main_file->compileIndex == 0xFF)
                return false;
            return true;
        }

        /// @brief Get the unarmed weapon pointer
        /// @return The unarmed weapon the game uses
        static RE::TESObjectWEAP* GetUnarmedWeapon()
        {
            auto** singleton{ reinterpret_cast<RE::TESObjectWEAP**>(REL::ID(401061).address()) };
            return *singleton;
        }

        /// @brief Run console command on reference
        /// @param a_target The reference to run the command on
        /// @param a_command The command string
        static void RunConsoleCommandOnRef(RE::TESObjectREFR* a_target, const std::string_view a_command)
        {
            const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
            const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
            if (!script) return;
            script->SetCommand(a_command);
            script->CompileAndRun(a_target);
        }

#pragma region EnumToString

        /// @defgroup EnumToString Enum to String helpers
        /// @{

        /// @brief Get the entry point name
        /// @param entryPoint The entry point you want to get the name of
        /// @return The name of the entry point
        static const char* EntryPointToString(RE::BGSEntryPoint::ENTRY_POINT entryPoint)
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

        /// @brief Get the name of a weapon type
        /// @param a_type The weapon type you want to get the name of
        /// @return The name of the Weapon type in the enum
        static const char* WeaponTypeToString(const RE::WEAPON_TYPE a_type)
        {
            switch (a_type)
            {
            case RE::WEAPON_TYPE::kBow:
                return "kBow";
            case RE::WEAPON_TYPE::kHandToHandMelee:
                return "kHandToHandMelee";
            case RE::WEAPON_TYPE::kOneHandAxe:
                return "kOneHandAxe";
            case RE::WEAPON_TYPE::kOneHandDagger:
                return "kOneHandDagger";
            case RE::WEAPON_TYPE::kOneHandMace:
                return "kOneHandMace";
            case RE::WEAPON_TYPE::kOneHandSword:
                return "kOneHandSword";
            case RE::WEAPON_TYPE::kTwoHandAxe:
                return "kTwoHandAxe";
            case RE::WEAPON_TYPE::kTwoHandSword:
                return "kTwoHandSword";
            case RE::WEAPON_TYPE::kCrossbow:
                return "kCrossbow";
            case RE::WEAPON_TYPE::kStaff:
                return "kStaff";
            default:
                return "Unknown";
            }
        }

        /// @brief Get the name of a specified attack state
        /// @param state The attack state you want to get the name of
        /// @return The name of the attack state
        static const char* AttackStateToString(RE::ATTACK_STATE_ENUM state) {

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
        }

        /// @}

#pragma endregion
    };
}
