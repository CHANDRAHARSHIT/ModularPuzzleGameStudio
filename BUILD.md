# Modular Puzzle Game Studio - Build Instructions

## Quick Start Guide

### Windows

#### Option 1: Using Visual Studio (Recommended)

1. **Install Prerequisites:**
   - Visual Studio 2019 or later with C++ development tools
   - Install vcpkg package manager

2. **Install SFML:**
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg integrate install
   .\vcpkg install sfml:x64-windows
   ```

3. **Build the Project:**
   ```powershell
   cd ModularPuzzleGameStudio
   mkdir build
   cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
   cmake --build . --config Release
   ```

4. **Run:**
   ```powershell
   cd Release
   .\GameStudio.exe
   ```

#### Option 2: Using MinGW

1. **Install MinGW-w64 and CMake**

2. **Download SFML:**
   - Get SFML 2.5.1 MinGW edition from https://www.sfml-dev.org/download.php
   - Extract to `C:\SFML`

3. **Build:**
   ```powershell
   cd ModularPuzzleGameStudio
   mkdir build
   cd build
   cmake .. -G "MinGW Makefiles" -DSFML_DIR="C:/SFML/lib/cmake/SFML"
   cmake --build .
   ```

### Linux (Ubuntu/Debian)

1. **Install Dependencies:**
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential cmake libsfml-dev
   ```

2. **Build:**
   ```bash
   cd ModularPuzzleGameStudio
   mkdir build
   cd build
   cmake ..
   make -j4
   ```

3. **Run:**
   ```bash
   ./GameStudio
   ```

### macOS

1. **Install Dependencies:**
   ```bash
   brew install cmake sfml
   ```

2. **Build:**
   ```bash
   cd ModularPuzzleGameStudio
   mkdir build
   cd build
   cmake ..
   make -j4
   ```

3. **Run:**
   ```bash
   ./GameStudio
   ```

## Font Setup

The application requires a font file. It will attempt to load from:
1. `assets/fonts/arial.ttf` (create this directory and add arial.ttf)
2. System fonts (Windows: `C:/Windows/Fonts/arial.ttf`)

For best results, place a font file in `assets/fonts/arial.ttf`

## Troubleshooting

### SFML Not Found
If CMake can't find SFML:
```bash
cmake .. -DSFML_DIR="path/to/SFML/lib/cmake/SFML"
```

### Missing DLLs on Windows
Copy SFML DLLs from the SFML bin directory to your executable directory:
- sfml-graphics-2.dll
- sfml-window-2.dll
- sfml-system-2.dll

### Font Not Loading
Place `arial.ttf` or any TrueType font in `assets/fonts/` directory.

## Running Tests

Currently, no unit tests are implemented. This is an area for future enhancement.

## Building for Distribution

### Windows
```powershell
cmake --build . --config Release
cpack
```

### Linux
```bash
make
sudo make install
```

## Development

For development with IDE support:
- **Visual Studio**: Open the generated `.sln` file in the build directory
- **CLion**: Open the project root directory directly
- **VS Code**: Install C++ and CMake Tools extensions

## Performance Tips

- Build in Release mode for better performance: `-DCMAKE_BUILD_TYPE=Release`
- Enable compiler optimizations
- Use static linking for standalone executables

## Contact

For issues or questions, refer to the README.md file.
