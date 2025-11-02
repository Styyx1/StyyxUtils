#pragma once

namespace StyyxUtil {


	struct FormUtil {
        static inline RE::TESForm* GetFormFromString(const std::string& formIDstring)
        {
            if (formIDstring.empty()) {
                return nullptr;
            }

            if (formIDstring.find('|') != std::string::npos) {
                std::istringstream ss{ formIDstring };
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

            if (auto* form = RE::TESForm::LookupByEditorID(formIDstring)) {
                return form;
            }
            return nullptr;
        }
	};
}
