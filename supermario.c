#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define ROWS 10
#define COLS 20

int playerRow = 9;
int playerCol = 0;

int hasKey = 0;
int hasMushroom = 0;
int hasLuigi = 0;
int missionCompleted = 0;
int gameOver = 0;

// Added variables for weapons
int selectedWeapon = 0;  // 0: No weapon, 1: Fireballs, 2: AK-47, 3: Rockets, 4: Revolver

char level[ROWS][COLS] = {
    "###################",
    "#        K        #",
    "#        D        #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "#                 #",
    "###################"
};

void playSound(const char* soundFilePath) {
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    if (SDL_LoadWAV(soundFilePath, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        fprintf(stderr, "Could not load sound file: %s\n", SDL_GetError());
        return;
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        fprintf(stderr, "Could not open audio device: %s\n", SDL_GetError());
        SDL_FreeWAV(wavBuffer);
        return;
    }

    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    // Wait for the sound to finish playing
    SDL_Delay(1000);  // Adjust as needed

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}

void printLevel() {
    system("cls");  // Clear the console

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", level[i][j]);
        }
        printf("\n");
    }

    // Display the selected weapon in the inventory
    printf("\nInventory: ");
    switch (selectedWeapon) {
        case 0:
            printf("No weapon");
            break;
        case 1:
            printf("Fireballs");
            break;
        case 2:
            printf("AK-47");
            break;
        case 3:
            printf("Rockets");
            break;
        case 4:
            printf("Revolver");
            break;
    }
    printf("\n");
}

void movePlayer(char direction) {
    int newPlayerRow = playerRow;
    int newPlayerCol = playerCol;

    switch (direction) {
        case 'w':
            newPlayerRow--;
            break;
        case 's':
            newPlayerRow++;
            break;
        case 'a':
            newPlayerCol--;
            break;
        case 'd':
            newPlayerCol++;
            break;
    }

    // Check boundaries
    if (newPlayerRow >= 0 && newPlayerRow < ROWS && newPlayerCol >= 0 && newPlayerCol < COLS) {
        // Check if the new position is a wall
        if (level[newPlayerRow][newPlayerCol] != '#') {
            // Check if the new position has a key
            if (level[newPlayerRow][newPlayerCol] == 'K') {
                hasKey = 1;
                printf("You've got the key!\n");
                level[newPlayerRow][newPlayerCol] = ' ';  // Remove the key from the level
            }

            // Check if the new position has a mushroom
            if (level[newPlayerRow][newPlayerCol] == 'M') {
                hasMushroom = 1;
                printf("You've got a mushroom! Power up!\n");
                level[newPlayerRow][newPlayerCol] = ' ';  // Remove the mushroom from the level
            }

            // Check if the new position has a door
            if (level[newPlayerRow][newPlayerCol] == 'D') {
                if (hasKey) {
                    printf("Congratulations! You've opened the door!\n");
                    level[newPlayerRow][newPlayerCol] = ' ';  // Remove the door from the level
                    missionCompleted = 1;
                } else {
                    printf("You need a key to open this door!\n");
                }
            }

            // Check if the new position has Luigi
            if (level[newPlayerRow][newPlayerCol] == 'L') {
                if (!hasLuigi) {
                    printf("Luigi: Hey, who are you?\n");
                    printf("Mario: It's-a me, Mario!\n");
                    printf("Luigi: I challenge you to a friendly duel!\n");

                    // Fight event (simple simulation)
                    printf("Mario vs. Luigi - Fight!\n");

                    int marioHealth = 100;
                    int luigiHealth = 100;

                    while (marioHealth > 0 && luigiHealth > 0) {
                        printf("Mario's health: %d | Luigi's health: %d\n", marioHealth, luigiHealth);

                        // Simulate a turn-based fight
                        marioHealth -= rand() % 20;  // Mario's attack
                        luigiHealth -= rand() % 20;  // Luigi's attack

                        // Delay for a moment to show the fight progress
                        for (int i = 0; i < 100000000; i++);

                        system("cls");  // Clear the console for the next iteration
                    }

                    if (marioHealth <= 0) {
                        printf("Luigi: I won! But let's be friends, okay?\n");
                        hasLuigi = 1;
                    } else {
                        printf("Mario: It's-a me, the winner! Let's be friends, Luigi!\n");
                        hasLuigi = 1;
                    }
                } else {
                    printf("Luigi: We're already friends, Mario!\n");
                }
            }

            // Update the player position
            level[playerRow][playerCol] = ' ';
            playerRow = newPlayerRow;
            playerCol = newPlayerCol;
            level[playerRow][playerCol] = 'P';
        } else {
            printf("Can't move there! It's a wall!\n");
        }
    } else {
        printf("Can't move there! Out of bounds!\n");
    }
}

