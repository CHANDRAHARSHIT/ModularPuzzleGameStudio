@echo off
REM Quick Setup Script for Modular Puzzle Game Studio
REM This script helps set up the project for building

echo ========================================
echo Modular Puzzle Game Studio - Quick Setup
echo ========================================
echo.

REM Step 1: Copy font file
echo Step 1: Setting up font file...
if exist "C:\Windows\Fonts\arial.ttf" (
    copy "C:\Windows\Fonts\arial.ttf" "assets\fonts\arial.ttf" >nul 2>&1
    echo [OK] Font file copied successfully
) else (
    echo [WARNING] arial.ttf not found in Windows\Fonts
    echo Please manually place a .ttf font file in assets\fonts\
)
echo.

REM Step 2: Check for CMake
echo Step 2: Checking for CMake...
where cmake >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [OK] CMake found
) else (
    echo [WARNING] CMake not found. Please install CMake from https://cmake.org/
)
echo.

REM Step 3: Check for SFML
echo Step 3: Checking for SFML...
echo You need to install SFML manually. Options:
echo   A) Using vcpkg (recommended):
echo      vcpkg install sfml:x64-windows
echo   B) Manual download from https://www.sfml-dev.org/
echo.

REM Step 4: Instructions
echo Step 4: Build Instructions
echo ========================================
echo After installing SFML, run these commands:
echo.
echo   mkdir build
echo   cd build
echo   cmake .. -DCMAKE_TOOLCHAIN_FILE="path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
echo   cmake --build . --config Release
echo.
echo Then run: .\Release\GameStudio.exe
echo ========================================
echo.

pause
