@page changelog Changelog

## Changelog

### [UNRELEASED]

#### Removed

- `AVUtil::LookupActorValueByName` - use `RE::ActorValueList::LookupActorValueByName()` directly
- `MiscUtil::IsQuestObject` - use `RE::ExtraDataList::HasQuestObjectAlias()` directly
- `GetInventoryWeight` - use `Actor::GetActorValue(RE::ActorValue::kInventoryWeight)` instead
- `GetMount` - use `Actor::GetMount` directly

#### Added

- ``GetAllPlayablePerks``
- `GetAllWarriorPerks`
- `GetAllMagePerks`
- `GetAllThiefPerks`
- namespace `DBGUtils`
- `GetSpellFromString`
- `GetEffectSettingFromString`
- `GetWeaponFromString`

#### Misc Changes

- refractored files to better reflect the struct the functions are in
- added options to xmake.lua (better explained in the readme)
- removed inner struct in TimerUtil
- updated doxygen documentation
- added `HookUtil`
-
