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
        for (auto& menuName : a_menuNames)            
        {
          if (auto menu = a_ui->GetMenu(menuName); menu && menu.get()->OnStack())
            return true;
        }
        return false;
    }
};
} // namespace StyyxUtil
