#pragma once

namespace StyyxUtil {


	struct FormUtil {
        /// @brief Get Form from a string
        /// @param a_form_id_string The string to get the Form from
        /// @return A TESForm* or nullptr if it can't find a form
        /// @par Usage
        /// @code
        /// "Skyrim.esm|0x800" or "MyAwesomeFormEditorID"
        /// @endcode
        /// @note To make use of EditorID `powerofthree tweaks` needs to be installed
        static RE::TESForm* GetFormFromString(const std::string& a_form_id_string)
        {
            if (a_form_id_string.empty()) {
                return nullptr;
            }

            if (a_form_id_string.find('|') != std::string::npos) {
                std::istringstream ss{ a_form_id_string };
                std::string plugin, id;
                std::getline(ss, plugin, '|');
                std::getline(ss, id);

                if (plugin.empty() || id.empty()) {
                    return nullptr;
                }

                RE::FormID rawFormID{};
                std::istringstream(id) >> std::hex >> rawFormID;

                if (!rawFormID) {
                    return nullptr;
                }

                if (auto* dataHandler = RE::TESDataHandler::GetSingleton()) {
                    auto* form = dataHandler->LookupForm(rawFormID, plugin);
                    return form;
                }
                return nullptr;
            }

            if (auto* form = RE::TESForm::LookupByEditorID(a_form_id_string)) {
                return form;
            }
            return nullptr;
        }

	    /// @copybrief GetFormFromString
	    /// @ref GetFormFromString for usage details
	    static RE::SpellItem* GetSpellFromString(const std::string& a_form_id_string)
        {
            const auto form = GetFormFromString(a_form_id_string);
            return  form ? form->As<RE::SpellItem>() : nullptr;
        }

	    /// @copybrief GetFormFromString
	    /// @ref GetFormFromString for usage details
	    static RE::EffectSetting* GetEffectSettingFromString(const std::string& a_form_id_string)
        {
            const auto form = GetFormFromString(a_form_id_string);
            return  form ? form->As<RE::EffectSetting>() : nullptr;
        }

	    /// @copybrief GetFormFromString
	    /// @ref GetFormFromString for usage details
	    static RE::TESObjectWEAP* GetWeaponFromString(const std::string& a_form_id_string)
        {
            const auto form = GetFormFromString(a_form_id_string);
            return  form ? form->As<RE::TESObjectWEAP>() : nullptr;
        }

	};
}
