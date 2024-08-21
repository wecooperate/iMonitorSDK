@ECHO OFF & PUSHD %~DP0

:Menu
Echo.&Echo  1.GenerateSolution
Echo.&Echo  2.BuildDebug32
Echo.&Echo  3.BuildRelease32
Echo.&Echo  4.BuildDebug64
Echo.&Echo  5.BuildRelease64
Echo.&Echo.

set /p a=Input Number:
If Not "%a%"=="" Set a=%a:~0,1%
If "%a%"=="1" Goto GenerateSolution
If "%a%"=="2" Goto BuildDebug32
If "%a%"=="3" Goto BuildRelease32
If "%a%"=="4" Goto BuildDebug64
If "%a%"=="5" Goto BuildRelease64
Exit

:GenerateSolution
cmake -G "Visual Studio 17 2022" -A "x64" -T "v141_xp" sample/CMakeLists.txt -B build/64
cmake -G "Visual Studio 17 2022" -A "Win32" -T "v141_xp" sample/CMakeLists.txt -B build/32
Goto Menu

:BuildDebug32
cmake --build build/32 --config Debug
Goto Menu

:BuildRelease32
cmake --build build/32 --config Release
Goto Menu

:BuildDebug64
cmake --build build/64 --config Debug
Goto Menu

:BuildRelease64
cmake --build build/64 --config Release
Goto Menu