void spawnMushroom() {
    int mushroomRow, mushroomCol;

    do {
        mushroomRow = rand() % ROWS;
        mushroomCol = rand() % COLS;
    } while (level[mushroomRow][mushroomCol] != ' ');

    level[mushroomRow][mushroomCol] = 'M';
}

void spawnEnemy() {
    int enemyRow, enemyCol;

    do {
        enemyRow = rand() % ROWS;
        enemyCol = rand() % COLS;
    } while (level[enemyRow][enemyCol] != ' ');

    level[enemyRow][enemyCol] = 'E';
}

void spawnLuigi() {
    int luigiRow, luigiCol;

    do {
        luigiRow = rand() % ROWS;
        luigiCol = rand() % COLS;
    } while (level[luigiRow][luigiCol] != ' ');

    level[luigiRow][luigiCol] = 'L';
}

void spawnAlligator() {
    int alligatorRow, alligatorCol;

    do {
        alligatorRow = rand() % ROWS;
        alligatorCol = rand() % COLS;
    } while (level[alligatorRow][alligatorCol] != ' ');

    level[alligatorRow][alligatorCol] = 'A';
}

void spawnSaturnAlien() {
    int alienRow, alienCol;

    do {
        alienRow = rand() % ROWS;
        alienCol = rand() % COLS;
    } while (level[alienRow][alienCol] != ' ');

    level[alienRow][alienCol] = 'S';
}

void spawnElf() {
    int elfRow, elfCol;

    do {
        elfRow = rand() % ROWS;
        elfCol = rand() % COLS;
    } while (level[elfRow][elfCol] != ' ');

    level[elfRow][elfCol] = 'E';
}

void spawnLuigiEnemy() {
    int luigiRow, luigiCol;

    do {
        luigiRow = rand() % ROWS;
        luigiCol = rand() % COLS;
    } while (level[luigiRow][luigiCol] != ' ');

    level[luigiRow][luigiCol] = 'X';  // Luigi turns into an enemy
}

void spawnGrandSpider() {
    int spiderRow, spiderCol;

    do {
        spiderRow = rand() % ROWS;
        spiderCol = rand() % COLS;
    } while (level[spiderRow][spiderCol] != ' ');

    level[spiderRow][spiderCol] = 'G';  // Grand Spider of Sutawashi
}

void spawnBeesAndWasps() {
    int beesRow, beesCol;

    do {
        beesRow = rand() % ROWS;
        beesCol = rand() % COLS;
    } while (level[beesRow][beesCol] != ' ');

    level[beesRow][beesCol] = 'B';  // Bees

    int waspsRow, waspsCol;

    do {
        waspsRow = rand() % ROWS;
        waspsCol = rand() % COLS;
    } while (level[waspsRow][waspsCol] != ' ');

    level[waspsRow][waspsCol] = 'W';  // Wasps
}

