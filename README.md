# Candyland Terminal Game (C++)

## 🍬 Overview
This project is a fully playable, object-oriented implementation of a Candyland-style board game built in C++. The game runs entirely in the terminal via VS Code, with support for up to 8 players and dynamic gameplay elements including a deck of cards, a candy store, and tile-based movement logic. I was provided only the game rules and tasked with designing and implementing the full codebase from scratch.

## 🛠 Tools & Technologies
- C++ (OOP and STL)
- Visual Studio Code
- Git / GitHub for version control

## 📦 Features
- Modular object-oriented design using multiple interacting classes
- Dynamic deck of cards that influences player progression
- Candy store system for in-game decision-making or bonuses
- Navigable board with tile logic
- Support for 2–8 players
- Clear turn system and win condition logic
- Fully playable in a terminal/command-line interface

## 🧱 Architecture
The game is divided into the following core components:
- `CandyTile` class – Represents spaces on the board
- `Deck` class – Manages drawing and shuffling of cards
- `Player` class – Tracks player stats, position, and inventory
- `CandyStore` class – Allows interaction with bonus items or boosts
- `BoardNavigation` – Handles movement and tile effects

## ⚠️ Challenges & Fixes
Toward the final stages of development, I encountered a **circular dependency** between two of the core classes, which caused compiler errors. This was resolved by refactoring the code to reduce interdependencies and using forward declarations to break the cycle. Redefining function locations and managing header inclusions were key to successfully compiling and running the game.

## Code
All of the code has been added to this repository. Feel free to navigate to the Project 2 file above to take a look.
