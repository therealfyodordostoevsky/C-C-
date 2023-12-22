#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define WIDTH 10
#define HEIGHT 20

int board[HEIGHT][WIDTH] = {0};
int score = 0;
int level = 1;

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point block[4];
} Tetromino;

Tetromino tetrominos[7] = {
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}},   // I
    {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}},   // O
    {{{1, 0}, {0, 1}, {1, 1}, {2, 1}}},   // L
    {{{0, 0}, {1, 0}, {2, 0}, {2, 1}}},   // J
    {{{1, 0}, {2, 0}, {0, 1}, {1, 1}}},   // S
    {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}},   // Z
    {{{0, 1}, {1, 1}, {2, 1}, {1, 0}}}    // T
};

Tetromino nextTetromino;
Tetromino heldTetromino;
int hasHeldTetromino = 0;

void drawBoard();
void drawTetromino(Tetromino *t, int value);
void drawGhostPiece(Tetromino *t, int value);
int checkCollision(Tetromino *t, int offsetX, int offsetY);
void mergeTetromino(Tetromino *t);
void rotateTetromino(Tetromino *t);
int getRandomTetromino();
void resetGame();
int moveTetromino(Tetromino *t, int offsetX, int offsetY);
void updateScoreAndLevel(int linesCleared);
void generateNextTetromino();
void holdTetromino();
void setColor(int color);
void gameOverScreen();
void pauseScreen();

int main() {
    srand(time(NULL));
    resetGame();

    int key;
    Tetromino currentTetromino;
    int currentX, currentY;

    int gameOver = 0;

    while (!gameOver) {
        currentTetromino = nextTetromino;
        currentX = WIDTH / 2 - 1;
        currentY = 0;
        hasHeldTetromino = 0;

        generateNextTetromino();

        if (checkCollision(&currentTetromino, currentX, currentY)) {
            gameOver = 1;
            break;
        }

        while (1) {
            drawBoard();
            drawTetromino(&currentTetromino, 1);
            drawGhostPiece(&currentTetromino, 8);

            if (_kbhit()) {
                key = _getch();
                switch (key) {
                    case 'a':
                        moveTetromino(&currentTetromino, -1, 0);
                        break;
                    case 'd':
                        moveTetromino(&currentTetromino, 1, 0);
                        break;
                    case 's':
                        if (!moveTetromino(&currentTetromino, 0, 1)) {
                            mergeTetromino(&currentTetromino);
                            break;
                        }
                        break;
                    case 'w':
                        rotateTetromino(&currentTetromino);
                        break;
                    case 'h':
                        holdTetromino();
                        break;
                    case 'q':
                        gameOver = 1;
                        break;
                    case 224:  // Arrow key
                        key = _getch();
                        switch (key) {
                            case 75:  // Left arrow
                                moveTetromino(&currentTetromino, -1, 0);
                                break;
                            case 77:  // Right arrow
                                moveTetromino(&currentTetromino, 1, 0);
                                break;
                            case 80:  // Down arrow
                                if (!moveTetromino(&currentTetromino, 0, 1)) {
                                    mergeTetromino(&currentTetromino);
                                    break;
                                }
                                break;
                        }
                        break;
                    case 32:  // Space key (pause)
                        pauseScreen();
                        break;
                }
            }

            if (!moveTetromino(&currentTetromino, 0, 1)) {
                mergeTetromino(&currentTetromino);
                break;
            }

            Sleep(100);
        }
    }

    gameOverScreen();
    return 0;
}

void drawBoard() {
    system("cls");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j]) {
                setColor(board[i][j]);
                printf("*");
                setColor(7);  // Reset color to default
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Score: %d\tLevel: %d\n", score, level);
    printf("Next Tetromino:\n");
    drawTetromino(&nextTetromino, 1);
    printf("\nHeld Tetromino:\n");
    drawTetromino(&heldTetromino, 1);
}

