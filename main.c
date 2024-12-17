#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

char board[HEIGHT*2][WIDTH*2];
int playerCurrentRoomID = 1;
Item items[3];
Creature creatures[2];
Room rooms[4];

void printMap() {
    for (int i=0; i<HEIGHT*2; i++) {
        for (int j=0; j<WIDTH*2; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void createMap() {

    int playerX = HEIGHT/2, playerY = WIDTH/2;
    for (int row=0; row<HEIGHT*2; row++) {
        for (int col=0; col<WIDTH*2; col++) {
            if (row==0 || row==HEIGHT*2-1 || col==0 || col==WIDTH*2-1) {
                board[row][col] = WALL;
            } else if (row % HEIGHT == 0 || col % WIDTH==0) {
                board[row][col] = WALL;
            } else {
                board[row][col] = EMPTY;
            }
        }
    }


    for (int roomRow=0; roomRow<2; roomRow++) {
        for (int roomCol=0; roomCol<2; roomCol++) {
            int roomTopLeftRow = roomRow * HEIGHT;
            int roomTopLeftCol = roomCol * WIDTH;

            if (roomRow<1) {
                for (int col = roomTopLeftCol; col < roomTopLeftCol + WIDTH; col++) {
                    board[roomTopLeftRow + HEIGHT][col] = WALL;
                }
                board[roomTopLeftRow + HEIGHT][roomTopLeftCol + WIDTH / 2] = DOOR;
            }

            if (roomCol<1) {
                for (int row = roomTopLeftRow; row < roomTopLeftRow + HEIGHT; row++) {
                    board[row][roomTopLeftCol + WIDTH] = WALL;
                }
                board[roomTopLeftRow + HEIGHT / 2][roomTopLeftCol + WIDTH] = DOOR;
            }
        }
    }
    board[playerX][playerY] = PLAYER;
}

void movePlayer(char direction,int roomId) {
    int playerXRoom1 = HEIGHT/2, playerYRoom1 = WIDTH/2;
    int playerXRoom2 = HEIGHT/2, playerYRoom2 = WIDTH+4;
    int playerXRoom3 = HEIGHT+2, playerYRoom3 = WIDTH/2;
    int playerXRoom4 = HEIGHT+2, playerYRoom4 = WIDTH+4;

    if (roomId == 1) {
        if(direction == 'd') {
            board[playerXRoom1][playerYRoom1] = ' ';
            board[playerXRoom3][playerYRoom3] = PLAYER;
            playerCurrentRoomID = 3;
            printf("You moved from Dungeon Room to Goblin Room!\n");
        }
        else if (direction == 'r') {
            board[playerXRoom1][playerYRoom1] = ' ';
            board[playerXRoom2][playerYRoom2] = PLAYER;
            playerCurrentRoomID = 2;
            printf("You moved from Dungeon Room to Sword Room!\n");
        }
        else
            printf("You cant move here!!!\n");
    }

    else if (roomId == 2) {
        if (direction == 'l') {
            board[playerXRoom2][playerYRoom2] = ' ';
            board[playerXRoom1][playerYRoom1] = PLAYER;
            playerCurrentRoomID = 1;
            printf("You moved from Sword Room to Dungeon Room!\n");
        }
        else if (direction == 'd') {
            board[playerXRoom2][playerYRoom2] = ' ';
            board[playerXRoom4][playerYRoom4] = PLAYER;
            playerCurrentRoomID = 4;
            printf("You moved from Sword Room to End Room!\n");
        }
        else
            printf("You cant move here!!!\n");
    }
    else if (roomId == 3) {
        if (direction == 'u') {
            board[playerXRoom3][playerYRoom3] = ' ';
            board[playerXRoom1][playerYRoom1] = PLAYER;
            playerCurrentRoomID = 1;
            printf("You moved from Goblin Room to Dungeon Room!\n");
        }
        else if (direction == 'r') {
            board[playerXRoom3][playerYRoom3] = ' ';
            board[playerXRoom4][playerYRoom4] = PLAYER;
            playerCurrentRoomID = 4;
            printf("You moved from Goblin Room to End Room!\n");
        }
        else
            printf("You cant move here!!!\n");
    }
    else if (roomId == 4) {
        if (direction == 'l') {
            board[playerXRoom4][playerYRoom4] = ' ';
            board[playerXRoom3][playerYRoom3] = PLAYER;
            playerCurrentRoomID = 3;
            printf("You moved from End Room to Goblin Room!\n");
        }
        else if (direction == 'u') {
            board[playerXRoom4][playerYRoom4] = ' ';
            board[playerXRoom2][playerYRoom2] = PLAYER;
            playerCurrentRoomID = 2;
            printf("You moved from End Room to Sword Room!\n");
        }
        else
            printf("You cant move here!!!\n");
    }
}

void loadItems() {

    FILE *file = fopen("itemAttributes.txt", "r");
    if (file==NULL) {
        printf("Error: Could not openo file\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        char name[40], type[20];
        int damage, weight, currentRoomID;
        Item *item = (Item *)malloc(sizeof(Item));
        if (item==NULL){
            printf("Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        sscanf(line, "%d|%[^|]|%d|%[^|]|%d", &currentRoomID, name, &damage, type, &weight);
        item->name = strdup(name);
        item->type = strdup(type);
        item->damage = damage;
        item->weight = weight;
        item->currentRoomID = currentRoomID;
        items[count++] = *item;
        free(item);
    }

    fclose(file);
}

void loadCreatures() {

    FILE *file = fopen("creatureStats.txt", "r");
    if (file==NULL) {
        printf("Error: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        char name[40];
        int maxHealth, damage, currentRoomID;
        Creature *creature = (Creature *)malloc(sizeof(Creature));
        if (creature==NULL){
            printf("Error: Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        sscanf(line, "%d|%[^|]|%d|%d", &currentRoomID, name, &maxHealth, &damage);
        creature->name = strdup(name);
        creature->damage = damage;
        creature->maxHealth = maxHealth;
        creature->currentRoomID = currentRoomID;
        creature->health = maxHealth;
        creatures[count++] = *creature;
        free(creature);
    }

    fclose(file);
}

void loadRooms() {
    FILE *file = fopen("roomDescriptions.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int roomCount = 0;

    while (fgets(line, sizeof(line), file)) {
        char name[40], description[200];
        int id;

        sscanf(line, "%d|%[^|]|%[^|]", &id, name, description);

        Room *room = &rooms[roomCount];
        room->id = id;
        room->name = strdup(name);
        room->description = strdup(description);
        room->up = NULL;
        room->down = NULL;
        room->left = NULL;
        room->right = NULL;
        room->creature = NULL;
        room->item = NULL;
        roomCount++;
    }

    fclose(file);

    rooms[0].right = &rooms[1];
    rooms[0].down = &rooms[2];
    rooms[0].item = &items[0];

    rooms[1].left = &rooms[0];
    rooms[1].down = &rooms[3];
    rooms[1].item = &items[1];

    rooms[2].up = &rooms[0];
    rooms[2].right = &rooms[3];
    rooms[2].item = &items[2];
    rooms[2].creature = &creatures[0];

    rooms[3].up = &rooms[1];
    rooms[3].left = &rooms[2];
    rooms[3].creature = &creatures[1];
}

void look(int roomID){

    Room *room = &rooms[roomID-1];
    printf("You look at the room %d!\n", room->id);
    printf("%s", room->description);
    printf("Item: %s\n", room->item ? room->item->name : "There are no items in this room");
    if (room->creature == NULL || room->creature->name == NULL) {
        printf("Creature: There are no creatures in this room\n");
    } else {
        printf("Creature: %s\n", room->creature->name);
    }

}

void pickup(Inventory *inventory, int roomID) {

    if (roomID<=0 || roomID>4) {
        printf("Invalid room ID.\n");
        return;
    }
    Room *room = &rooms[roomID - 1];

    if (room->item == NULL) {
        printf("There are no items in this room to pick up.\n");
        return;
    }

    if (inventory->itemCount >= MAX_INVENTORY) {
        printf("Your inventory is full! Drop an item to pick up a new one.\n");
        return;
    }

    inventory->itemsInInventory[inventory->itemCount++] = room->item;

    printf("You picked up: %s\n", room->item->name);

    room->item = NULL;
}

void viewInventory(const Inventory *inventory) {
    if (inventory->itemCount == 0) {
        printf("There are no items in your inventory.\n");
        return;
    }

    printf("Items in your inventory:\n");
    for (int i = 0; i < inventory->itemCount; i++) {
        printf("%d. %s (Type: %s, Damage: %d, Weight: %d)\n",
        i+1,
        inventory->itemsInInventory[i]->name,
        inventory->itemsInInventory[i]->type,
        inventory->itemsInInventory[i]->damage,
        inventory->itemsInInventory[i]->weight);
    }
}
void dropItem(Inventory *inventory, char itemName[10]) {

    int itemIndex = -1;
    for (int i=0; i<inventory->itemCount; i++) {
        if (strcmp(inventory->itemsInInventory[i]->name, itemName) == 0) {
            itemIndex = i;
            break;
        }
    }

    if (itemIndex==-1) {
        printf("Item '%s' is not in your inventory.\n", itemName);
        return;
    }

    for (int i=itemIndex; i<inventory->itemCount-1; i++) {
        inventory->itemsInInventory[i]=inventory->itemsInInventory[i + 1];
    }
    inventory->itemCount--;

    printf("You dropped: %s\n", itemName);
}

void attack(Player *player, const Inventory *inventory, Creature *creature) {
    if (creature==NULL || creature->health<=0) {
        printf("There is no creature here to attack!\n");
        return;
    }

    printf("Select a weapon to attack with:\n");
    for (int i=0; i<inventory->itemCount; i++) {
        if (strcmp(inventory->itemsInInventory[i]->type, "Weapon") == 0) {
            printf("%d. %s (Damage: %d)\n", i+1, inventory->itemsInInventory[i]->name, inventory->itemsInInventory[i]->damage);
        }
    }

    int choice;
    printf("Enter the weapon number: ");
    scanf("%d", &choice);
    printf("\n");

    if (choice < 1 || choice > inventory->itemCount || strcmp(inventory->itemsInInventory[choice - 1]->type, "Weapon") != 0) {
        printf("Invalid choice! Attack aborted.\n");
        return;
    }

    Item *weapon = inventory->itemsInInventory[choice - 1];
    printf("You attack the %s with %s, dealing %d damage!\n", creature->name, weapon->name, weapon->damage);
    creature->health -= weapon->damage;

    if (creature->health <= 0) {
        printf("You defeated the %s!\n", creature->name);
        rooms[playerCurrentRoomID-1].creature->name=NULL;
        return;
    }

    printf("The %s retaliates, dealing %d damage to you!\n", creature->name, creature->damage);
    player->health -= creature->damage;

    if (player->health <= 0) {
        printf("You have been defeated by the %s...\n", creature->name);
        return;
    }
    printf("Your current health: %d\n", player->health);
    printf("The %s's current health: %d\n", creature->name, creature->health);
    printf("\n");
}

void healPlayer(Player *player, Inventory *inventory) {

    int potionIndex=-1;
    for (int i=0; i<inventory->itemCount; i++) {
        if (strcmp(inventory->itemsInInventory[i]->name, "Health Potion") == 0) {
            potionIndex = i;
            break;
        }
    }

    if (potionIndex == -1) {
        printf("You don't have any Health Potions in your inventory!\n");
        return;
    }

    printf("You used a Health Potion! Your health is restored by 10 points.\n");
    player->health += 10;
    if (player->health > player->maxHealth) {
        player->health = player->maxHealth;
    }

    for (int i=potionIndex; i<inventory->itemCount-1; i++) {
        inventory->itemsInInventory[i]=inventory->itemsInInventory[i+1];
    }
    inventory->itemCount--;

    printf("Your current health: %d/%d\n", player->health, player->maxHealth);
}

void saveGame(Player *player, Inventory *inventory) {
    FILE *file = fopen("savedGames.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    fprintf(file, "Player Health: %d/%d\n", player->health, player->maxHealth);

    fprintf(file, "Inventory:\n");
    for (int i=0; i<inventory->itemCount; i++) {
        Item *item = inventory->itemsInInventory[i];
        fprintf(file, "- %s,%d,%s,%d,%d\n", item->name, item->damage, item->type, item->weight, item->currentRoomID);
    }

    fclose(file);
    printf("Game saved to %s\n", "savedGames.txt file");
}

void loadGame(Player *player, Inventory *inventory) {
    FILE *file = fopen("savedGames.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file for loading.\n");
        return;
    }

    fscanf(file, "Player Health: %d/%d\n", &player->health, &player->maxHealth);

    char line[256];
    inventory->itemCount = 0;
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '-') {
            Item *item = malloc(sizeof(Item));
            if (!item) {
                printf("Error: Memory allocation failed for item.\n");
                fclose(file);
                return;
            }

            char tempName[50], tempType[20];
            sscanf(line, "- %[^,],%d,%[^,],%d,%d\n", tempName, &item->damage, tempType, &item->weight, &item->currentRoomID);

            item->name = malloc(strlen(tempName) + 1);
            if (!item->name) {
                printf("Error: Memory allocation failed for item name.\n");
                free(item);
                fclose(file);
                return;
            }
            strcpy(item->name, tempName);

            item->type = malloc(strlen(tempType) + 1);
            if (!item->type) {
                printf("Error: Memory allocation failed for item type.\n");
                free(item->name);
                free(item);
                fclose(file);
                return;
            }
            strcpy(item->type, tempType);
            inventory->itemsInInventory[inventory->itemCount++] = item;
        } else {
            break;
        }
    }
    fclose(file);

    file = fopen("savedGames.txt", "w");
    if (file != NULL) {
        fclose(file);
    } else {
        printf("Error: Could not clear the saved game file.\n");
    }

    printf("Game loaded and saved game cleared from %s\n", "savedGames.txt");
}

void listSavedGame() {
    FILE *file = fopen("savedGames.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open saved games file.\n");
        return;
    }
    char line[256];

    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Player Health:", 14) == 0) {
            found = 1;
            printf("\n--- Saved Game ---\n");
        }
        printf("%s", line);
    }

    if (!found) {
        printf("No saved games found in the file.\n");
    }
    fclose(file);
}


int main(void) {

    Player *player = (Player *)malloc(sizeof(Player));
    player->name = "Player";
    player->maxHealth = 100;
    player->health = 100;
    player->strength = 0;
    Inventory *inventory = (Inventory *)malloc(sizeof(Inventory));
    inventory->itemCount = 0;
    createMap();
    loadItems();
    loadCreatures();
    loadRooms();

    printf("Welcome to the adventure game!\n");
    printf("\n");
    printf("You will start at dungeon room\n");

    printMap();
    printf("Available commands:\n");
    printf("1. move up\n");
    printf("2. move down\n");
    printf("3. move left\n");
    printf("4. move right\n");
    printf("5. look room\n");
    printf("6. look inventory\n");
    printf("7. attack\n");
    printf("8. pick up item\n");
    printf("9. drop item from inventory\n");
    printf("10. heal player using Health Potion\n");
    printf("11. save game(only one game can be saved)\n");
    printf("12. load saved game\n");
    printf("13. exit game\n");
    printf("=========================\n");

    int input=-1;
    while(1) {
    printf("What would you like to do? Enter number: \n");
        if (scanf("%d", &input) != 1) {
            printf("You entered invalid input.\n");
            while (getchar() != '\n') {}
            continue;
        }
    switch (input) {
        case 1:
            movePlayer('u',playerCurrentRoomID);
            printMap();
        break;
        case 2:
            movePlayer('d',playerCurrentRoomID);
            printMap();
        break;
        case 3:
            movePlayer('l',playerCurrentRoomID);
            printMap();
        break;
        case 4:
            movePlayer('r',playerCurrentRoomID);
            printMap();
        break;
        case 5:
            look(playerCurrentRoomID);
        break;
        case 6:
            viewInventory(inventory);
        break;
        case 7:
            if(inventory->itemCount==0 || strcmp(inventory->itemsInInventory[0]->name, "Health Potion") == 0) {
                printf("You cant attack. You have no weapon to attack!\n");
                break;
            }
            if(rooms[playerCurrentRoomID-1].creature==NULL || rooms[playerCurrentRoomID-1].creature->health<=0) {
                printf("There is no creature here to attack!\n");
                break;
            }
            while (player->health>0 && inventory,rooms[playerCurrentRoomID-1].creature->health>0) {
                attack(player, inventory,rooms[playerCurrentRoomID-1].creature);
            }
        break;
        case 8:
            pickup(inventory,playerCurrentRoomID);
        break;
        case 9:
            printf("Which item you would like to drop? Enter name: (Magic Wand, Special Sword etc.)\n");
            if(inventory->itemCount==0) {
            printf("There are no items in your inventory.\n");
            break;
            }
            char inputDrop[30];
            scanf(" %[^\n]", inputDrop);
            dropItem(inventory,inputDrop);
        break;
        case 10:
            healPlayer(player,inventory);
        break;
        case 11:
            saveGame(player,inventory);
        break;
        case 12:
            loadGame(player,inventory);
        break;
        case 13:
            exit(0);
        default:
            printf("You entered invalid input.\n");
        break;
        }
        if(creatures[0].health<=0 && creatures[1].health<=0)
            break;

    }

    printf("Congrulations you won the game. There are no creatures left!!!\n");

    free(player);
    free(inventory);

}

