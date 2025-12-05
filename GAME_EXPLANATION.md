# How the Modular Puzzle Game Studio Works

## What is this Game?
This is a **game collection** that includes multiple puzzle games like Tic-Tac-Toe, 2048, and Sudoku all in one application. It's built using C++ and SFML (Simple and Fast Multimedia Library) for graphics.

## How Everything Works Together

### 1. The Main Menu System
When you start the game, you see a main menu with options like:
- Play Games (Tic-Tac-Toe, 2048, Sudoku)
- Settings
- Scoreboard
- Exit

Think of it like a **TV remote** - the main menu lets you switch between different "channels" (games).

### 2. Game Flow
```
Start App → Main Menu → Choose Game → Play → Back to Menu
```

## Object-Oriented Programming (OOP) Concepts Used

### 1. **Classes and Objects** 
**What it is**: A class is like a blueprint, an object is the actual thing built from that blueprint.

**In our game**:
- `TicTacToeGame` class = blueprint for how Tic-Tac-Toe works
- When you click "Play Tic-Tac-Toe", we create an **object** from this class

**Real-world example**: 
- Class = Car blueprint (has wheels, engine, doors)
- Object = Your actual Toyota Camry sitting in the driveway

### 2. **Inheritance**
**What it is**: Child classes get features from parent classes, like how children inherit traits from parents.

**In our game**:
```
Game (Parent Class)
├── TicTacToeGame (Child)
├── Puzzle2048Game (Child)
└── SudokuGame (Child)
```

All games inherit basic features like:
- `getName()` - what's the game called?
- `render()` - how to draw on screen
- `handleEvent()` - what happens when you click/press keys

**Real-world example**: All vehicles have wheels and engines, but a car has 4 wheels while a motorcycle has 2.

### 3. **Polymorphism**
**What it is**: Different objects can respond to the same command in their own way.

**In our game**:
When we say "render()" (draw yourself):
- Tic-Tac-Toe draws a 3x3 grid
- 2048 draws numbered tiles
- Sudoku draws a 9x9 puzzle

**Real-world example**: When you say "make sound" to different animals:
- Dog says "woof"
- Cat says "meow"
- Cow says "moo"

### 4. **Encapsulation**
**What it is**: Keeping data safe inside classes and only allowing controlled access.

**In our game**:
- Game board data is **private** inside the TicTacToe class
- You can't directly mess with the board
- You must use proper methods like `handleClick()` to make moves

**Real-world example**: Your bank account balance is private - you can't directly change it, you must use ATM or bank teller (proper methods).

### 5. **Exception Handling** (Error Management)
**What it is**: A way to handle errors gracefully instead of crashing the program.

**Why we SHOULD use it more in our game**:
- What if the font file doesn't exist? (Currently we just use a backup font)
- What if save file is corrupted? (Currently might crash)
- What if invalid moves are made? (Currently we just ignore them)

**How it SHOULD work**:
```cpp
try {
    font.loadFromFile("assets/fonts/arial.ttf");
} catch (FileNotFoundException& e) {
    // Use system font instead
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
} catch (std::exception& e) {
    // Log error and use default rendering
}
```

**Real-world example**: When you try to withdraw money but account is empty, the ATM doesn't break - it shows an error message and lets you try again.

**Current limitations in our game**: We use basic error checking (like `if (!font.loadFromFile())`) but don't have proper exception handling for serious errors.

## Design Patterns Used

### 1. **Strategy Pattern** (AI System)
**What it does**: Lets you swap different strategies/algorithms easily.

**In our game**: 
- We have `TicTacToeRandomAI` that makes random moves
- We could easily add `TicTacToeSmartAI` without changing the game code
- The game just says "AI, make your move" and doesn't care which AI is being used

**Real-world example**: GPS navigation can use different routes (fastest, shortest, scenic) but the car doesn't need to know which strategy is chosen.

### 2. **Observer Pattern** (Score Tracking)
**What it does**: When something important happens, automatically notify all interested parties.

**In our game**:
- When a game ends, the `Subject` notifies the `ScoreBoard`
- The scoreboard automatically updates without the game knowing about it
- It's like a news subscription - when news happens, all subscribers get notified

**Real-world example**: When you score in a soccer game, the scoreboard automatically updates, the announcer talks, and stats are recorded - all without the player doing anything extra.

### 3. **Factory Pattern** (Game Creation)
**What it does**: Creates objects without specifying exactly which class to create.

