# Ceng-209-Game-Homework
My project is a, a text-based adventure game where the player explores rooms, collects items, fights creatures. Navigate through interconnected rooms, gather resources, and defeat all creatures to win the game.
## Features
1. **Room Exploration**: 
   - Move between rooms in four directions: **up, down, left, and right**.
   - View room descriptions and available items or creatures.

2. **Inventory Management**: 
   - Pick up items found in rooms.
   - Drop items to free space in your inventory.
   - Limited inventory size ensures strategic management.

3. **Combat System**:
   - Attack creatures using weapons from your inventory.
   - Creatures retaliate, reducing player health.

4. **Healing Mechanism**:
   - Use **Health Potions** to restore health during gameplay.

5. **Save and Load**:
   - Save the current game state to a file.
   - Load the saved game to resume progress.

6. **Winning Condition**:
   - Defeat all creatures in the game to win.

### **Commands**
The game supports the following actions, triggered by entering a number:

| Command Number | Action                              |
|----------------|-------------------------------------|
| 1              | Move Up                            |
| 2              | Move Down                          |
| 3              | Move Left                          |
| 4              | Move Right                         |
| 5              | Look around the current room       |
| 6              | View inventory                     |
| 7              | Attack the creature in the room    |
| 8              | Pick up an item in the room        |
| 9              | Drop an item from the inventory    |
| 10             | Heal player using Health Potion    |
| 11             | Save the game                      |
| 12             | Load the previously saved game     |
| 13             | Exit the game                      |

### **Files**
- `main.c`: Contains the game logic, player interactions, and main loop.
- `Header.h`: Contains the structure definitions for **Player**, **Item**, **Creature**, **Room**, and **Inventory**.

### **Structures**
1. **Player**: Represents the player’s health and attributes.
2. **Item**: Represents items such as weapons and potions.
3. **Creature**: Represents enemies with health and damage stats.
4. **Room**: Represents a single room in the dungeon.
5. **Inventory**: Represents the player's inventory with a size limit.

### **Key Functions**

| Function Name          | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| `createMap()`          | Initializes the map layout with rooms and doors.                           |
| `movePlayer()`         | Handles player movement between rooms.                                     |
| `loadItems()`          | Loads item data from the `itemAttributes.txt` file.                        |
| `loadCreatures()`      | Loads creature data from the `creatureStats.txt` file.                     |
| `loadRooms()`          | Loads room descriptions and links between rooms.                           |
| `look()`               | Displays the current room description, item, and creature (if any).        |
| `pickup()`             | Picks up an item from the room if the inventory is not full.               |
| `dropItem()`           | Drops an item from the player's inventory.                                 |
| `attack()`             | Allows the player to attack creatures with weapons.                        |
| `healPlayer()`         | Uses a Health Potion to restore player health.                             |
| `saveGame()`           | Saves the current player state and inventory to a file.                    |
| `loadGame()`           | Loads the saved player state and inventory from a file.                    |
| `viewInventory()`      | Displays the player’s current inventory.          
