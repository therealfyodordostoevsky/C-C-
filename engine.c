#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 30
#define HEIGHT 20
#define POWER_UP_CHANCE 0.1
#define TIMER_DURATION 1000
#define LEVEL_UP_SCORE 10
#define ENEMY_CHANCE 0.2
#define AMMO_CAPACITY 10
#define INVENTORY_SIZE 5

// Enum of weapons
enum Weapon {
    AK47,
    P90,
    DesertEagle,
    C4Bomb,
    HandGrenade
};

// Enum of characters
enum Character {
    None,
    Dracula,
    Zombie,
    Princess,
    Emperor
};

// Enum of transportation vehicles
enum Vehicle {
    NoneVehicle,
    Horse,
    Camel,
    Car,
    Locomotive,
    Plane
};

// Enum of missions
enum Mission {
    NoMission,
    SavePrincess,
    FightDracula,
    FlyPlane,
    DriveCar,
    RideHorse
};

// Enum of materials
enum Material {
    NoneMaterial,
    Dirt,
    Iron,
    Uranium
};

// Enum of terrains
enum Terrain {
    Grass,
    Mountain,
    Cave
};

// Struct for characters
struct CharacterInfo {
    enum Character character;
    const char* dialogue;
};

// Struct for vehicles
struct VehicleInfo {
    enum Vehicle vehicle;
    const char* description;
};

// Struct for missions
struct MissionInfo {
    enum Mission mission;
    const char* description;
};

// Struct for materials
struct MaterialInfo {
    enum Material material;
    const char* name;
};

// Struct for terrains
struct TerrainInfo {
    enum Terrain terrain;
    const char* name;
};

// Function prototypes
void initializeGame();
void updateGame();
void drawGame();
void processInput();
void saveLocation();
void printCoordinates();

// Game variables
int playerX, playerY;
int enemyX, enemyY;
int powerUpX, powerUpY;
int score;
int timer;
int level;
int ammo;
int enemyCount;
int firstPersonView;
enum Weapon currentWeapon;
struct CharacterInfo currentCharacter;
struct VehicleInfo currentVehicle;
struct MissionInfo currentMission;
struct MaterialInfo inventory[INVENTORY_SIZE];
struct TerrainInfo gameMap[WIDTH][HEIGHT];

int main() {
    initializeGame();

    while (1) {
        updateGame();
        drawGame();
        processInput();
        Sleep(100);
    }

    return 0;
}

void initializeGame() {
    // Initialize player position
    playerX = WIDTH / 2;
    playerY = HEIGHT / 2;

    // Initialize enemy position
    enemyX = rand() % WIDTH;
    enemyY = rand() % HEIGHT;

    // Initialize power-up position
    powerUpX = rand() % WIDTH;
    powerUpY = rand() % HEIGHT;

    // Initialize game variables
    score = 0;
    timer = TIMER_DURATION;
    level = 1;
    ammo = AMMO_CAPACITY;
    enemyCount = 0;
    firstPersonView = 0;  // 0 for third-person view, 1 for first-person view
    currentWeapon = AK47;  // Default weapon
    currentCharacter.character = None;  // No character initially
    currentVehicle.vehicle = NoneVehicle;  // No vehicle initially
    currentMission.mission = NoMission;  // No mission initially

    // Initialize inventory
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        inventory[i].material = NoneMaterial;
        inventory[i].name = "None";
    }

    // Initialize game map
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // Default terrain is grass
            gameMap[x][y].terrain = Grass;
            gameMap[x][y].name = "Grass";
        }
    }

    // Set console window title
    SetConsoleTitle("Shooting Game: Collect Power-Ups and Shoot Enemies!");
}