void drawTetromino(Tetromino *t, int value) {
    int color = 7;  // Default color (white)

    switch (getRandomTetromino()) {
        case 0:
            color = 9;  // Blue
            break;
        case 1:
            color = 14;  // Yellow
            break;
        // ... (assign colors to other Tetrominos)
    }

    setColor(color);

    for (int i = 0; i < 4; i++) {
        int x = t->block[i].x;
        int y = t->block[i].y;

        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            printf("*");
        }
    }

    setColor(7);  // Reset color to default
}

void drawGhostPiece(Tetromino *t, int value) {
    int originalY = t->block[0].y;
    while (!checkCollision(t, 0, 1)) {
        moveTetromino(t, 0, 1);
    }
    t->block[0].y = originalY;

    drawTetromino(t, value);
}

int checkCollision(Tetromino *t, int offsetX, int offsetY) {
    for (int i = 0; i < 4; i++) {
        int x = t->block[i].x + offsetX;
        int y = t->block[i].y + offsetY;

        if (y >= HEIGHT || x < 0 || x >= WIDTH || (y >= 0 && board[y][x] != 0)) {
            return 1;  // Collision detected
        }
    }

    return 0;
}

void mergeTetromino(Tetromino *t) {
    for (int i = 0; i < 4; i++) {
        int x = t->block[i].x;
        int y = t->block[i].y;

        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            board[y][x] = getRandomTetromino() + 1;  // Set color as value
        }
    }

    int linesCleared = 0;
    for (int i = HEIGHT - 1; i >= 0; i--) {
        int lineFull = 1;
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == 0) {
                lineFull = 0;
                break;
            }
        }

        if (lineFull) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            linesCleared++;
            i++;  // Check the same line again
        }
    }

    updateScoreAndLevel(linesCleared);
}

void rotateTetromino(Tetromino *t) {
    Tetromino rotated = *t;
    Point center = t->block[1];

    for (int i = 0; i < 4; i++) {
        int x = t->block[i].x - center.x;
        int y = t->block[i].y - center.y;

        rotated.block[i].x = center.x - y;
        rotated.block[i].y = center.y + x;
    }

    if (!checkCollision(&rotated, 0, 0)) {
        *t = rotated;
    }
}

int getRandomTetromino() {
    return rand() % 7;
}

void resetGame() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = 0;
        }
    }

    score = 0;
    level = 1;
}

int moveTetromino(Tetromino *t, int offsetX, int offsetY) {
    if (!checkCollision(t, offsetX, offsetY)) {
        t->block[0].x += offsetX;
        t->block[1].x += offsetX;
        t->block[2].x += offsetX;
        t->block[3].x += offsetX;

        t->block[0].y += offsetY;
        t->block[1].y += offsetY;
        t->block[2].y += offsetY;
        t->block[3].y += offsetY;

        return 1;  // Move successful
    }

    return 0;  // Move failed (collision)
}

void updateScoreAndLevel(int linesCleared) {
    switch (linesCleared) {
        case 1:
            score += 40 * level;
            break;
        case 2:
            score += 100 * level;
            break;
        case 3:
            score += 300 * level;
            break;
        case 4:
            score += 1200 * level;
            break;
    }

    level = score / 1000 + 1;
}

void generateNextTetromino() {
    nextTetromino = tetrominos[getRandomTetromino()];
}

void holdTetromino() {
    if (!hasHeldTetromino) {
        if (heldTetromino.block[0].x == -1) {
            heldTetromino = currentTetromino;
            currentTetromino = tetrominos[getRandomTetromino()];
        } else {
            Tetromino temp = currentTetromino;
            currentTetromino = heldTetromino;
            heldTetromino = temp;
        }
        hasHeldTetromino = 1;
    }
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void gameOverScreen() {
    system("cls");
    printf("Game Over!\n");
    printf("Final Score: %d\n", score);
    printf("Press 'R' to restart or 'Q' to quit.\n");

    int key;
    do {
        key = _getch();
    } while (key != 'r' && key != 'q');

    if (key == 'r') {
        resetGame();
        main();  // Restart the game
    } else {
        exit(0);  // Quit the game
    }
}

void pauseScreen() {
    printf("Paused. Press any key to resume.\n");
    _getch();  // Wait for a key press to resume
}
