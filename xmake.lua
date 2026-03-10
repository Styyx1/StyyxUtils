option("use-hook-utils", function()
    set_default(false)
    set_description("enable hooking utils")
    add_defines("STYYX_HOOK_UTILS=1")
end)

if has_config("use-hook-utils") then
    add_requires("xbyak")
end

target("styyx-util")
    set_kind("headeronly")
    add_headerfiles("include/**.h")
    add_includedirs("include", {public = true})
    add_options("use-hook-utils", {public = true})
    if has_config("use-hook-utils") then
        add_packages("xbyak", {public = true})
    end