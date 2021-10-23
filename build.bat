@echo off

cmake -G "Visual Studio 16 2019" -A "Win32" -T "v141_xp" sample/CMakeLists.txt -B build

cmake --build build --config Release
