# 🍬 Candy-Land Terminal Game (C++)

## 🧠 Overview
This is a terminal-based, object-oriented board game inspired by Candyland, fully implemented in C++. The game supports up to 8 players and runs entirely in the terminal using a custom class system built from scratch. I was given only the gameplay rules and created the entire codebase — including the game flow, class structure, file I/O, and user interaction logic — independently.

## 🛠 Tools & Technologies
- C++17
- Visual Studio Code
- Git / GitHub

## 📦 Features
- Object-oriented architecture with clean separation of game logic
- Custom deck and board mechanics
- Candy store for in-game bonuses or modifiers
- Data-driven design with external text files for cards and characters
- Modular driver files for testing and demonstration
- Fully interactive terminal gameplay

## 🧱 Class Breakdown
- `Board.cpp/h`: Manages tile layout and player positioning
- `DeckOfCards.cpp/h`: Handles card generation, shuffling, and draws
- `CandyStore.cpp/h`: Contains bonus systems or player upgrades
- `Game.cpp/h`: Coordinates overall game logic and flow
- `Player.cpp/h`: Tracks player data, movement, and inventory

## 📂 Key Data Files
- `Candies.txt`: Stores candy tile descriptions or layout data
- `Characters.txt`: Contains player/character starting info

## 🧪 Driver Files
These were created to test individual systems during development:
- `Driver.cpp`: Main game entry point
- `boardDriver.cpp`, `playerDriver.cpp`, `candyStoreDriver.cpp`: Unit-level testing for major classes
- `practice.cpp`: Scratch/test space for isolated logic

## ⚠️ Challenges
A major challenge I faced was resolving a circular dependency error between two interlinked classes. This caused compile-time issues, which I resolved through forward declarations and by refactoring some function placements to break the dependency cycle.

## ▶️ How to Compile & Run
Make sure you're in the `Project 2` directory and have a C++17-compatible compiler (like `g++`):

Compile: ```g++ -std=c++17 -Wall -Werror -Wpedantic Game.cpp Player.cpp DeckOfCards.cpp Board.cpp CandyStore.cpp Driver.cpp ```
Run: ```./a.outg++ -std=c++17 *.cpp -o candyland```
```./candyland```
