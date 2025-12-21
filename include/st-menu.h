#pragma once

namespace StyyxUtil {
	struct MenuUtil {

        /// <summary>
        /// Closes menu with name
        /// </summary>
        /// <param name="a_menuName"></param>
        inline static void CloseMenu(RE::BSFixedString a_menuName)
        {
            if (const auto UIMsgQueue = RE::UIMessageQueue::GetSingleton(); UIMsgQueue) {
                UIMsgQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kHide, nullptr);
            }
        }

	};
}