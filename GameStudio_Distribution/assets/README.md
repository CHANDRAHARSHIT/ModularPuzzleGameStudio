# Assets Directory

This directory contains game assets such as fonts and images.

## Required Files

### Fonts
Place a TrueType font file (e.g., `arial.ttf`) in the `fonts/` subdirectory.

**Option 1:** Copy from Windows:
```
copy C:\Windows\Fonts\arial.ttf assets\fonts\arial.ttf
```

**Option 2:** Download a free font from:
- Google Fonts: https://fonts.google.com/
- Font Squirrel: https://www.fontsquirrel.com/

### Images (Optional)
Future enhancements may include:
- Game icons
- Background images
- Button graphics
- Splash screens

## Current Status

The application will attempt to load fonts from:
1. `assets/fonts/arial.ttf` (preferred)
2. System font path: `C:/Windows/Fonts/arial.ttf` (Windows fallback)

If no font is found, text rendering may fail. Please ensure at least one font file is available.
