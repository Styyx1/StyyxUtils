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
        FUCK::Indent(indent);
        FUCK::TextColored(color, text.c_str());
        FUCK::Unindent(indent);
    }

    static void GreenTitleText(const std::string& text, float indent = 75.f)
    {
        FUCK::Indent(indent);
        FUCK::TextColored(GREEN, text.c_str());
        FUCK::Unindent(indent);
    }

    static void RedTitleText(const std::string& text, float indent = 75.f)
    {
        FUCK::Indent(indent);
        FUCK::TextColored(RED, text.c_str());
        FUCK::Unindent(indent);
    }

    template <class T>
    static bool Checkbox(const char* label, T& value, auto& configEntry, const char* help = nullptr)
    {

        if (FUCK::Checkbox(label, &value))
        {
            configEntry.SetValue(value);
            return true;
        }
        if (help)
        {
            FUCK::SetTooltip(help);
        }
        return false;
    }

    template <class T>
    static bool SliderInt(const char* label, T& value, auto& configEntry, T min, T max, const char* help = nullptr)
    {
        if (FUCK::SliderInt(label, reinterpret_cast<int*>(&value), min, max))
        {
            configEntry.SetValue(value);
            return true;
        }
        if (help)
        {
            FUCK::SetTooltip(help);
        }

        return false;
    }

    template <class T>
    static bool SliderFloat(const char* label, T& value, auto& configEntry, float min, float max,
                            const char* help = nullptr)
    {
        if (FUCK::SliderFloat(label, reinterpret_cast<float*>(&value), min, max))
        {
            configEntry.SetValue(value);
            return true;
        }
        if (help)
        {
            FUCK::SetTooltip(help);
        }
        return false;
    }

    template <typename T>
    static bool FEnumStepper(const char* label, T* current_val, const std::vector<std::string>& items,
                             auto& configEntry, const char* help = nullptr, int first = 0, bool a_translate = true)
    {
        if (items.empty())
            return false;

        int idx = static_cast<int>(*current_val);
        if (idx < first)
            idx = first;
        if (idx >= static_cast<int>(items.size()))
            idx = static_cast<int>(items.size()) - 1;

        bool l = false, r = false;

        const char* displayText = a_translate ? FUCK::Translate(items[idx].c_str()) : items[idx].c_str();

        FUCK::Stepper(label, displayText, &l, &r);

        if (l)
        {
            *current_val = static_cast<T>((idx - 1 + static_cast<int>(items.size())) % static_cast<int>(items.size()));
            configEntry.SetValue(*current_val);
            return true;
        }
        if (r)
        {
            *current_val = static_cast<T>((idx + 1) % static_cast<int>(items.size()));
            configEntry.SetValue(*current_val);

            return true;
        }
        if (help)
        {
            FUCK::SetTooltip(help);
        }
        return false;
    }


    static bool InputText(const char* label, char* buffer, size_t size, std::string& value, auto& configEntry,
                          const char* help = nullptr)
    {
        if (FUCK::InputText(label, buffer, size))
        {
            value = buffer;
            configEntry.SetValue(value);
            return true;
        }
        if (help)
        {
            FUCK::SetTooltip(help);
        }
        return false;
    }
};
} // namespace StyyxUtil