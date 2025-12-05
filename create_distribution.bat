@echo off
setlocal EnableExtensions EnableDelayedExpansion
REM Script to create a distributable package of the Game Studio
echo ======================================
echo Creating Distribution Package
echo ======================================

REM Set variables
set "BUILD_DIR=build"
set "DIST_DIR=GameStudio_Distribution"
set "EXE_NAME=GameStudio.exe"

REM Optional arg to disable pause (use: create_distribution.bat nopause)
set "_NOPAUSE=0"
if /I "%~1"=="nopause" set "_NOPAUSE=1"

REM Check if executable exists
if not exist "%BUILD_DIR%\%EXE_NAME%" (
    echo ERROR: %EXE_NAME% not found in %BUILD_DIR%
    echo Please build the project first using: cmake --build build
    if "%_NOPAUSE%"=="0" pause
    exit /b 1
)

REM Create distribution directory
echo Creating distribution directory...
if exist "%DIST_DIR%" rmdir /s /q "%DIST_DIR%"
mkdir "%DIST_DIR%"

REM Copy executable
echo Copying executable...
copy "%BUILD_DIR%\%EXE_NAME%" "%DIST_DIR%\"

REM Copy assets
echo Copying assets...
xcopy /E /I /Y "%BUILD_DIR%\assets" "%DIST_DIR%\assets"

REM Copy scores file if it exists
if exist "%BUILD_DIR%\scores.txt" (
    echo Copying scores file...
    copy "%BUILD_DIR%\scores.txt" "%DIST_DIR%\"
)

REM Find and copy SFML DLLs
echo Copying SFML DLLs...
set SFML_FOUND=0

REM Check multiple SFML installation paths
if exist "C:\SFML\SFML-2.6.2-gcc15\bin" (
    set SFML_BIN_PATH=C:\SFML\SFML-2.6.2-gcc15\bin
    set SFML_FOUND=1
) else if exist "C:\SFML\SFML-2.6.2\bin" (
    set SFML_BIN_PATH=C:\SFML\SFML-2.6.2\bin
    set SFML_FOUND=1
) else if exist "C:\SFML\SFML-3.0.2\bin" (
    set SFML_BIN_PATH=C:\SFML\SFML-3.0.2\bin
    set SFML_FOUND=1
)

if %SFML_FOUND%==1 (
    echo Found SFML at: %SFML_BIN_PATH%
    copy "%SFML_BIN_PATH%\sfml-graphics-2.dll" "%DIST_DIR%\" 2>nul
    copy "%SFML_BIN_PATH%\sfml-window-2.dll" "%DIST_DIR%\" 2>nul
    copy "%SFML_BIN_PATH%\sfml-system-2.dll" "%DIST_DIR%\" 2>nul
    copy "%SFML_BIN_PATH%\sfml-audio-2.dll" "%DIST_DIR%\" 2>nul
    copy "%SFML_BIN_PATH%\openal32.dll" "%DIST_DIR%\" 2>nul
    
    REM For SFML 3.x
    copy "%SFML_BIN_PATH%\sfml-graphics-3.dll" "%DIST_DIR%\" 2>nul
    copy "%SFML_BIN_PATH%\sfml-window-3.dll" "%DIST_DIR%\" 2>nul
    copy "%SFML_BIN_PATH%\sfml-system-3.dll" "%DIST_DIR%\" 2>nul

    REM Copy any additional dependent DLLs (freetype, zlib, ogg, vorbis, etc.)
    copy "%SFML_BIN_PATH%\*.dll" "%DIST_DIR%\" 2>nul
) else (
    echo WARNING: SFML installation not found!
    echo Please copy SFML DLLs manually to %DIST_DIR%
)

REM Find and copy MinGW runtime DLLs
echo Copying MinGW runtime DLLs...
set MINGW_FOUND=0

REM Check if MinGW is in PATH
where gcc.exe >nul 2>&1
if not errorlevel 1 (
    for /f "delims=" %%i in ('where gcc.exe') do set "GCC_PATH=%%i"
    for %%i in ("!GCC_PATH!") do set "MINGW_BIN=%%~dpi"
    set MINGW_FOUND=1
    echo Found MinGW at: !MINGW_BIN!
    
    copy "!MINGW_BIN!libgcc_s_seh-1.dll" "%DIST_DIR%\" 2>nul
    copy "!MINGW_BIN!libgcc_s_dw2-1.dll" "%DIST_DIR%\" 2>nul
    copy "!MINGW_BIN!libstdc++-6.dll" "%DIST_DIR%\" 2>nul
    copy "!MINGW_BIN!libwinpthread-1.dll" "%DIST_DIR%\" 2>nul
)

if %MINGW_FOUND%==0 (
    echo WARNING: MinGW not found in PATH!
    echo If the game doesn't run on other systems, you may need to:
    echo 1. Copy MinGW runtime DLLs manually, or
    echo 2. Statically link the runtime libraries during compilation
)

REM Create README for distribution
echo Creating README...
(
echo Game Studio - Modular Puzzle Game Collection
echo ============================================
echo.
echo To run the game:
echo 1. Make sure all DLL files are in the same directory as GameStudio.exe
echo 2. Double-click GameStudio.exe
echo.
echo System Requirements:
echo - Windows 7 or later
echo - OpenGL compatible graphics card
echo.
echo Included Games:
echo - Tic-Tac-Toe
echo - 2048 Puzzle
echo - Sudoku
echo.
echo For issues or questions, please contact the developer.
echo.
echo Files Included:
) > "%DIST_DIR%\README.txt"

dir /b "%DIST_DIR%" >> "%DIST_DIR%\README.txt"

REM Create a ZIP file if 7-Zip or PowerShell is available
echo.
echo Creating ZIP archive...
powershell -NoProfile -Command "Compress-Archive -Path '%DIST_DIR%\*' -DestinationPath '%DIST_DIR%.zip' -Force" 2>nul
if %ERRORLEVEL%==0 (
    echo ZIP archive created: %DIST_DIR%.zip
) else (
    echo ZIP creation failed. Please manually compress the %DIST_DIR% folder.
)

echo.
echo ======================================
echo Distribution package created successfully!
echo ======================================
echo Location: %CD%\%DIST_DIR%
echo.
echo You can now share the '%DIST_DIR%' folder or '%DIST_DIR%.zip' file.
echo.
if "%_NOPAUSE%"=="0" pause
endlocal
