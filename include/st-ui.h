#pragma once
#define NOMINMAX
#undef ERROR
#include "API/SKSEMenuFramework.h"

using namespace ImGuiMCP;

namespace StyyxUtil {
    struct UIUtil {       

        static inline void HelpMarker(const char* desc)
        {
            ImGuiMCP::ImGui::TextDisabled("(?)");
            if (ImGuiMCP::ImGui::BeginItemTooltip())
            {
                ImGuiMCP::ImGui::PushTextWrapPos(ImGuiMCP::ImGui::GetFontSize() * 35.0f);
                ImGuiMCP::ImGui::TextUnformatted(desc);
                ImGuiMCP::ImGui::PopTextWrapPos();
                ImGuiMCP::ImGui::EndTooltip();
            }
        }

        

    };
	

}