**In our game**:
```cpp
GameFactory::createGame("TicTacToe") // Returns TicTacToeGame object
GameFactory::createGame("2048")      // Returns Puzzle2048Game object
```

**Real-world example**: When you order "a sandwich" at a restaurant, the kitchen decides whether to make turkey, ham, or veggie based on what you specify - you don't need to know the exact recipe.

### 4. **Template Pattern** (Grid System)
**What it does**: Uses the same structure for different types of data.

**In our game**:
- `Grid<char>` for Tic-Tac-Toe (stores X, O, or empty)
- `Grid<int>` for 2048 (stores numbers like 2, 4, 8, 16...)
- Same grid behavior, different data types

**Real-world example**: An ice cube tray works the same way whether you put water, juice, or coffee in it.

## File Organization

### Core Files (The Engine)
- **`main.cpp`**: Starts everything, like turning on your computer
- **`GameManager.cpp`**: Controls which game is running, like a traffic controller
- **`ScreenManager.cpp`**: Switches between different screens (menu, game, settings)

### Game Files (The Fun Stuff)
- **`TicTacToeGame.cpp`**: All the logic for Tic-Tac-Toe
- **`Puzzle2048Game.cpp`**: All the logic for 2048 puzzle
- **`SudokuGame.cpp`**: All the logic for Sudoku

### UI Files (What You See)
- **`MainMenuScreen.cpp`**: The main menu you see when you start
- **`SettingsScreen.cpp`**: Options and preferences
- **`ScoreBoardScreen.cpp`**: Shows your high scores

### Helper Files (Behind the Scenes)
- **`Grid.hpp`**: Manages game boards (like a smart spreadsheet)
- **`FileManager.cpp`**: Saves and loads game data
- **`ScoreBoard.cpp`**: Keeps track of your scores

## How AI Works (Simple Version)

1. **It's your turn**: You click a square in Tic-Tac-Toe
2. **Game checks**: Is this move valid? (empty square?)
3. **Your move is made**: X appears on the board
4. **AI's turn**: The `TicTacToeRandomAI` looks at all empty squares
5. **AI chooses**: Picks one randomly
6. **AI moves**: O appears on the board
7. **Check winner**: Did anyone win? If not, back to your turn

## How Everything Connects

```
You Click Button
       ↓
ScreenManager sees the click
       ↓
Creates the right game object
       ↓
Game starts running
       ↓
You play, AI responds
       ↓
Game ends, score is saved
       ↓
Back to main menu
```

## Why This Design is Good

### 1. **Easy to Add New Games**
- Want to add Chess? Just create `ChessGame.cpp` following the same pattern
- No need to change existing code

### 2. **Easy to Fix Bugs**
- Bug in Tic-Tac-Toe? Only look in `TicTacToeGame.cpp`
- Won't accidentally break other games

### 3. **Easy to Add Features**
- Want better AI? Just create new AI class and swap it in
- Want online scores? Just add new observer to the system

### 4. **Code Reuse**
- The same Grid system works for all board games
- The same Screen system works for all menus
- Don't write the same code twice

### 5. **Missing: Proper Exception Handling**
- **Current problem**: Game might crash if files are missing or corrupted
- **What we should add**: Try-catch blocks for file loading, memory allocation, and invalid operations
- **Benefits**: Game would be more stable and user-friendly
- **Example**: If high scores file is corrupted, show error message instead of crashing

## What Could Be Improved

### Exception Handling We Should Add:
1. **File Operations**: What if save files are corrupted or missing?
2. **Memory Management**: What if we run out of memory for large grids?
3. **User Input Validation**: What if someone enters invalid data?
4. **Network Operations**: If we add online features, what if connection fails?

### Example of Better Error Handling:
```cpp
// Current way (basic):
if (!font.loadFromFile("assets/fonts/arial.ttf")) {
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

// Better way (with exceptions):
try {
    font.loadFromFile("assets/fonts/arial.ttf");
} catch (FileNotFoundException& e) {
    try {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    } catch (FileNotFoundException& e2) {
        throw GameInitializationException("No fonts available");
    }
} catch (std::bad_alloc& e) {
    throw GameInitializationException("Not enough memory for fonts");
}
```

## Summary in Simple Terms

This game is like a **well-organized toy box**:
- Each game is in its own compartment (classes)
- There are rules for how toys work together (inheritance)
- Some toys can do similar things in different ways (polymorphism)
- The toys are protected from being broken (encapsulation)
- There are smart systems that help manage everything (design patterns)

The whole thing is designed so that adding new games or features is like adding new toys to the box - everything has its place and works together nicely!