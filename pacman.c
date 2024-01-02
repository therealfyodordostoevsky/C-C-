#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#define WIDTH 30
#define HEIGHT 17
#define GHOSTS 5

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int CELL_SIZE = 64;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position position;
    SDL_Texture *texture;
} Entity;

// Function to initialize SDL and create a window and renderer
int initializeSDL(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

// Function to load an image as an SDL texture
SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (surface == NULL) {
        fprintf(stderr, "SDL_LoadBMP failed: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

// Function to draw the game board
void drawBoard(SDL_Renderer *renderer, Entity player, Entity ghosts[], Entity dots[], int numGhosts, int numDots) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw dots
    for (int i = 0; i < numDots; i++) {
        SDL_RenderCopy(renderer, dots[i].texture, NULL, &(SDL_Rect){dots[i].position.x, dots[i].position.y, CELL_SIZE, CELL_SIZE});
    }

    // Draw player
    SDL_RenderCopy(renderer, player.texture, NULL, &(SDL_Rect){player.position.x, player.position.y, CELL_SIZE, CELL_SIZE});

    // Draw ghosts
    for (int i = 0; i < numGhosts; i++) {
        SDL_RenderCopy(renderer, ghosts[i].texture, NULL, &(SDL_Rect){ghosts[i].position.x, ghosts[i].position.y, CELL_SIZE, CELL_SIZE});
    }

    SDL_RenderPresent(renderer);
}

// Function to check collision with ghosts
int checkCollision(Position playerPos, Position ghostPos[], int numGhosts) {
    for (int i = 0; i < numGhosts; i++) {
        if (playerPos.x == ghostPos[i].x && playerPos.y == ghostPos[i].y) {
            return 1;  // Collision with a ghost
        }
    }
    return 0;  // No collision
}

// Function to update ghost positions randomly
void updateGhosts(Position ghostPos[], int numGhosts) {
    for (int i = 0; i < numGhosts; i++) {
        int move = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

        switch (move) {
            case 0:
                if (ghostPos[i].y > 0) {
                    ghostPos[i].y--;
                }
                break;
            case 1:
                if (ghostPos[i].y < HEIGHT - 1) {
                    ghostPos[i].y++;
                }
                break;
            case 2:
                if (ghostPos[i].x > 0) {
                    ghostPos[i].x--;
                }
                break;
            case 3:
                if (ghostPos[i].x < WIDTH - 1) {
                    ghostPos[i].x++;
                }
                break;
        }
    }
}

// Function to randomly update the game board with dots
void updateBoard(Entity dots[], int *numDots) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (rand() % 5 == 0) {
                // Randomly update a cell
                if (rand() % 2 == 0) {
                    dots[*numDots].position.x = j * CELL_SIZE;
                    dots[*numDots].position.y = i * CELL_SIZE;
                    (*numDots)++;
                }
            }
        }
    }
}

// Function to free SDL textures
void freeTextures(Entity player, Entity ghosts[], Entity dots[], int numGhosts, int numDots) {
    SDL_DestroyTexture(player.texture);
    for (int i = 0; i < numGhosts; i++) {
        SDL_DestroyTexture(ghosts[i].texture);
    }
    for (int i = 0; i < numDots; i++) {
        SDL_DestroyTexture(dots[i].texture);
    }
}

int main() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!initializeSDL(&window, &renderer)) {
        return 1;
    }

    srand(time(NULL));  // Seed for random number generation

    Entity player;
    player.position.x = WIDTH / 2 * CELL_SIZE;
    player.position.y = HEIGHT / 2 * CELL_SIZE;
    player.texture = loadTexture(renderer, "path/to/player.bmp");

    Entity ghosts[GHOSTS];
    for (int i = 0; i < GHOSTS; i++) {
        ghosts[i].position.x = rand() % WIDTH * CELL_SIZE;
        ghosts[i].position.y = rand() % HEIGHT * CELL_SIZE;
        ghosts[i].texture = loadTexture(renderer, "path/to/ghost.bmp");
    }

    Entity dots[WIDTH * HEIGHT];
    int numDots = 0;

    updateBoard(dots, &numDots);

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                freeTextures(player, ghosts, dots, GHOSTS, numDots);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
        }

        drawBoard(renderer, player, ghosts, dots, GHOSTS, numDots);

        // Get user input
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_W] && player.position.y > 0) {
            player.position.y -= CELL_SIZE;
        }
        if (state[SDL_SCANCODE_A] && player.position.x > 0) {
            player.position.x -= CELL_SIZE;
        }
        if (state[SDL_SCANCODE_S] && player.position.y < (HEIGHT - 1) * CELL_SIZE) {
            player.position.y += CELL_SIZE;
        }
        if (state[SDL_SCANCODE_D] && player.position.x < (WIDTH - 1) * CELL_SIZE) {
            player.position.x += CELL_SIZE;
        }

        // Update ghost positions randomly
        updateGhosts(ghosts, GHOSTS);

        // Check for collision with ghosts
        if (checkCollision(player.position, ghosts, GHOSTS)) {
            printf("\nMission Failed! You got caught by a ghost.\n");
            break;
        }

        // Update the game board randomly with dots
        updateBoard(dots, &numDots);

        // Check if all dots are eaten
        if (numDots == 0) {
            printf("\nMission Completed!\n");
            SDL_Delay(1000);  // Delay for better visualization
            break;
        }
    }

    freeTextures(player, ghosts, dots, GHOSTS, numDots);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
