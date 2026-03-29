#pragma once
#define NOMINMAX
#undef ERROR
#include "API/SKSEMenuFramework.h"

using namespace ImGuiMCP;

namespace StyyxUtil {
    struct UIUtil {       

        /// @brief Draw a ? that pops up some help text in SKSE Menu Framework
        /// @param desc Help text that should be shown
        /// @note Credits to: [QTR-Modding](https://github.com/QTR-Modding/SaveManagerSKSE/blob/af53d32f57a3fc4a0c0e22828b66e4592338826e/src/UI.cpp#L3)
        static void HelpMarker(const char* desc)
        {
            TextDisabled("(?)");
            if (BeginItemTooltip())
            {
                PushTextWrapPos(GetFontSize() * 35.0f);
                TextUnformatted(desc);
                PopTextWrapPos();
                EndTooltip();
            }
        }

        /// @brief Template to easily set up a slider with help text and have it optionally run a function if the slider changed
        /// @tparam T Any numeric type
        /// @param a_label Name of the slider (visible)
        /// @param a_sliderVariable Variable of the slider to change
        /// @param a_sliderMin Minimum value of the slider
        /// @param a_sliderMax Maximum value of the slider
        /// @param a_sliderFormat Formatting for the slider
        /// @param a_helpText Help text that's shown
        /// @param a_sliderWidth Slider width. Default = 200.0
        /// @param a_onSliderChanged Function to run when the slider changed
        /// @return True if slider changed
        /// @note Example. This Gives you a float slider with 2 decimals and changes a REX::TOML::F32 setting if the slider changes
        /// @code
        /// SettingSlider("ManipToml", m_TempFloat, 0.0f, 100.0f, "%.2f", "This slider will change a toml setting", 300.0f, [&](float var){mySetting.SetValue(var);});
        /// @endcode
        template <class T>
        static bool SettingSlider(const char* a_label, T& a_sliderVariable, const T &a_sliderMin, const T &a_sliderMax, const char* a_sliderFormat,
            const char* a_helpText, const float a_sliderWidth = 200.0f, const std::function<void(T)> &a_onSliderChanged = nullptr)
        {
            SetNextItemWidth(a_sliderWidth);

            constexpr auto data_type = std::is_same_v<T, uint32_t> ? ImGuiDataType_U32 :
                           std::is_integral_v<T>        ? ImGuiDataType_S32 :
                                                          ImGuiDataType_Float;

            const bool changed = SliderScalar(a_label, data_type, &a_sliderVariable, &a_sliderMin, &a_sliderMax, a_sliderFormat);
            if (changed && a_onSliderChanged)
                a_onSliderChanged(a_sliderVariable);
            SameLine();
            HelpMarker(a_helpText);
            return changed;
        }

        static bool SetCheckbox(const char* a_label, bool& a_settingVariable, const char* a_helpText, const std::function<void(bool)>& a_onCheckbox = nullptr)
        {
            const bool changed = Checkbox(a_label, &a_settingVariable);
            if (changed && a_onCheckbox)
                a_onCheckbox(a_settingVariable);
            SameLine();
            HelpMarker(a_helpText);
            return changed;
        }

        static constexpr ImVec4 GREEN{0.2f, 0.6f, 0.3f, 1.0f};
        static constexpr ImVec4 RED{0.78f, 0.0f, 0.0f, 1.0f};

        static void IndentTextColored(const ImVec4& color, const std::string& text, float indent = 120.f)
        {
            SetCursorPosX(GetCursorPosX() + indent);
            TextColored(color, text.c_str());
        }

        static void GreenTitleText(const std::string& text, float indent = 75.f)
        {
            SetCursorPosX(GetCursorPosX() + indent);
            TextColored(GREEN, text.c_str());
        }

        static void RedTitleText(const std::string& text, float indent = 75.f)
        {
            SetCursorPosX(GetCursorPosX() + indent);
            TextColored(RED, text.c_str());
        }

        static bool InputText(const char* label, char* buffer, size_t size, std::string& value, auto& configEntry, const char* help = nullptr)
        {
            if (ImGuiMCP::InputText(label, buffer, size)) {
                value = buffer;
                configEntry.SetValue(value);
                return true;
            }
            if (help) {
                SameLine();
                HelpMarker(help);
            }
            return false;
        }



    };
	

}


