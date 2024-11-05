@echo off
if "%1" == "clean" (
	if exist Win32 rmdir /s /q Win32
	if exist x64 rmdir /s /q x64
	if exist test.* del /f test.*
	exit /b
)
if "%1" == "install" (
	copy x64\Release\libredstone.dll C:\Windows\System32
	copy x64\Release\redstone.exe C:\Windows\System32
	copy x64\Release\testredstone.exe C:\Windows\System32
	copy ..\redstone.cfg C:\Windows\System32
	exit /b
)
if "%1" == "uninstall" (
	del C:\Windows\System32\libredstone.dll
	del C:\Windows\System32\redstone.exe
	del C:\Windows\System32\testredstone.exe
	del C:\Windows\System32\redstone.cfg
	exit /b
)
Setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
msbuild -m redstone.sln /p:Configuration=Debug /p:Platform=x64
msbuild -m redstone.sln /p:Configuration=Release /p:Platform=x64
msbuild -m redstone.sln /p:Configuration=Debug /p:Platform=x86
msbuild -m redstone.sln /p:Configuration=Release /p:Platform=x86
Endlocal
exit /b
