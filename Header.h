#ifndef Header_h
#define Header_h

#define WIDTH 8
#define HEIGHT 4
#define WALL '|'
#define EMPTY ' '
#define DOOR '_'
#define PLAYER 'P'
#define MAX_INVENTORY 2

typedef struct {
    char *name;
    int damage;
    char *type;
    int weight;
    int currentRoomID;
} Item;

typedef struct {
    char *name;
    int maxHealth;
    int health;
    int strength;
} Player;

typedef struct {
    char *name;
    int maxHealth;
    int health;
    int damage;
    int currentRoomID;
} Creature;

typedef struct Room {
    char *name;
    int id;
    char *description;
    Item *item;
    struct Room *up;
    struct Room *down;
    struct Room *left;
    struct Room *right;
    Creature *creature;
} Room;

typedef struct {
    Item *itemsInInventory[MAX_INVENTORY];
    int itemCount;
} Inventory;

extern char board[HEIGHT * 2][WIDTH * 2];
extern int playerCurrentRoomID;
extern Item items[3];
extern Creature creatures[2];
extern Room rooms[4];

void createMap();
void movePlayer(char direction, int currentRoomID);
void printMap();
void look(int roomID);
void loadItems();
void loadCreatures();
void loadRooms();
void viewInventory(const Inventory *inventory);
void pickup(Inventory *inventory, int roomID);
void dropItem(Inventory *inventory, char itemName[30]);
void attack(Player *player, const Inventory *inventory, Creature *creature);
void healPlayer(Player *player, Inventory *inventory);
void saveGame(Player *player, Inventory *inventory);
void loadGame(Player *player, Inventory *inventory);
void listSavedGame();

#endif
