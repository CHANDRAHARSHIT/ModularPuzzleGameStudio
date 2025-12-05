# Project Code Explanation & Interview Preparation

This document provides a detailed explanation of the Modular Puzzle Game Studio project, focusing on Object-Oriented Programming (OOP) concepts and Design Patterns. Use this to prepare for your interview.

## 1. Project Overview
This is a C++ game engine built with SFML that supports multiple puzzle games (Tic-Tac-Toe, Sudoku, 2048). It uses a modular architecture allowing new games to be added easily without modifying existing code.

## 2. Key OOP Concepts Used

### Encapsulation
*   **Definition**: Bundling data and methods that operate on that data within a single unit (class) and hiding internal details.
*   **In Project**: Classes like `GameManager`, `ScreenManager`, and `TicTacToeGame` encapsulate their internal state (variables) and expose only necessary methods (`public` interface) while keeping data `private`.

### Inheritance
*   **Definition**: A mechanism where a new class derives properties and behavior from an existing class.
*   **In Project**: `TicTacToeGame`, `SudokuGame`, and `Puzzle2048Game` all inherit from the base class `Game`. They "are a" `Game`.

### Polymorphism
*   **Definition**: The ability of different classes to be treated as instances of the same general class through a common interface.
*   **In Project**: The `GameManager` holds a pointer to `Game` (`std::unique_ptr<Game>`). It calls `update()` and `render()` on this pointer, and the specific version for the active game (Tic-Tac-Toe, Sudoku, etc.) is executed at runtime. This is **Runtime Polymorphism** (Virtual Functions).

### Abstraction
*   **Definition**: Hiding complex implementation details and showing only the necessary features of an object.
*   **In Project**: The `Game` class is an **Abstract Base Class** (Interface). It defines *what* a game must do (`init`, `update`, `render`) but not *how*.

---

## 3. Design Patterns

### Factory Pattern
*   **Purpose**: Creates objects without specifying the exact class of object that will be created.
*   **Implementation**: `GameFactory` class. It allows creating games by string name ("Tic-Tac-Toe") rather than hardcoding `new TicTacToeGame()`.

### Observer Pattern
*   **Purpose**: Defines a subscription mechanism to notify multiple objects about any events that happen to the object they're observing.
*   **Implementation**: `Subject` (the publisher) and `Observer` (the subscriber). When a game ends, the `Subject` notifies the `ScoreBoard` (an `Observer`) to record the score.

### Strategy Pattern
*   **Purpose**: Enables selecting an algorithm at runtime.
*   **Implementation**: `MoveStrategy` in the AI system. The AI can switch between different strategies (e.g., Random Move vs. Smart Move) without changing the game logic.

---

## 4. Line-by-Line Code Explanation

### A. `include/core/Game.hpp` (Abstraction & Polymorphism)

```cpp
class Game {
public:
    virtual ~Game() = default; // Virtual destructor ensures proper cleanup of derived classes
    
    // Pure Virtual Functions (= 0) make this an Abstract Class
    virtual std::string getName() const = 0; 
    virtual void init() = 0;
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isOver() const = 0;
};
```

*   **Interview Explanation**: "This file defines the `Game` interface. It uses **Pure Virtual Functions** (denoted by `= 0`), which forces any class inheriting from `Game` to implement these specific methods. This guarantees that the `GameManager` can treat any game exactly the same way, regardless of whether it's Tic-Tac-Toe or Sudoku."

### B. `include/core/GameFactory.hpp` (Factory Pattern)

```cpp
class GameFactory {
public:
    // Defines a function type that returns a unique_ptr to a Game
    using Creator = std::function<std::unique_ptr<Game>()>;

private:
    // Maps a string (e.g., "Tic-Tac-Toe") to a function that creates it
    std::unordered_map<std::string, Creator> registry;

public:
    void registerGame(const std::string& name, Creator creator);
    std::unique_ptr<Game> create(const std::string& name) const;
};
```

*   **Interview Explanation**: "This is the **Factory Pattern**. Instead of using `if-else` statements to create games, I register them in a map. When the user selects a game, the `create` method looks up the name and calls the corresponding function to instantiate the game. This adheres to the **Open/Closed Principle**—I can add new games without modifying the factory's logic."

