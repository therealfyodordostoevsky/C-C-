#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

struct Point {
    int x, y;
};

struct Tetromino {
    Point block[4];
};

class Tetris {
private:
    int board[HEIGHT][WIDTH] = {0};
    int score = 0;
    int level = 1;
    Tetromino tetrominos[7] = {
        {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}},   // I
        {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}},   // O
        {{{1, 0}, {0, 1}, {1, 1}, {2, 1}}},   // L
        {{{0, 0}, {1, 0}, {2, 0}, {2, 1}}},   // J
        {{{1, 0}, {2, 0}, {0, 1}, {1, 1}}},   // S
        {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}},   // Z
        {{{0, 1}, {1, 1}, {2, 1}, {1, 0}}}    // T
    };
    Tetromino currentTetromino;
    Tetromino nextTetromino;
    Tetromino heldTetromino;
    bool hasHeldTetromino = false;

public:
    void drawBoard();
    void drawTetromino(const Tetromino& t, int value);
    bool checkCollision(const Tetromino& t, int offsetX, int offsetY);
    void mergeTetromino(const Tetromino& t);
    void rotateTetromino(Tetromino& t);
    int getRandomTetromino();
    void resetGame();
    bool moveTetromino(Tetromino& t, int offsetX, int offsetY);
    void updateScoreAndLevel(int linesCleared);
    void generateNextTetromino();
    void holdTetromino();
    void setColor(int color);
    void gameOverScreen();
    void drawGhostPiece(const Tetromino& t, int value);
    void pauseScreen();
    void runGame();
};

void Tetris::drawBoard() {
    system("cls");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j]) {
                setColor(board[i][j]);
                cout << "*";
                setColor(7);  // Reset color to default
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "Score: " << score << "\tLevel: " << level << endl;
    cout << "Next Tetromino:" << endl;
    drawTetromino(nextTetromino, 1);
    cout << "\nHeld Tetromino:" << endl;
    drawTetromino(heldTetromino, 1);
}

void Tetris::drawTetromino(const Tetromino& t, int value) {
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
        int x = t.block[i].x;
        int y = t.block[i].y;

        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            cout << "*";
        }
    }

    setColor(7);  // Reset color to default
}

bool Tetris::checkCollision(const Tetromino& t, int offsetX, int offsetY) {
    for (int i = 0; i < 4; i++) {
        int x = t.block[i].x + offsetX;
        int y = t.block[i].y + offsetY;

        if (y >= HEIGHT || x < 0 || x >= WIDTH || (y >= 0 && board[y][x] != 0)) {
            return true;  // Collision detected
        }
    }

    return false;
}

void Tetris::mergeTetromino(const Tetromino& t) {
    for (int i = 0; i < 4; i++) {
        int x = t.block[i].x;
        int y = t.block[i].y;

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

void Tetris::rotateTetromino(Tetromino& t) {
    Tetromino rotated = t;
    Point center = t.block[1];

    for (int i = 0; i < 4; i++) {
        int x = t.block[i].x - center.x;
        int y = t.block[i].y - center.y;

        rotated.block[i].x = center.x - y;
        rotated.block[i].y = center.y + x;
    }

    if (!checkCollision(rotated, 0, 0)) {
        t = rotated;
    }
}

int Tetris::getRandomTetromino() {
    return rand() % 7;
}

void Tetris::resetGame() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = 0;
        }
    }

    score = 0;
    level = 1;
}

bool Tetris::moveTetromino(Tetromino& t, int offsetX, int offsetY) {
    if (!checkCollision(t, offsetX, offsetY)) {
        t.block[0].x += offsetX;
        t.block[1].x += offsetX;
        t.block[2].x += offsetX;
        t.block[3].x += offsetX;

        t.block[0].y += offsetY;
        t.block[1].y += offsetY;
        t.block[2].y += offsetY;
        t.block[3].y += offsetY;

        return true;  // Move successful
    }

    return false;  // Move failed (collision)
}

void Tetris::updateScoreAndLevel(int linesCleared) {
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

void Tetris::generateNextTetromino() {
    nextTetromino = tetrominos[getRandomTetromino()];
}

void Tetris::holdTetromino() {
    if (!hasHeldTetromino) {
        if (heldTetromino.block[0].x == -1) {
            heldTetromino = currentTetromino;
            currentTetromino = tetrominos[getRandomTetromino()];
        } else {
            Tetromino temp = currentTetromino;
            currentTetromino = heldTetromino;
            heldTetromino = temp;
        }
        hasHeldTetromino = true;
    }
}

void Tetris::setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Tetris::gameOverScreen() {
    system("cls");
    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;
    cout << "Press 'R' to restart or 'Q' to quit." << endl;

    char key;
    do {
        key = _getch();
    } while (key != 'r' && key != 'q');

    if (key == 'r') {
        resetGame();
        runGame();  // Restart the game
    } else {
        exit(0);  // Quit the game
    }
}

void Tetris::drawGhostPiece(const Tetromino& t, int value) {
    int originalY = t.block[0].y;
    while (!checkCollision(t, 0, 1)) {
        moveTetromino(t, 0, 1);
    }
    t.block[0].y = originalY;

    drawTetromino(t, value);
}

void Tetris::pauseScreen() {
    cout << "Paused. Press any key to resume." << endl;
    _getch();  // Wait for a key press to resume
}

void Tetris::runGame() {
    srand(time(nullptr));
    resetGame();

    char key;
    bool gameOver = false;

    while (!gameOver) {
        currentTetromino = nextTetromino;
        int currentX = WIDTH / 2 - 1;
        int currentY = 0;
        hasHeldTetromino = false;

        generateNextTetromino();

        if (checkCollision(currentTetromino, currentX, currentY)) {
            gameOver = true;
            break;
        }

        while (true) {
            drawBoard();
            drawGhostPiece(currentTetromino, 1);

            if (_kbhit()) {
                key = _getch();
                switch (key) {
                    case 'a':
                        moveTetromino(currentTetromino, -1, 0);
                        break;
                    case 'd':
                        moveTetromino(currentTetromino, 1, 0);
                        break;
                    case 's':
                        if (!moveTetromino(currentTetromino, 0, 1)) {
                            mergeTetromino(currentTetromino);
                            break;
                        }
                        break;
                    case 'w':
                        rotateTetromino(currentTetromino);
                        break;
                    case 'h':
                        holdTetromino();
                        break;
                    case 'q':
                        gameOver = true;
                        break;
                    case 224:  // Arrow key
                        key = _getch();
                        switch (key) {
                            case 75:  // Left arrow
                                moveTetromino(currentTetromino, -1, 0);
                                break;
                            case 77:  // Right arrow
                                moveTetromino(currentTetromino, 1, 0);
                                break;
                            case 80:  // Down arrow
                                if (!moveTetromino(currentTetromino, 0, 1)) {
                                    mergeTetromino(currentTetromino);
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

            if (!moveTetromino(currentTetromino, 0, 1)) {
                mergeTetromino(currentTetromino);
                break;
            }

            Sleep(100);
        }
    }

    gameOverScreen();
}

int main() {
    Tetris tetris;
    tetris.runGame();

    return 0;
}
