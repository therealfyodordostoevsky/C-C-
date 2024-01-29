#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 10
#define POWER_UP_CHANCE 0.1
#define TIMER_DURATION 1000
#define LEVEL_UP_SCORE 10
#define ENEMY_CHANCE 0.2
#define AMMO_CAPACITY 10

// Function prototypes
void initializeGame();
void updateGame();
void drawGame();
void processInput();

// Game variables
int playerX, playerY;
int enemyX, enemyY;
int powerUpX, powerUpY;
int score;
int timer;
int level;
int ammo;
int enemyCount;
int viewMode;  // 0: First-person, 1: Third-person

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
    viewMode = 0;  // First-person view

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
    }

    // Check for collision with player
    if (playerX == enemyX && playerY == enemyY) {
        printf("\nGame Over! Your Score: %d\n", score);
        exit(0);
    }

    // Check for collision with power-up
    if (playerX == powerUpX && playerY == powerUpY) {
        score += 2;
        timer = TIMER_DURATION;
        ammo = AMMO_CAPACITY;  // Refill ammo when collecting a power-up
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
}

void drawGame() {
    // Draw game elements
    system("cls");
    printf("Score: %d | Timer: %d ms | Level: %d | Ammo: %d | Enemies: %d\n", score, timer, level, ammo, enemyCount);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (viewMode == 0 && x == playerX && y == playerY) {
                printf("P");  // Player (first-person view)
            } else if (viewMode == 1 && (x == playerX || y == playerY)) {
                printf("P");  // Player (third-person view)
            } else if (x == enemyX && y == enemyY) {
                printf("E");  // Enemy
            } else if (x == powerUpX && y == powerUpY) {
                printf("U");  // Power-up
            } else {
                printf(".");
            }
        }
        printf("\n");
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
        case 'c':
            // Toggle view mode between first-person and third-person
            viewMode = (viewMode == 0) ? 1 : 0;
            break;
        case 'space':
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
        default:
            break;
    }

    // Ensure player stays within bounds
    playerX = (playerX + WIDTH) % WIDTH;
    playerY = (playerY + HEIGHT) % HEIGHT;
}