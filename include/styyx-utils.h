#pragma once

#include "st-actor.h"
#include "st-cells.h"
#include "st-crimes.h"
#include "st-forms.h"
#include "st-magic.h"
#include "st-math.h"
#include "st-menu.h"
#include "st-misc.h"
#include "st-perks.h"
#include "st-random.h"
#include "st-refs.h"
#include "st-sounds.h"
#include "st-timer.h"
#ifdef STYYX_DEBUG_UTILS
#include "st-debug.h"
#endif

#ifdef STYYX_HOOK_UTILS
#include "st-hooks.h"
#endif

namespace StyyxUtil
{
/// <summary>
/// Template function for game function calls
/// use like this:
/// FuncCall<123456, void>(a_this)
/// </summary>
/// <typeparam name="Ret"></typeparam>
/// <typeparam name="...Args"></typeparam>
/// <typeparam name="FuncID"></typeparam>
/// <param name="...args"></param>
/// <returns></returns>
template <auto FuncID, typename Ret, typename... Args>
static inline Ret FuncCall(Args... args)
{
    using func_t = Ret (*)(Args...);
    REL::Relocation<func_t> target{REL::ID(FuncID)};
    return target(std::forward<Args>(args)...);
}
} // namespace StyyxUtil
