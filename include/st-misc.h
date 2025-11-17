#pragma once

namespace StyyxUtil
{
struct SoundUtil
{
    inline static void PlaySound(RE::Actor *a_actor, RE::BGSSoundDescriptorForm *a_sound, float a_volume)
    {
        RE::BSSoundHandle handle;
        auto am = RE::BSAudioManager::GetSingleton();

        am->BuildSoundDataFromDescriptor(handle, a_sound->soundDescriptor);
        handle.SetVolume(a_volume);
        handle.SetObjectToFollow(a_actor->Get3D());
        handle.Play();
    }
};
struct AVUtil
{
    static inline RE::ActorValue LookupActorValueByName(const char *av_name)
    {
        using func_t = decltype(&LookupActorValueByName);
        REL::Relocation<func_t> func{REL::ID(27203)};
        return func(av_name);
    }

    // returns from 0 - 1.0 1 == 100%
    static inline float GetActorValuePercentage(RE::Actor *a_actor, RE::ActorValue a_av)
    {
        using func_t = decltype(&GetActorValuePercentage);
        REL::Relocation<func_t> target{REL::ID(37337)};
        return target(a_actor, a_av);
    }
};
struct MiscUtil
{
    static inline bool IsQuestObject(RE::ExtraDataList *a_list)
    {
        using func_t = decltype(&IsQuestObject);
        REL::Relocation<func_t> target{REL::ID(12052)};
        return target(a_list);
    }

    [[nodiscard]] static inline bool IsAnyOfMenuOpen(RE::UI *a_ui, const std::vector<std::string> &a_menuNames)
    {
        if (!a_ui)
            return true;
        for (auto &menuName : a_menuNames)
        {
            if (auto menu = a_ui->GetMenu(menuName); menu && menu.get()->OnStack())
                return true;
        }
        return false;
    }

    static inline RE::Setting *GetGameSetting(const char *a_setting)
    {
        return RE::GameSettingCollection::GetSingleton()
                   ? RE::GameSettingCollection::GetSingleton()->GetSetting(a_setting)
                   : nullptr;
    }

    template <class T> static inline void ChangeGameSetting(RE::Setting *setting, const T &value)
    {
        if (!setting)
        {
            return;
        }

        switch (setting->GetType())
        {

        case RE::Setting::Type::kBool:
            if constexpr (std::is_same_v<T, bool> || std::is_same_v<T, int> || std::is_same_v<T, uint32_t>)
            {
                setting->data.b = static_cast<bool>(value);
            }
            break;

        case RE::Setting::Type::kFloat:
            if constexpr (std::is_floating_point_v<T> || std::is_integral_v<T>)
            {
                setting->data.f = static_cast<float>(value);
            }
            break;

        case RE::Setting::Type::kSignedInteger:
            if constexpr (std::is_integral_v<T>)
            {
                setting->data.i = static_cast<std::int32_t>(value);
            }
            break;

        case RE::Setting::Type::kUnsignedInteger:
            if constexpr (std::is_integral_v<T>)
            {
                setting->data.u = static_cast<std::uint32_t>(value);
            }
            break;

        case RE::Setting::Type::kString:
            if constexpr (std::is_same_v<T, const char *> || std::is_same_v<T, std::string>)
            {
                setting->data.s(value);
            }
            break;

        default:
            break;
        }
    };
    template <class T> static inline void SetGMST(const char *gmst, const T &value)
    {
      ChangeGameSetting(GetGameSetting(gmst), value);
    };
};
} // namespace StyyxUtil