### C. `src/main.cpp` (Putting it together)

```cpp
int main() {
    // 1. Observer Pattern Setup
    Subject gameSubject;
    ScoreBoard scoreBoard("scores.txt");
    gameSubject.addObserver(&scoreBoard); // ScoreBoard listens to game events

    // 2. Factory Pattern Setup
    GameFactory factory;
    // Lambda function used to register the creation logic
    factory.registerGame("Tic-Tac-Toe", [&gameSubject]() {
        return std::make_unique<TicTacToeGame>(&gameSubject);
    });
    
    // ... (Registration of other games)

    // 3. Game Loop
    while (window.isOpen()) {
        // Polymorphism in action: screenManager handles the current screen
        // regardless of what specific screen it is.
        screenManager.update(dt);
        screenManager.render(window);
    }
}
```

*   **Interview Explanation**: "In `main`, I wire everything together. I create the `Subject` for the Observer pattern so scores can be tracked. I register games into the `GameFactory`. Then I enter the main game loop, which delegates updates and rendering to the `ScreenManager`."

### D. `include/games/TicTacToeGame.hpp` (Inheritance)

```cpp
class TicTacToeGame : public Game { // Inherits from Game
private:
    Grid<char> board; // Composition: Game HAS-A Grid
    Subject* subject; // Association: Game knows about Subject
    std::unique_ptr<MoveStrategy<Grid<char>>> aiStrategy; // Strategy Pattern

public:
    // Overrides the pure virtual functions from the base class
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    // ...
};
```

*   **Interview Explanation**: "Here, `TicTacToeGame` inherits from `Game`, implementing the specific logic for this game. It uses **Composition** by containing a `Grid` object for the board. It also holds a pointer to an `AIStrategy`, allowing the AI behavior to be swapped out easily."

### E. `include/core/Grid.hpp` (Templates & Generic Programming)

```cpp
template<typename T>
class Grid {
private:
    std::vector<T> data;
    // ...
public:
    Grid(size_t r, size_t c, const T& v = T()) ...
    // ...
};
```

*   **Interview Explanation**: "This class uses **C++ Templates** to create a generic Grid. This means I can have a `Grid<char>` for Tic-Tac-Toe, a `Grid<int>` for Sudoku, or a `Grid<Tile>` for 2048, all using the same code. This promotes **Code Reusability** and avoids code duplication."

### F. `include/ai/MoveStrategy.hpp` (Strategy Pattern & Templates)

```cpp
template<typename BoardType>
class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;
    virtual void makeMove(BoardType& board, char symbol) = 0;
};
```

*   **Interview Explanation**: "This combines the **Strategy Pattern** with **Templates**. It defines an interface for an AI move algorithm. Because it's templated, it can work with any type of board (Tic-Tac-Toe board, etc.). Concrete strategies (like `TicTacToeRandomAI`) implement this interface to define specific behaviors."

---

## 5. Potential Counter-Questions & Answers

**Q: Why use `std::unique_ptr` instead of raw pointers?**
*   **A**: "To manage memory automatically (RAII). `unique_ptr` ensures that the game object is deleted when it goes out of scope or is replaced, preventing memory leaks. It also expresses exclusive ownership."

**Q: Why is the destructor in `Game` virtual?**
*   **A**: "If I delete a derived object (like `TicTacToeGame`) through a base pointer (`Game*`), a non-virtual destructor would only call the base class destructor, potentially leaking memory allocated by the derived class. Making it virtual ensures the correct destructor is called."

**Q: How would you add a new game, say 'Chess'?**
*   **A**: "I would create a `ChessGame` class that inherits from `Game` and implements the required methods. Then, in `main.cpp`, I would simply register it with the factory: `factory.registerGame("Chess", ...);`. No other existing code needs to change."

**Q: What is the benefit of the Observer pattern here?**
*   **A**: "It decouples the Game logic from the ScoreBoard. The Game doesn't need to know *how* scores are saved or displayed; it just notifies the Subject that the game ended. This makes the system more modular and easier to test."
l