void updateGame() {
    // Update enemy position randomly
    if ((double)rand() / RAND_MAX < ENEMY_CHANCE) {
        enemyX = rand() % WIDTH;
        enemyY = rand() % HEIGHT;
        enemyCount++;
    }

    // Update power-up position
    if ((double)rand() / RAND_MAX < POWER_UP_CHANCE) {
        powerUpX = rand() % WIDTH;
        powerUpY = rand() % HEIGHT;

        // Switch to a random character when collecting a power-up
        currentCharacter.character = (enum Character)(rand() % 4 + 1);  // 1 to 4 are characters
        currentVehicle.vehicle = (enum Vehicle)(rand() % 5 + 1);  // 1 to 5 are vehicles
        currentMission.mission = (enum Mission)(rand() % 6 + 1);  // 1 to 6 are missions

        // Switch to a random material when collecting a power-up
        for (int i = 0; i < INVENTORY_SIZE; i++) {
            inventory[i].material = (enum Material)(rand() % 4 + 1);  // 1 to 4 are materials
            switch (inventory[i].material) {
                case Dirt:
                    inventory[i].name = "Dirt";
                    break;
                case Iron:
                    inventory[i].name = "Iron";
                    break;
                case Uranium:
                    inventory[i].name = "Uranium";
                    break;
                default:
                    inventory[i].name = "None";
                    break;
            }
        }
    }

    // Update timer
    timer -= 100;

    // Check if the timer has reached zero
    if (timer <= 0) {
        printf("\nTime's up! Your Score: %d\n", score);
        exit(0);
    }

    // Check for level up
    if (score >= LEVEL_UP_SCORE * level) {
        level++;
        printf("\nLevel up! Current Level: %d\n", level);
    }

    // Check for mission completion
    switch (currentMission.mission) {
        case SavePrincess:
            // Check for princess character and complete mission
            if (currentCharacter.character == Princess) {
                printf("\nMission Complete! Saved the Princess! +5 score\n");
                score += 5;
                currentMission.mission = NoMission;  // Reset mission after completion
            }
            break;
        case FightDracula:
            // Check for Dracula character and complete mission
            if (currentCharacter.character == Dracula) {
                printf("\nMission Complete! Defeated Dracula! +10 score\n");
                score += 10;
                currentMission.mission = NoMission;  // Reset mission after completion
            }
            break;
        case FlyPlane:
            // Check for Plane vehicle and complete mission
            if (currentVehicle.vehicle == Plane) {
                printf("\nMission Complete! Flew a Plane! +8 score\n");
                score += 8;
                currentMission.mission = NoMission;  // Reset mission after completion
            }
            break;
        case DriveCar:
            // Check for Car vehicle and complete mission
            if (currentVehicle.vehicle == Car) {
                printf("\nMission Complete! Drove a Car! +6 score\n");
                score += 6;
                currentMission.mission = NoMission;  // Reset mission after completion
            }
            break;
        case RideHorse:
            // Check for Horse vehicle and complete mission
            if (currentVehicle.vehicle == Horse) {
                printf("\nMission Complete! Rode a Horse! +4 score\n");
                score += 4;
                currentMission.mission = NoMission;  // Reset mission after completion
            }
            break;
        default:
            break;
    }
}

