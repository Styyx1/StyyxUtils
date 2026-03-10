//
// Created by styyx on 09/03/2026.
//

#pragma once
#include <xbyak/xbyak.h>

namespace StyyxUtil
{
     namespace HookUtils
     {
          template <class T>
          void WriteCall5(REL::ID a_relID, uint32_t a_offset)
          {
               const REL::Relocation<uintptr_t> targ {a_relID, a_offset};
               auto& trampoline = SKSE::GetTrampoline();
               T::func = trampoline.write_call<5>(targ.address(), T::Call);
          }
          template <class O, uint32_t table, uint32_t index, class T>
          void WriteVFunc()
          {
               REL::Relocation<uintptr_t> vtbl {O::VTABLE[table]};
               T::func = vtbl.write_vfunc(index, T::Call);
          }

          template <typename Ret, typename... Args> static Ret GenericCall(REL::ID a_id, uint32_t a_offset, Args... args)
          {
               using func_t = Ret(*)(Args...);
               REL::Relocation<func_t> target{ a_id, a_offset };
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
