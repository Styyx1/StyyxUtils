//
// Created by styyx on 09/03/2026.
//

#pragma once
#include <xbyak/xbyak.h>

namespace StyyxUtil
{
     namespace HookUtils
     {
          /// @brief Basic Call hook.
          /// @tparam T The class this template works with
          /// @param a_relID Relocation ID for the function
          /// @param a_offset Offset for the function address
          /// @note needs SKSE::AllocTrampoline(14) per usage
          /// @note Hooked function needs to be called `Call` and the Relocation needs to be called func
          /// @par Example Usage:
          /// @code
          /// struct HasPerkHook
          ///{
          ///     static bool Call(RE::Actor* a_this, RE::BGSPerk* a_perk)
          ///     {
          ///          Your Code
          ///          return func(a_this, a_perk));
          ///     }
          ///     static inline REL::Relocation<decltype(Call)> func;
          ///};
          ///void InstallHook(){
          ///WriteCall5<HasPerkHook>(RELOCATION_ID(420, 69), 0x5);
          ///}
          /// @endcode
          template <class T>
          void WriteCall5(const REL::ID a_relID, const uint32_t a_offset)
          {
               static REL::Relocation<uintptr_t> targ {a_relID, a_offset};
               auto& trampoline = SKSE::GetTrampoline();
               T::func = trampoline.write_call<5>(targ.address(), T::Call);
          }
          template <class O, uint32_t table, uint32_t index, class T>
          void WriteVFunc()
          {
               static REL::Relocation<uintptr_t> vtbl {O::VTABLE[table]};
               T::func = vtbl.write_vfunc(index, T::Call);
          }

          template <typename Ret, typename... Args> static Ret GenericCall(REL::ID a_id, uint32_t a_offset, Args... args)
          {
               using func_t = Ret(*)(Args...);
               static REL::Relocation<func_t> target{ a_id, a_offset };
               return target(std::forward<Args>(args)...);
          }
          // copied from https://github.com/powerof3/PapyrusExtenderSSE/blob/0fbb355b634f2edcfd72bd364884e3ee5caadfc9/include/PCH.h#L140-L167
          // MIT License
          template <class T, std::size_t BYTES>
          void hook_function_prologue(std::uintptr_t a_src)
          {
               struct Patch : Xbyak::CodeGenerator
               {
                    Patch(std::uintptr_t a_originalFuncAddr, std::size_t a_originalByteLength)
                    {
                         // Hook returns here. Execute the restored bytes and jump back to the original function.
                         for (size_t i = 0; i < a_originalByteLength; ++i) {
                              db(*reinterpret_cast<std::uint8_t*>(a_originalFuncAddr + i));
                         }
                         jmp(ptr[rip]);
                         dq(a_originalFuncAddr + a_originalByteLength);
                    }
               };

               Patch p(a_src, BYTES);
               p.ready();

               auto& trampoline = SKSE::GetTrampoline();
               trampoline.write_branch<5>(a_src, T::thunk);

               auto alloc = trampoline.allocate(p.getSize());
               std::memcpy(alloc, p.getCode(), p.getSize());

               T::func = reinterpret_cast<std::uintptr_t>(alloc);
          }
     }
}
