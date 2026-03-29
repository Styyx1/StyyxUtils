//
// Created by styyx on 24/03/2026.
//

#pragma once

#include <functional>

#include "API/FUCK_API.h"

namespace StyyxUtil
{
    struct FUCKUtil
    {
        static constexpr ImVec4 GREEN{0.2f, 0.6f, 0.3f, 1.0f};
        static constexpr ImVec4 RED{0.78f, 0.0f, 0.0f, 1.0f};

        static void IndentTextColored(const ImVec4& color, const std::string& text, float indent = 120.f)
        {
            FUCK::SetCursorPosX(FUCK::GetCursorPos().x + indent);
            FUCK::TextColored(color, text.c_str());
        }

        static void GreenTitleText(const std::string& text, float indent = 75.f)
        {
            FUCK::SetCursorPosX(FUCK::GetCursorPos().x + indent);
            FUCK::TextColored(GREEN, text.c_str());
        }

        static void RedTitleText(const std::string& text, float indent = 75.f)
        {
            FUCK::SetCursorPosX(FUCK::GetCursorPos().x + indent);
            FUCK::TextColored(RED, text.c_str());
        }


        template <class T>
        static bool Checkbox(const char* label, T& value, auto& configEntry, const char* help = nullptr)
        {
            if (FUCK::Checkbox(label, &value)) {
                configEntry.SetValue(value);
                return true;
            }
            if (help) {
                FUCK::SameLine();
                FUCK::HelpMarker(help);
            }
            return false;
        }

        template <class T>
        static bool SliderInt(const char* label, T& value, auto& configEntry, T min, T max, const char* help = nullptr)
        {
            if (FUCK::SliderInt(label, reinterpret_cast<int*>(&value), min, max)) {
                configEntry.SetValue(value);
                return true;
            }
            if (help) {
                FUCK::SameLine();
                FUCK::HelpMarker(help);
            }

            return false;
        }

        template <class T>
        static bool SliderFloat(const char* label, T& value, auto& configEntry, float min, float max, const char* help = nullptr)
        {
            if (FUCK::SliderFloat(label, reinterpret_cast<float*>(&value), min, max))
            {
                configEntry.SetValue(value);
                return true;
            }
            if (help)
            {
                FUCK::SameLine();
                FUCK::HelpMarker(help);
            }
            return false;
        }

        static bool InputText(const char* label, char* buffer, size_t size, std::string& value, auto& configEntry, const char* help = nullptr)
        {
            if (FUCK::InputText(label, buffer, size)) {
                value = buffer;
                configEntry.SetValue(value);
                return true;
            }
            if (help) {
                FUCK::SameLine();
                FUCK::HelpMarker(help);
            }
            return false;
        }
    };
}