# Dungeon - An OOP Project

A text-based dungeon crawler game developed in C++ demonstrating Object-Oriented Programming principles. Navigate through different rooms, battle monsters, interact with NPCs, manage resources, and survive to escape the dungeon!

## Game Overview

In this adventure game, you play as a brave adventurer trapped in a dungeon. Your goal is to defeat the Demon King and escape. Along the way, you'll need to manage your health, hunger, and thirst while battling monsters, trading with NPCs, and collecting items.

### Key Features

- **Character Customization**: Allocate 2000 points among health, attack, and defense stats
- **Multiple Room Types**: Navigate through different environments (Lobby, Desert, Forest, Swamp, Castle)
- **Combat System**: Turn-based battles with attack/retreat options
- **Resource Management**: Manage hunger, thirst, and poison status effects
- **NPC Trading**: Buy items from vendors using golden coins
- **Item System**: Collect weapons, food, and special items from chests and defeated monsters
- **Environmental Hazards**: Sandstorms in deserts, poison in swamps, varying resource consumption rates

## Map Structure

```
[Room 0: Lobby Square]
        |
[Room 1: Desert] ─── [Room 2: Forest]
        |
[Room 3: Swamp] ─── [Room 4: Demon's Castle (EXIT)]
```

### Room Types & Effects

| Room Type | Hunger Cost | Thirst Cost | Special Effects                          |
| --------- | ----------- | ----------- | ---------------------------------------- |
| Normal    | -5          | -10         | None                                     |
| Desert    | -10         | -25         | Sandstorms (30% chance), Oasis discovery |
| Forest    | -20         | -5          | Lake discovery                           |
| Swamp     | -7          | -13         | Poison effect, Lotus leaf discovery      |

## Game Mechanics

### Player Stats

- **Health**: Your life points (game over when reaching 0)
- **Attack**: Damage dealt to monsters
- **Defense**: Reduces incoming damage (degrades by 30% each hit taken)
- **Hunger**: Decreases over time; at 0, lose 10 HP per turn
- **Thirst**: Decreases over time; at 0, lose 15 HP per turn + 30% miss chance
- **Poison**: Deals damage over time; cured by milk

### Combat

- Engage monsters to fight or retreat
- Defense stats degrade during combat (player: 70%, monster: 90% per hit)
- Defeat monsters to claim their loot
- Victory requires defeating the Demon King in Room 4

### Items

| Item Type    | Effect                            |
| ------------ | --------------------------------- |
| Weapons      | Boost health/attack/defense stats |
| Food         | Restore hunger/thirst             |
| Milk         | Cure poison (150 points)          |
| Chests       | Contain multiple items            |
| Golden Coins | Currency for NPC trading          |

### Monsters

| Monster           | Location | HP  | ATK | DEF | Special             |
| ----------------- | -------- | --- | --- | --- | ------------------- |
| Dead Angel        | Lobby    | 100 | 35  | 30  | -                   |
| Camel             | Desert   | -   | -   | -   | Animal (gives milk) |
| Huge Krait        | Forest   | 400 | 200 | 200 | Poison attack       |
| Ancient Crocodile | Swamp    | 500 | 230 | 150 | -                   |
| Demon the King    | Castle   | 450 | 310 | 210 | Final boss          |

## Project Structure

```
Dungeon_code/
├── main.cpp           # Entry point
├── Dungeon.cpp/hpp    # Main game controller
├── Object.cpp/hpp     # Base class (pure virtual)
├── GameCharacter.cpp/hpp  # Character base class
├── Player.cpp/hpp     # Player implementation
├── Monster.cpp/hpp    # Monster/Enemy implementation
├── NPC.cpp/hpp        # NPC trading system
├── Item.cpp/hpp       # Items and equipment
├── Room.cpp/hpp       # Room/environment system
└── Record.cpp/h       # Save/Load system (optional)
```

### Class Hierarchy

```
Object (Abstract Base)
├── Item
└── GameCharacter
    ├── Player
    ├── Monster
    └── NPC
```

## Building & Running

### Prerequisites

- C++ compiler with C++11 support (g++, clang++)
- Make

### Using Make (Recommended)

```bash
cd Dungeon_code

# Build the game
make

# Run the game
make run

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild

# Debug build (with debug symbols, no optimization)
make debug

# Release build (optimized)
make release
```

### Manual Compilation

```bash
cd Dungeon_code
g++ -std=c++11 -o dungeon main.cpp Dungeon.cpp Object.cpp GameCharacter.cpp Player.cpp Monster.cpp NPC.cpp Item.cpp Room.cpp
```

### Run

```bash
./dungeon
```

## How to Play

1. **Start**: Enter your name and allocate your 2000 stat points
2. **Navigate**: Use the action menu to move between rooms
3. **Survive**: Keep hunger and thirst above 0
4. **Fight**: Battle monsters to progress and collect loot
5. **Trade**: Find golden coins and buy items from NPCs
6. **Win**: Defeat the Demon King in Room 4 to escape!

### Controls

The game uses a numbered menu system. Simply enter the number corresponding to your desired action:

- `1` - Move/Retreat
- `2` - Check Status
- `3` - Open Backpack
- `4+` - Interact with objects in the room

## OOP Concepts Demonstrated

- **Inheritance**: `GameCharacter` extends `Object`; `Player`, `Monster`, `NPC` extend `GameCharacter`
- **Polymorphism**: Virtual `triggerEvent()` method with different implementations
- **Encapsulation**: Private member variables with getter/setter methods
- **Abstraction**: Pure virtual functions in `Object` base class
- **Composition**: Rooms contain collections of Objects; Characters have inventories of Items

## Additional Files

- `spec.pdf` - Project specification document
- `report.pdf` - Project report
- `demo.mp4` - Gameplay demonstration video
- `Dungeon.drawio` - Map/architecture diagram

## License

This project was created as a course assignment for NYCU CS.

---

_Kill all monsters and survive... Good luck, adventurer!_
