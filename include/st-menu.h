#pragma once

namespace StyyxUtil {
	struct MenuUtil {
        /// @brief Closes the specified menu
        /// @param a_menuName The name of the menu to close
        static void CloseMenu(const RE::BSFixedString& a_menuName)
        {
            if (const auto UIMsgQueue = RE::UIMessageQueue::GetSingleton(); UIMsgQueue) {
                UIMsgQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kHide, nullptr);
            }
        }

		/// @brief Check if any menu from a vector with menu names is open
		/// @param a_menuNames vector of menu names to check
		/// @return true if any menu from the vector is open (on the menu stack)
		[[nodiscard]] static bool IsAnyOfMenuOpen(const std::vector<std::string> &a_menuNames)
        {
        	const auto ui = RE::UI::GetSingleton();
        	if (!ui)
        		return true;
        	for (auto &menuName : a_menuNames)
        	{
        		if (const auto menu = ui->GetMenu(menuName); menu && menu->OnStack())
        			return true;
        	}
        	return false;
        }

	};
}