# StyyxUtils

Some headers with functions i reuse in various mods of mine. 
inspired by po3's [ClibUtil](https://github.com/powerof3/CLibUtil)   
documentation generated with doxygen [here](https://styyx1.github.io/StyyxUtils/)

to use it in your project, add it as submodule 
```
git submodule add https://github.com/Styyx1/StyyxUtils extern/styyx-utils
```

and in your xmake.lua
```
includes("extern/styyx-utils/xmake.lua")
```
and in target:
```
add_deps("styyx-util")
```
