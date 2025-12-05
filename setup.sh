#!/bin/bash
# Quick Setup Script for Modular Puzzle Game Studio (Linux/macOS)

echo "========================================"
echo "Modular Puzzle Game Studio - Quick Setup"
echo "========================================"
echo

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
else
    echo "Unsupported OS"
    exit 1
fi

# Step 1: Install dependencies
echo "Step 1: Installing dependencies..."
if [ "$OS" = "linux" ]; then
    echo "Installing SFML on Linux..."
    sudo apt-get update
    sudo apt-get install -y build-essential cmake libsfml-dev
    echo "[OK] Dependencies installed"
elif [ "$OS" = "macos" ]; then
    echo "Installing SFML on macOS..."
    if command -v brew &> /dev/null; then
        brew install cmake sfml
        echo "[OK] Dependencies installed"
    else
        echo "[ERROR] Homebrew not found. Please install from https://brew.sh/"
        exit 1
    fi
fi
echo

# Step 2: Copy font
echo "Step 2: Setting up font..."
if [ -f "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf" ]; then
    cp "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf" "assets/fonts/arial.ttf"
    echo "[OK] Font copied"
elif [ -f "/System/Library/Fonts/Supplemental/Arial.ttf" ]; then
    cp "/System/Library/Fonts/Supplemental/Arial.ttf" "assets/fonts/arial.ttf"
    echo "[OK] Font copied"
else
    echo "[WARNING] Default font not found. Please manually add a .ttf file to assets/fonts/"
fi
echo

# Step 3: Build project
echo "Step 3: Building project..."
mkdir -p build
cd build
cmake ..
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu)
echo "[OK] Build complete"
echo

# Step 4: Run
echo "========================================"
echo "Setup complete! Run the game with:"
echo "  ./build/GameStudio"
echo "========================================"
