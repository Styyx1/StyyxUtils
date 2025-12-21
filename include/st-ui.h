#pragma once
#define NOMINMAX
#undef ERROR
#include "API/SKSEMenuFramework.h"

using namespace ImGuiMCP;

namespace StyyxUtil {
    struct UIUtil {       
        /// <summary>
        /// helper function for skse menu framework integration. 
        /// this requires the included api
        /// Credits:
        /// [QTR-Modding](https://github.com/QTR-Modding/SaveManagerSKSE/blob/af53d32f57a3fc4a0c0e22828b66e4592338826e/src/UI.cpp#L3)
        /// </summary>
        /// <param name="desc"></param>
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


