//
// Created by styyx on 13/03/2026.
//

#pragma once

namespace StyyxUtil
{
    struct CrimeUtil
    {
        static uint64_t GetCrimeValue(RE::Actor* a_actor, RE::PackageNS::CRIME_TYPE a_crime, RE::TESFaction* a_faction, int32_t a_itemValue = 0) {
            using func_t = decltype(&GetCrimeValue);
            static REL::Relocation<func_t> func{ RELOCATION_ID(36672,37680) };
            return func(a_actor, a_crime, a_faction, a_itemValue);
        }

        static void SendTrespassingAlarm(RE::Actor* a_this, RE::Actor* a_caughtBy, RE::TESNPC* a_caughtByBase, RE::PackageNS::CRIME_TYPE a_crimeType = RE::PackageNS::CRIME_TYPE::kTrespass) {
            using func_t = decltype(&SendTrespassingAlarm);
            static REL::Relocation<func_t> func{ RELOCATION_ID(36432, 37427) };
            return func(a_this, a_caughtBy, a_caughtByBase, a_crimeType);
        }

        static bool unk_Assault(RE::AIProcess* a_victimProcess, RE::Actor* a_victim, RE::Actor* a_aggressor, int64_t param_4 = 0, float param_5 = 0) {
            using func_t = decltype(&unk_Assault);
            static REL::Relocation<func_t> func{ RELOCATION_ID(38375,39359) };
            return func(a_victimProcess, a_victim, a_aggressor, param_4, param_5);
        }

        static void SendAssaultAlarm(RE::Actor* a_this, RE::Actor* a_attacker, int32_t a3, float a4) {
            using func_t = decltype(&SendAssaultAlarm);
            static REL::Relocation<func_t> func{ RELOCATION_ID(36429,37424) };
            return func(a_this, a_attacker, a3, a4);
        }

        static void SendStealAlarm(RE::Actor* a_this, RE::Actor * a_thief, RE::TESObjectREFR * a_stolenItemRef, RE::TESForm * a_stolenItemBase, int32_t a_stolenItemCount, int32_t a_itemWorth, RE::TESForm * a_owner, bool a8) {
            using func_t = decltype(&SendStealAlarm);
            static REL::Relocation<func_t> func{ RELOCATION_ID(36427,37422) };
            return func(a_this, a_thief, a_stolenItemRef, a_stolenItemBase, a_stolenItemCount, a_itemWorth, a_owner, a8);
        }
    };
}