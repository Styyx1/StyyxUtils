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


