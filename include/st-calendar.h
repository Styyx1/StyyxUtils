#pragma once

#include <array>
#include <cstdint>

#include "RE/C/Calendar.h"

namespace StyyxUtil
{
struct CalendarUtil
{
    // Reference: https://en.uesp.net/wiki/Skyrim:Calendar

    inline static constexpr uint32_t kStartYear               = 201;
    inline static constexpr RE::Calendar::Day kFirstDayInYear = RE::Calendar::Day::kMiddas;

    inline static constexpr uint32_t kDaysPerYear = 365;
    inline static constexpr uint32_t kDaysPerWeek = 7;

    inline static constexpr std::array<uint32_t, 12> kDaysInMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    inline static constexpr std::array<uint32_t, 12> kMonthDayOffsets{
        0,   // Jan
        31,  // Feb
        59,  // March
        90,  // April
        120, // May
        151, // June
        181, // July
        212, // Aug
        243, // Sept
        273, // Oct
        304, // Nov
        334  // Dec
    };

    static std::uint32_t GetDayOfYear(std::uint32_t a_month, std::uint32_t a_day)
    {
        return kMonthDayOffsets[a_month] + a_day - 1;
    }

    static std::uint32_t GetAbsoluteDay(std::uint32_t a_year, std::uint32_t a_month, std::uint32_t a_day)
    {
        return (a_year - kStartYear) * kDaysPerYear + GetDayOfYear(a_month, a_day);
    }

    static RE::Calendar::Day GetDayOfWeek(std::uint32_t a_year, std::uint32_t a_month, std::uint32_t a_day)
    {
        const auto absoluteDay = GetAbsoluteDay(a_year, a_month, a_day);

        return static_cast<RE::Calendar::Day>((static_cast<std::uint32_t>(kFirstDayInYear) + absoluteDay) %
                                              kDaysPerWeek);
    }

    static RE::Calendar::Day GetDayOfWeek()
    {
        const auto calendar = RE::Calendar::GetSingleton();

        return GetDayOfWeek(calendar->GetYear(), calendar->GetMonth(), static_cast<std::uint32_t>(calendar->GetDay()));
    }

    static const char* GetDayOfWeekString()
    {
        auto day = GetDayOfWeek();
        switch (day)
        {
            case RE::Calendar::Day::kFredas:
                return "Fredas";
            case RE::Calendar::Day::kLoredas:
                return "Loredas";
            case RE::Calendar::Day::kMiddas:
                return "Middas";
            case RE::Calendar::Day::kMorndas:
                return "Morndas";
            case RE::Calendar::Day::kSundas:
                return "Sundas";
            case RE::Calendar::Day::kTirdas:
                return "Tirdas";
            case RE::Calendar::Day::kTurdas:
                return "Turdas";
            default:
                return "Middas";
        }
    }
};
} // namespace StyyxUtil