// Function to handle the inventory
void handleInventory() {
    char inventoryInput;
    
    do {
        printf("\nInventory Options:\n");
        printf("1. Fireballs\n");
        printf("2. AK-47\n");
        printf("3. Rockets\n");
        printf("4. Revolver\n");
        printf("Press the corresponding number to select a weapon (0 to exit): ");

        inventoryInput = getch();

        switch (inventoryInput) {
            case '1':
                selectedWeapon = 1;
                printf("You've selected Fireballs!\n");
                break;
            case '2':
                selectedWeapon = 2;
                printf("You've selected AK-47!\n");
                break;
            case '3':
                selectedWeapon = 3;
                printf("You've selected Rockets!\n");
                break;
            case '4':
                selectedWeapon = 4;
                printf("You've selected Revolver!\n");
                break;
            case '0':
                printf("Exiting inventory...\n");
                break;
            default:
                printf("Invalid option! Try again.\n");
        }

        printLevel();  // Display the level after selecting a weapon

    } while (inventoryInput != '0');
}

int main() {
    // Initial mission setup
    printf("Mission 1: Mario encountering Luigi\n");

    level[playerRow][playerCol] = 'P';  // Place the player on the starting position
    spawnLuigi();  // Luigi is part of the game

    while (!missionCompleted && !gameOver) {
        printLevel();

        printf("Enter a move (w/a/s/d, i for inventory): ");
        char move = getch();  // Get a character without waiting for Enter

        if (move == 'i' || move == 'I') {
            handleInventory();
        } else {
            movePlayer(move);
        }

        // Simulate enemy movement (simple random movement)
        int enemyMove = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

        switch (enemyMove) {
            case 0:
                movePlayer('w');
                break;
            case 1:
                movePlayer('s');
                break;
            case 2:
                movePlayer('a');
                break;
            case 3:
                movePlayer('d');
                break;
        }

        // Spawn Luigi periodically
        if (!hasLuigi && rand() % 20 == 0) {
            spawnLuigi();
        }
    }

    // Mission 5: Grand Spider of Sutawashi attacking the two while reunited
    printf("Mission 5: Grand Spider of Sutawashi attacking the two while reunited\n");

    // Clear the level for the new mission
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            level[i][j] = ' ';
        }
    }

    playerRow = 9;
    playerCol = 0;
    missionCompleted = 0;

    level[playerRow][playerCol] = 'P';  // Place the player on the starting position
    spawnLuigiEnemy();  // Luigi as an enemy is part of the game

    while (!missionCompleted) {
        printLevel();

        printf("Enter a move (w/a/s/d): ");
        char move = getch();  // Get a character without waiting for Enter
        movePlayer(move);

        // Simulate enemy movement (simple random movement)
        int enemyMove = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

        switch (enemyMove) {
            case 0:
                movePlayer('w');
                break;
            case 1:
                movePlayer('s');
                break;
            case 2:
                movePlayer('a');
                break;
            case 3:
                movePlayer('d');
                break;
        }

        // Spawn Grand Spider periodically
        if (rand() % 15 == 0) {
            spawnGrandSpider();
        }
    }

    // Mission 6: Bees of Qiakaria uniting with Wasps, attacking the pair
    printf("Mission 6: Bees of Qiakaria uniting with Wasps, attacking the pair\n");

    // Clear the level for the new mission
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            level[i][j] = ' ';
        }
    }

    playerRow = 9;
    playerCol = 0;
    missionCompleted = 0;

    level[playerRow][playerCol] = 'P';  // Place the player on the starting position
    spawnGrandSpider();  // Grand Spider is part of the game

    while (!missionCompleted) {
        printLevel();

        printf("Enter a move (w/a/s/d): ");
        char move = getch();  // Get a character without waiting for Enter
        movePlayer(move);

        // Simulate enemy movement (simple random movement)
        int enemyMove = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

        switch (enemyMove) {
            case 0:
                movePlayer('w');
                break;
            case 1:
                movePlayer('s');
                break;
            case 2:
                movePlayer('a');
                break;
            case 3:
                movePlayer('d');
                break;
        }

        // Spawn Bees and Wasps periodically
        if (rand() % 20 == 0) {
            spawnBeesAndWasps();
        }
    }

    // Mission 7: Meeting of Luigi and Mario with Mike, a character just like them but with a blue color.
