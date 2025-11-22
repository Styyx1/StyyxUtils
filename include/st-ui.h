#pragma once
#define NOMINMAX
#undef ERROR
#include "API/SKSEMenuFramework.h"

namespace StyyxUtil {
    struct UIUtil {

        static inline void HelpMarker(const char* desc)
        {
            ImGui::TextDisabled("(?)");
            if (ImGui::BeginItemTooltip())
            {
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted(desc);
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
        }

    };
	

}


