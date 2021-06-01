@setlocal enabledelayedexpansion
@echo off

rem Example
rem
rem   Build target : VC++2019, Win32, Release, Windows 10
rem     call lz4-msbuild.bat lz4.sln /p:PlatformToolset=v142 /p:Platform=Win32 /p:Configuration=Release /p:WindowsTargetPlatformVersion=10
rem
rem   Build target : VC++2017, x64, Debug, Windows 8
rem     call lz4-msbuild.bat lz4.sln /p:PlatformToolset=v141 /p:Platform=x64 /p:Configuration=Debug
rem


rem Find vswhere.exe
rem https://github.com/Microsoft/vswhere
set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%vswhere%" (
  echo Error : Failed to find vswhere && exit /b 1
)


rem Find MSVC
rem https://github.com/microsoft/vswhere/wiki/Find-VC#batch
for /f "usebackq tokens=*" %%i in (`"%vswhere%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
  set "InstallDir=%%i"
)
if not exist "%InstallDir%\VC\Auxiliary\Build\vcvars64.bat" (
  echo Error : Failed to find MSVC && exit /b 1
)


rem Call setup script
call "%InstallDir%\VC\Auxiliary\Build\vcvars64.bat"


rem Invoke msbuild
echo on

msbuild /nologo /m /verbosity:minimal /t:Clean,Build %*

@echo off
echo errorlevel = %errorlevel%
exit /b %errorlevel%
