# ffscriptUT
Ffscript's Unit test project

# Prerequisites
Conan version 1.9.2 or higher.

# How to build

1. You may need to add 'bincrafters' into conan remote repositories.  
```
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```
2. Create 'conan' directory.  

3. Run command.  
This project uses multi-configurations on Windows, so use following commands.
```
conan install .. -g cmake_multi -s arch=x86 -s build_type=Release
conan install .. -g cmake_multi -s arch=x86 -s build_type=Debug
conan install .. -g cmake_multi -s arch=x86_64 -s build_type=Release
conan install .. -g cmake_multi -s arch=x86_64 -s build_type=Debug
```

For Linux(test on Ubuntu 16.04).
```
conan install .. --build missing -s compiler.libcxx=libstdc++11
```