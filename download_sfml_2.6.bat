@echo off
echo ========================================
echo SFML 2.6.2 Quick Setup for MinGW
echo ========================================
echo.

echo Downloading SFML 2.6.2...
powershell -Command "Invoke-WebRequest -Uri 'https://www.sfml-dev.org/files/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit.zip' -OutFile '%USERPROFILE%\Downloads\SFML-2.6.2.zip'"

if exist "%USERPROFILE%\Downloads\SFML-2.6.2.zip" (
    echo Download complete!
    echo.
    echo Extracting to C:\SFML...
    powershell -Command "Expand-Archive -Path '%USERPROFILE%\Downloads\SFML-2.6.2.zip' -DestinationPath 'C:\SFML' -Force"
    echo.
    echo Done! SFML 2.6.2 installed at C:\SFML\SFML-2.6.2
    echo.
    echo Next steps:
    echo 1. Go back to ModularPuzzleGameStudio folder
    echo 2. Delete the build folder
    echo 3. Run: mkdir build; cd build
    echo 4. Run: cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
    echo 5. Run: cmake --build . --config Release
    echo.
) else (
    echo Download failed! Please download manually from:
    echo https://www.sfml-dev.org/download/sfml/2.6.2/
    echo Choose: SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit.zip
)

pause
