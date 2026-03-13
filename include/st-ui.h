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

        

    };
	

}


