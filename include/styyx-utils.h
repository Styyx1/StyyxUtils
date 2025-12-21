#include "st-random.h"
#include "st-magic.h"
#include "st-actor.h"
#include "st-cells.h"
#include "st-menu.h"
#include "st-forms.h"
#include "st-misc.h"
#include "st-timer.h"
#include "st-refs.h"

namespace StyyxUtil {
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
    template <auto FuncID, typename Ret, typename... Args> static inline Ret FuncCall(Args... args)
    {
        using func_t = Ret(*)(Args...);
        REL::Relocation<func_t> target{ REL::ID(FuncID) };
        return target(std::forward<Args>(args)...);
    }
}
