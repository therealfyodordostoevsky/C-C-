#include <iostream>
#include <vector>
#include <SDL.h>
#include <GL/gl.h>

using namespace std;

SDL_Window* window;
SDL_GLContext context;

// Character structure representing a robot
struct Robot {
    char name;     // Robot name (A1 to Z9)
    int lives;     // Number of lives in combat
    int attack;    // Attack power
    int defense;   // Defense power
};

// Planet structure representing a planet in the game
struct Planet {
    string name;   // Planet name
    int threatLevel; // Threat level on the planet
};

// Item structure representing an item in the inventory
struct Item {
    string name;   // Item name
    string type;   // Item type (Weapon, Armor, etc.)
    int attackBonus;  // Attack bonus provided by the item
    int defenseBonus; // Defense bonus provided by the item
};

Robot player;  // Player's robot
Planet currentPlanet;  // Current planet
vector<Item> inventory;  // Player's inventory

// Function to initialize SDL and OpenGL
void init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    window = SDL_CreateWindow("Sci-Fi Adventure Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to draw characters and planets
void drawCharacters() {
    // Add OpenGL drawing code for characters
    glBegin(GL_QUADS);
    // Draw characters
    glEnd();

    // Add OpenGL drawing code for planets
    glBegin(GL_QUADS);
    // Draw planets
    glEnd();
}

// Function to handle events
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
    }
}

// Function to display the player's inventory
void displayInventory() {
    cout << "Inventory:" << endl;
    for (const auto& item : inventory) {
        cout << " - " << item.name << " (Type: " << item.type << ", Attack Bonus: " << item.attackBonus << ", Defense Bonus: " << item.defenseBonus << ")" << endl;
    }
    cout << endl;
}

// Function to simulate combat with an enemy
void combatWithEnemy() {
    cout << "Combat initiated with enemy on planet " << currentPlanet.name << "!" << endl;

    // Apply bonuses from inventory items to player's stats
    for (const auto& item : inventory) {
        player.attack += item.attackBonus;
        player.defense += item.defenseBonus;
    }

    // Simulate combat by deducting lives
    player.lives -= (currentPlanet.threatLevel - player.defense);

    if (player.lives <= 0) {
        cout << "Your robot has been defeated. Game Over!" << endl;
        SDL_Quit();
        exit(0);
    } else {
        cout << "Enemy defeated! Your robot has " << player.lives << " lives remaining." << endl;
    }

    // Reset player's stats after combat
    player.attack = 0;
    player.defense = 0;
}

int main() {
    // Initialize game elements
    init();

    // Set up player's robot
    player.name = 'A';
    player.lives = 2;
    player.attack = 0;
    player.defense = 0;

    // Set up initial planet
    currentPlanet.name = "Earth";
    currentPlanet.threatLevel = 1;

    // Add some items to the player's inventory
    inventory.push_back({"Laser Sword", "Weapon", 5, 2});
    inventory.push_back({"Energy Shield", "Armor", 0, 8});
    inventory.push_back({"AK-47", "Weapon", 10, 0});
    inventory.push_back({"M-16 Rifle", "Weapon", 8, 0});
    inventory.push_back({"RPG", "Weapon", 15, 0});
    inventory.push_back({"M1911 Pistol", "Weapon", 6, 0});
    inventory.push_back({"Glock 17", "Weapon", 5, 0});

    while (true) {
        handleEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        // Add game logic
        drawCharacters();

        // Display player's inventory
        displayInventory();

        // Check for combat on the current planet
        if (currentPlanet.threatLevel > 0) {
            combatWithEnemy();
            // Reset threat level after combat
            currentPlanet.threatLevel = 0;
        }

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
