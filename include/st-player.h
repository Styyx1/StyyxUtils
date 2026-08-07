#pragma once

namespace StyyxUtil
{

struct PlayerUtil
{

    static inline bool IsBeastForm()
    {
        auto menu_control = RE::MenuControls::GetSingleton();
        return menu_control->InBeastForm();
    }

    static inline bool PlayerIsSuperNatural()
    {
        auto player  = RE::PlayerCharacter::GetSingleton();
        auto pl_race = player->GetRace();

        return IsBeastForm() || player->HasKeywordWithType(RE::DEFAULT_OBJECT::kKeywordUndead);
    }
};

} // namespace StyyxUtil