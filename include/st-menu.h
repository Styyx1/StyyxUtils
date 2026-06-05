#pragma once

namespace StyyxUtil
{
struct MenuUtil
{
    /// @brief Closes the specified menu
    /// @param a_menuName The name of the menu to close
    static void CloseMenu(const RE::BSFixedString& a_menuName)
    {
        if (const auto UIMsgQueue = RE::UIMessageQueue::GetSingleton(); UIMsgQueue)
        {
            UIMsgQueue->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kHide, nullptr);
        }
    }

    /// @brief Check if any menu from a vector with menu names is open
    /// @param a_menuNames vector of menu names to check
    /// @return true if any menu from the vector is open (on the menu stack)
    [[nodiscard]] static bool IsAnyOfMenuOpen(const std::vector<std::string>& a_menuNames)
    {
        const auto ui = RE::UI::GetSingleton();
        if (!ui)
            return true;
        for (auto& menuName : a_menuNames)
        {
            if (const auto menu = ui->GetMenu(menuName); menu && menu->OnStack())
                return true;
        }
        return false;
    }

    static void VisitMenuMembersRec(const char* a_path, RE::GFxValue& a_obj, int depth = 0, int max_depth = 4)
    {
        if (depth > max_depth)
        {
            return;
        }

        struct MemberVisitor : RE::GFxValue::ObjectVisitor
        {
            const char* path;
            int depth;
            int max_depth;

            void Visit(const char* a_name, const RE::GFxValue& a_val) override
            {
                std::string full_path = std::string(path) + "." + a_name;
                switch (a_val.GetType())
                {
                    case RE::GFxValue::ValueType::kNumber:
                        SKSE::log::info("{} = {}", full_path, a_val.GetNumber());
                        break;
                    case RE::GFxValue::ValueType::kBoolean:
                        SKSE::log::info("{} = {}", full_path, a_val.GetBool());
                        break;
                    case RE::GFxValue::ValueType::kString:
                        SKSE::log::info("{} = {}", full_path, a_val.GetString());
                        break;
                    case RE::GFxValue::ValueType::kObject:
                    case RE::GFxValue::ValueType::kDisplayObject:
                    {
                        SKSE::log::info("{} = [object]", full_path);
                        auto val_copy = const_cast<RE::GFxValue&>(a_val);
                        VisitMenuMembersRec(full_path.c_str(), val_copy, depth + 1, max_depth);
                        break;
                    }
                    default:
                        SKSE::log::info("{} = [unknown]", full_path);
                        break;
                }
            }
        };

        MemberVisitor visitor;
        visitor.path      = a_path;
        visitor.depth     = depth;
        visitor.max_depth = max_depth;
        a_obj.VisitMembers(&visitor);
    }
};
} // namespace StyyxUtil