@ECHO OFF & PUSHD %~DP0

:Menu
Echo.&Echo  1.GenerateSolution
Echo.&Echo  2.BuildDebug
Echo.&Echo  3.BuildRelease
Echo.&Echo.

set /p a=Input Number:
If Not "%a%"=="" Set a=%a:~0,1%
If "%a%"=="1" Goto GenerateSolution
If "%a%"=="2" Goto BuildDebug
If "%a%"=="3" Goto BuildRelease
Exit

:GenerateSolution
cmake -G "Visual Studio 16 2019" -A "x64" -T "v141_xp" sample/CMakeLists.txt -B build/64
cmake -G "Visual Studio 16 2019" -A "Win32" -T "v141_xp" sample/CMakeLists.txt -B build/32
Goto Menu

:BuildDebug
cmake --build build/64 --config Debug
cmake --build build/32 --config Debug
Goto Menu

:BuildRelease
cmake --build build/64 --config Release
cmake --build build/32 --config Release
Goto Menu