void drawGame() {
    // Draw game elements
    system("cls");
    printf("Score: %d | Timer: %d ms | Level: %d | Ammo: %d | Enemies: %d | View: %s | Weapon: ",
           score, timer, level, ammo, enemyCount, (firstPersonView ? "First-Person" : "Third-Person"));

    switch (currentWeapon) {
        case AK47:
            printf("AK-47");
            break;
        case P90:
            printf("P90");
            break;
        case DesertEagle:
            printf("Desert Eagle");
            break;
        case C4Bomb:
            printf("C4 Bomb");
            break;
        case HandGrenade:
            printf("Hand Grenade");
            break;
    }

    printf(" | ");

    switch (currentCharacter.character) {
        case Dracula:
            printf("Dracula: %s", currentCharacter.dialogue);
            break;
        case Zombie:
            printf("Zombie: %s", currentCharacter.dialogue);
            break;
        case Princess:
            printf("Princess: %s", currentCharacter.dialogue);
            break;
        case Emperor:
            printf("Emperor: %s", currentCharacter.dialogue);
            break;
        default:
            printf("No Character");
            break;
    }

    printf(" | ");

    switch (currentVehicle.vehicle) {
        case Horse:
            printf("Horse");
            break;
        case Camel:
            printf("Camel");
            break;
        case Car:
            printf("Car");
            break;
        case Locomotive:
            printf("Locomotive");
            break;
        case Plane:
            printf("Plane");
            break;
        default:
            printf("No Vehicle");
            break;
    }

    printf(" | ");

    switch (currentMission.mission) {
        case SavePrincess:
            printf("Mission: Save the Princess");
            break;
        case FightDracula:
            printf("Mission: Fight Dracula");
            break;
        case FlyPlane:
            printf("Mission: Fly a Plane");
            break;
        case DriveCar:
            printf("Mission: Drive a Car");
            break;
        case RideHorse:
            printf("Mission: Ride a Horse");
            break;
        default:
            printf("No Mission");
            break;
    }

    printf(" | Inventory: ");
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        printf("%s ", inventory[i].name);
    }

    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (firstPersonView) {
                // First-person view
                if (x == playerX && y == playerY) {
                    printf("P");
                } else {
                    printf(getTerrainSymbol(gameMap[x][y].terrain));
                }
            } else {
                // Third-person view
                if (x == playerX && y == playerY) {
                    printf("P");
                } else if (x == enemyX && y == enemyY) {
                    printf("E");
                } else if (x == powerUpX && y == powerUpY) {
                    printf("U");
                } else {
                    printf(getTerrainSymbol(gameMap[x][y].terrain));
                }
            }
        }
        printf("\n");
    }

    printCoordinates();
}

char getTerrainSymbol(enum Terrain terrain) {
    switch (terrain) {
        case Grass:
            return '.';
        case Mountain:
            return '^';
        case Cave:
            return 'C';
        default:
            return '?';
    }
}

void processInput() {
    // Process user input
    char key = _getch();

    // Handle input
    switch (key) {
        case 'w':
            playerY--;
            break;
        case 's':
            playerY++;
            break;
        case 'a':
            playerX--;
            break;
        case 'd':
            playerX++;
            break;
        case 'q':
            printf("\nGame Quit! Your Score: %d\n", score);
            exit(0);
            break;
        case ' ':
            if (ammo > 0) {
                // Check for shooting
                if (playerX == enemyX && playerY == enemyY) {
                    printf("Enemy shot! +1 score\n");
                    score++;
                    enemyX = -1;  // Move the enemy out of bounds
                    enemyY = -1;
                    enemyCount--;
                }
                ammo--;
            } else {
                printf("Out of ammo!\n");
            }
            break;
        case 'c':
            // Toggle between first-person and third-person views
            firstPersonView = !firstPersonView;
            break;
        case 's':
            // Save location
            saveLocation();
            break;
        default:
            break;
    }

    // Ensure player stays within bounds
    playerX = (playerX + WIDTH) % WIDTH;
    playerY = (playerY + HEIGHT) % HEIGHT;
}

void saveLocation() {
    // Save the current player coordinates
    printf("\nLocation saved: (%d, %d)\n", playerX, playerY);

    // Add the current location to a list of saved locations
    // You can use an array or a dynamic data structure to store multiple saved locations
    // For simplicity, let's use an array with a maximum of 10 saved locations
    const int maxSavedLocations = 10;
    static int savedLocationsX[maxSavedLocations];
    static int savedLocationsY[maxSavedLocations];
    static int numSavedLocations = 0;

    if (numSavedLocations < maxSavedLocations) {
        savedLocationsX[numSavedLocations] = playerX;
        savedLocationsY[numSavedLocations] = playerY;
        numSavedLocations++;
    } else {
        printf("Cannot save more locations. Maximum limit reached.\n");
    }
}

void printCoordinates() {
    // Print the saved coordinates menu
    printf("Press 'v' to view saved coordinates.\n");

    // Process user input for viewing saved coordinates
    char key = _getch();

    if (key == 'v') {
        printf("\nSaved Coordinates:\n");

        // Print all saved coordinates
        for (int i = 0; i < numSavedLocations; i++) {
            printf("(%d, %d)\n", savedLocationsX[i], savedLocationsY[i]);
        }

        // Wait for a key press before returning to the game
        printf("Press any key to continue.\n");
        _getch();
    }
}