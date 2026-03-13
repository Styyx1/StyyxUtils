//
// Created by styyx on 12/03/2026.
//

#pragma once
namespace StyyxUtil
{
    struct SoundUtil
    {
        /// @brief Play a specific sound form
        /// @param a_actor The actor the sound plays at
        /// @param a_sound The sound Form to play
        /// @param a_volume The volume to play the sound with
        static void PlaySound(const RE::Actor *a_actor, const RE::BGSSoundDescriptorForm *a_sound, const float a_volume)
        {
            RE::BSSoundHandle handle;
            const auto am = RE::BSAudioManager::GetSingleton();
            am->GetSoundHandle(handle, a_sound->soundDescriptor);
            handle.SetVolume(a_volume);
            handle.SetObjectToFollow(a_actor->Get3D());
            handle.Play();
        }
    };
}
