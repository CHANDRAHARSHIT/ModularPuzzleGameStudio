# Modular Puzzle Game Studio

A comprehensive C++ game framework demonstrating Object-Oriented Programming principles and design patterns using SFML graphics library.

## 🎮 Features

- **Multiple Games**: Tic-Tac-Toe, Sudoku, and 2048 Puzzle
- **Design Patterns**: Factory, Strategy, Observer, Template, and Manager patterns
- **Modular Architecture**: Easy to extend with new games
- **Score Tracking**: Persistent score storage with observer notifications
- **Modern C++**: C++17 features including smart pointers, templates, and optional

## 📁 Project Structure

```
ModularPuzzleGameStudio/
├── include/
│   ├── core/          # Core game engine interfaces and managers
│   ├── games/         # Game implementations
│   ├── ai/            # AI strategies
│   ├── observer/      # Observer pattern components
│   ├── util/          # Utility classes
│   └── ui/            # User interface screens
├── src/               # Implementation files (.cpp)
├── assets/
│   ├── fonts/         # Font files
│   └── images/        # Image assets
└── CMakeLists.txt     # Build configuration
```

## 🏗️ Architecture

### Core Components

- **Game**: Abstract base class for all games
- **GameManager**: Manages game lifecycle and main loop
- **GameFactory**: Creates game instances using Factory pattern
- **Screen**: Abstract base class for UI screens
- **ScreenManager**: Handles screen transitions
- **Grid<T>**: Generic 2D grid template for game boards

### Design Patterns

1. **Factory Pattern**: `GameFactory` dynamically creates game instances
2. **Strategy Pattern**: `MoveStrategy<T>` for AI implementations
3. **Observer Pattern**: `Subject`/`Observer` for game event notifications
4. **Template Pattern**: `Grid<T>` and `MoveStrategy<T>` for type-safe generics

### Games Implemented

1. **Tic-Tac-Toe**: Classic 3x3 game with win/draw detection
2. **Sudoku**: 9x9 puzzle with validation
3. **2048**: Tile-merging puzzle game

## 🔧 Prerequisites

- **C++ Compiler**: GCC 7+, Clang 6+, or MSVC 2017+
- **CMake**: Version 3.10 or higher
- **SFML**: Version 2.5 or higher

## 📦 Installing SFML

### Windows (Using vcpkg)
```powershell
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg install sfml:x64-windows
```

### Windows (Manual)
1. Download SFML from https://www.sfml-dev.org/download.php
2. Extract to `C:\SFML`
3. Update CMakeLists.txt with the correct path

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

### macOS
```bash
brew install sfml
```

## 🚀 Building the Project

### Using CMake

```bash
cd ModularPuzzleGameStudio
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows with Visual Studio

```powershell
cd ModularPuzzleGameStudio
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
```

### Manual Compilation (if CMake not preferred)

```bash
g++ -std=c++17 -Iinclude src/**/*.cpp src/main.cpp -o GameStudio -lsfml-graphics -lsfml-window -lsfml-system
```

## 🎯 Usage

Run the executable:

```bash
./GameStudio          # Linux/macOS
GameStudio.exe        # Windows
```

### Controls

**Main Menu:**
- ↑/↓ Arrow keys: Navigate menu
- Enter: Select option
- ESC: Exit to main menu

**Tic-Tac-Toe:**
- Mouse click: Place X/O

**Sudoku:**
- Mouse click: Select cell
- Number keys (1-9): Enter number
- Delete/Backspace: Clear cell

**2048:**
- Arrow keys or WASD: Move tiles

## 🧪 Adding New Games

1. Create header file in `include/games/YourGame.hpp`
2. Inherit from `Game` interface
3. Implement all virtual methods
4. Create implementation in `src/games/YourGame.cpp`
5. Register in `main.cpp`:

```cpp
factory.registerGame("YourGame", [&gameSubject]() {
    return std::make_unique<YourGame>(&gameSubject);
});
```

## 📊 OOP Principles Demonstrated

- **Encapsulation**: Private members with public interfaces
- **Inheritance**: Game and Screen hierarchies
- **Polymorphism**: Virtual functions for runtime behavior
- **Abstraction**: Abstract base classes (Game, Screen, Observer)
- **Composition**: Managers compose and coordinate components
- **SOLID Principles**: Single responsibility, open-closed, dependency inversion

## 📄 License

This project is created for educational purposes to demonstrate OOP concepts and design patterns.

## 🤝 Contributing

This is an educational project. Feel free to:
- Add new games
- Implement new AI strategies
- Enhance UI/UX
- Optimize performance

## 📚 Learning Resources

- Design Patterns: "Design Patterns" by Gang of Four
- Modern C++: "Effective Modern C++" by Scott Meyers
- SFML Documentation: https://www.sfml-dev.org/documentation/

## 🐛 Known Issues

- Font files must be present in `assets/fonts/` or the system will fall back to system fonts
- Windows users may need to copy SFML DLLs to the executable directory

## 👥 Authors

Created as an Object-Oriented Programming project demonstrating:
- Clean code architecture
- Design pattern implementation
- Modern C++ best practices
- Game development fundamentals

---

**Happy Gaming! 🎮**
