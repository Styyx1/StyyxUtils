#pragma once

namespace StyyxUtil {
	struct SoundUtil {
        inline static void PlaySound(RE::Actor* a_actor, RE::BGSSoundDescriptorForm* a_sound, float a_volume)
        {
            RE::BSSoundHandle    handle;
            auto                 am = RE::BSAudioManager::GetSingleton();
            
            am->BuildSoundDataFromDescriptor(handle, a_sound->soundDescriptor);
            handle.SetVolume(a_volume);
            handle.SetObjectToFollow(a_actor->Get3D());
            handle.Play();

        }
	};
}