printf("Mission 7: Meeting of Luigi and Mario with Mike, a character just like them but with a blue color.\n");
playSound("path/to/meeting_sound.wav");
// Clear the level for the new mission
for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        level[i][j] = ' ';
    }
}

playerRow = 9;
playerCol = 0;
missionCompleted = 0;

level[playerRow][playerCol] = 'P';  // Place the player on the starting position
spawnLuigi();  // Luigi is part of the game
spawnMike();  // Mike is part of the game

while (!missionCompleted) {
    printLevel();

    printf("Enter a move (w/a/s/d, i for inventory): ");
    char move = getch();  // Get a character without waiting for Enter

    if (move == 'i' || move == 'I') {
        handleInventory();
    } else {
        movePlayer(move);
    }

    // Simulate enemy movement (simple random movement)
    int enemyMove = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

    switch (enemyMove) {
        case 0:
            movePlayer('w');
            break;
        case 1:
            movePlayer('s');
            break;
        case 2:
            movePlayer('a');
            break;
        case 3:
            movePlayer('d');
            break;
    }

    // Spawn Luigi and Mike periodically
    if (!hasLuigi && rand() % 20 == 0) {
        spawnLuigi();
    }
    if (rand() % 30 == 0) {
        spawnMike();
    }
}

// Mission completed message
printf("Luigi: Mario, meet our new friend Mike! He's just like us but with a blue color.\n");
printf("Mike: Nice to meet you, Mario!\n");
printf("Mario: It's-a great to have you on our team, Mike!\n");


// Mission 8: Fighting with ants of Wermaanshung (Enemies: Ants)
printf("Mission 8: Fighting with ants of Wermaanshung (Enemies: Ants)\n");

// Clear the level for the new mission
for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        level[i][j] = ' ';
    }
}

playerRow = 9;
playerCol = 0;
missionCompleted = 0;

level[playerRow][playerCol] = 'P';  // Place the player on the starting position

while (!missionCompleted) {
    printLevel();

    printf("Enter a move (w/a/s/d, i for inventory): ");
    char move = getch();  // Get a character without waiting for Enter

    if (move == 'i' || move == 'I') {
        handleInventory();
    } else {
        movePlayer(move);
    }

    // Simulate enemy movement (simple random movement)
    int enemyMove = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

    switch (enemyMove) {
        case 0:
            movePlayer('w');
            break;
        case 1:
            movePlayer('s');
            break;
        case 2:
            movePlayer('a');
            break;
        case 3:
            movePlayer('d');
            break;
    }

    // Spawn ants periodically
    if (rand() % 15 == 0) {
        spawnAnt();
    }
}

// Mission completed message
printf("Congratulations! You've defeated the ants of Wermaanshung!\n");


// Mission 9: Encountering the Queen of Wermaanshung (Enemy: The gigantic ant)
printf("Mission 9: Encountering the Queen of Wermaanshung (Enemy: The gigantic ant)\n");

// Clear the level for the new mission
for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        level[i][j] = ' ';
    }
}

playerRow = 9;
playerCol = 0;
missionCompleted = 0;

level[playerRow][playerCol] = 'P';  // Place the player on the starting position

while (!missionCompleted) {
    printLevel();

    printf("Enter a move (w/a/s/d, i for inventory): ");
    char move = getch();  // Get a character without waiting for Enter

    if (move == 'i' || move == 'I') {
        handleInventory();
    } else {
        movePlayer(move);
    }

    // Simulate enemy movement (simple random movement)
    int enemyMove = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

    switch (enemyMove) {
        case 0:
            movePlayer('w');
            break;
        case 1:
            movePlayer('s');
            break;
        case 2:
            movePlayer('a');
            break;
        case 3:
            movePlayer('d');
            break;
    }

    // Spawn the Queen of Wermaanshung periodically
    if (rand() % 20 == 0) {
        spawnGiganticAnt();
    }
}

// Mission completed message
printf("Congratulations! You've encountered and survived the Queen of Wermaanshung!\n");


    // End of the game
    printf("Congratulations! You've completed all missions!\n");
    playSound("path/to/victory_sound.wav");

    return 0;
}

