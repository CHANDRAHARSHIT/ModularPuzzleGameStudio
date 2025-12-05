# Distribution Guide

## How to Share Your Game with Others

When sharing your game executable, you need to include all required DLL dependencies. This guide explains the complete process.

---

## Quick Solution

### Option 1: Use the Automated Script (Recommended)
Run the provided script to automatically create a distribution package:
```batch
create_distribution.bat
```

This will create a `GameStudio_Distribution` folder containing:
- `GameStudio.exe` (your game)
- All required DLL files
- Assets folder (fonts, images)
- README file

Share the entire folder or the generated ZIP file with others.

---

## Manual Distribution Process

### Step 1: Identify Required DLLs

#### A. SFML DLLs (Required)
Located in your SFML installation (e.g., `C:\SFML\SFML-2.6.2\bin\`):
- `sfml-graphics-2.dll`
- `sfml-window-2.dll`
- `sfml-system-2.dll`
- `sfml-audio-2.dll` (if using audio)
- `openal32.dll` (if using audio)

#### B. MinGW Runtime DLLs (May be Required)
Located in MinGW bin directory (e.g., `C:\MinGW\bin\` or where `gcc.exe` is located):
- `libgcc_s_seh-1.dll` or `libgcc_s_dw2-1.dll`
- `libstdc++-6.dll`
- `libwinpthread-1.dll`

### Step 2: Create Distribution Package

1. Create a new folder (e.g., `GameStudio_Distribution`)
2. Copy these items into the folder:
   ```
   GameStudio_Distribution/
   ├── GameStudio.exe
   ├── sfml-graphics-2.dll
   ├── sfml-window-2.dll
   ├── sfml-system-2.dll
   ├── libgcc_s_seh-1.dll
   ├── libstdc++-6.dll
   ├── libwinpthread-1.dll
   └── assets/
       ├── fonts/
       └── images/
   ```

3. Compress the folder to a ZIP file
4. Share the ZIP file

---

## Alternative Solutions

### Option A: Static Linking (Prevents DLL Issues)

Modify your `CMakeLists.txt` to statically link libraries:

```cmake
# Add after find_package(SFML...)
set(SFML_STATIC_LIBRARIES TRUE)

# For MinGW, link runtime statically
if(MINGW)
    target_link_options(GameStudio PRIVATE 
        -static-libgcc 
        -static-libstdc++ 
        -static
    )
endif()
```

**Benefits:**
- Single executable file (no DLLs needed)
- Easier distribution

**Drawbacks:**
- Larger executable size
- Need to rebuild the project

### Option B: Use Dependency Walker Tool

To identify missing DLLs on the target system:

1. Download Dependency Walker: https://www.dependencywalker.com/
2. Open your `GameStudio.exe` in the tool
3. It will show all required DLLs and which ones are missing

---

## Troubleshooting Missing DLLs

### Error: "The code execution cannot proceed because [DLL] was not found"

**Solution:**
1. Ensure all DLL files are in the same directory as `GameStudio.exe`
2. Verify you copied the correct DLL versions (32-bit vs 64-bit must match your executable)
3. Run the distribution script to auto-detect and copy DLLs

### Error: "The application was unable to start correctly (0xc000007b)"

**Solution:**
- This usually means DLL architecture mismatch (32-bit vs 64-bit)
- Ensure all DLLs and the executable are the same architecture
- Check if you're building for the correct platform

### Finding DLL Locations

**SFML DLLs:**
```powershell
# Search for SFML installation
Get-ChildItem C:\ -Filter "sfml-graphics-2.dll" -Recurse -ErrorAction SilentlyContinue
```

**MinGW DLLs:**
```powershell
# Find gcc location
where.exe gcc

# MinGW DLLs are typically in the same directory as gcc.exe
```

---

## Distribution Checklist

Before sharing your game, verify:

- [ ] `GameStudio.exe` runs on your computer
- [ ] All DLL files are included in the distribution folder
- [ ] Assets folder is included and contains all resources
- [ ] Tested the package on a different computer (if possible)
- [ ] Created a README file with instructions
- [ ] Compressed everything into a ZIP file

---

## Best Practices

1. **Always test on a clean system** (without development tools installed)
2. **Provide clear instructions** in a README file
3. **Include system requirements** (Windows version, RAM, etc.)
4. **Create a single ZIP file** for easy sharing
5. **Consider using an installer** (like NSIS or Inno Setup) for professional distribution

---

## Additional Resources

- [SFML Tutorial on Deployment](https://www.sfml-dev.org/tutorials/2.6/)
- [CMake Documentation](https://cmake.org/cmake/help/latest/)
- [MinGW Documentation](https://www.mingw-w64.org/)

---

## Quick Reference Commands

### Build Release Version (Optimized)
```batch
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Create Distribution Package
```batch
create_distribution.bat
```

### Verify DLLs on Target System
```batch
# Run this on the user's computer if they report DLL issues
dumpbin /dependents GameStudio.exe
```
